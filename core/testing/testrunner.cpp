#include "testrunner.h"

TestRunner::TestRunner(std::string name) : status(Status::Running), name(name) {

}

TestRunner::~TestRunner() {

}

void TestRunner::fail() {
    status = Status::Failed;
}

TestRunner::Status TestRunner::getStatus() {
    return status;
}

std::string TestRunner::getName() {
    return name;
}
