#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include "gamestage.h"

class TestRunner : public GameStage {
public:
    enum class Status {
        Running,
        Passed,
        Failed
    };

    TestRunner(std::string name);
    virtual ~TestRunner() = 0;

    /**
     * @brief fail Sets the test's status to Failed
     */
    void fail();
    Status getStatus();
    std::string getName();

protected:
    Status status;

private:
    std::string name;
};

#endif // TESTRUNNER_H
