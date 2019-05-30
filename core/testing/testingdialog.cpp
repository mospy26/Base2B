#include <QApplication>
#include <QDebug>
#include "testingdialog.h"

TestingDialog::TestingDialog(std::vector<std::unique_ptr<TestRunner>> tests, int timeout, int nextTestWaitTime) :
    timeout(timeout), nextTestWaitTime(nextTestWaitTime), tests(std::move(tests)), currentTest(0), initialized(false), waiting(false) {

}

void TestingDialog::update() {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    if (!initialized) {
        // Begin the timer when update is called for the first time
        time = currentTime;
        initialized = true;
    }

    if (currentTest >= tests.size()) {
        // Finished running test cases, so quit
        QApplication::quit();
        return;
    }

    auto &test = tests[currentTest];
    test->update();

    // Fail test case if it took too long to complete
    if (currentTime-time >= timeout) {
        test->fail();
    }

    if (waiting) {
        // Wait for specified time before starting next test
        if (currentTime-time >= nextTestWaitTime) {
            nextTest();
            waiting = false;
        }
    } else if (test->getStatus() != TestRunner::Status::Running) {
        // Start waiting if test case finished
        waiting = true;
        time = currentTime;
    }
}

void TestingDialog::nextTest() {
    QString res = tests[currentTest]->getStatus() == TestRunner::Status::Passed ? "PASSED" : "FAILED";
    qWarning() << QString("TEST (%1): %2").arg(QString::fromStdString(tests[currentTest]->getName())).arg(res);
    currentTest++;
    time = QDateTime::currentMSecsSinceEpoch();
}

void TestingDialog::render(Renderer &renderer) {
    if (currentTest < tests.size()) {
        // Draw status text in top left corner
        QString res;
        switch (tests[currentTest]->getStatus()) {
        case TestRunner::Status::Passed:
            res = "PASSED";
            break;
        case TestRunner::Status::Failed:
            res = "FAILED";
            break;
        default:
            res = "RUNNING";
            break;
        }
        renderer.getPainter().setFont(QFont("times", 22));
        renderer.getPainter().drawText(50, 50, QString::fromStdString(tests[currentTest]->getName()));
        renderer.getPainter().drawText(50, 100, res);

        // Render
        tests[currentTest]->render(renderer);
    }
}
