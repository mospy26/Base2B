#ifndef TESTINGDIALOG_H
#define TESTINGDIALOG_H

#include <vector>
#include <memory>
#include <QDateTime>
#include "testrunner.h"

class TestingDialog : public GameStage {
public:
    /**
     * @brief TestingDialog
     * @param tests The tests that will be run
     * @param timeout The maximum milliseconds a test can run for before automatically failing
     * @param nextTestWaitTime The delay in milliseconds before starting the next test
     */
    TestingDialog(std::vector<std::unique_ptr<TestRunner>> tests, int timeout = 10000, int nextTestWaitTime = 2000);

    void update();
    void render(Renderer &renderer);

    /**
     * @brief nextTest Stops the current test and starts the next one
     */
    void nextTest();

private:
    qint64 time;
    int timeout;
    int nextTestWaitTime;
    std::vector<std::unique_ptr<TestRunner>> tests;
    size_t currentTest;
    bool initialized;
    bool waiting;
};

#endif // TESTINGDIALOG_H
