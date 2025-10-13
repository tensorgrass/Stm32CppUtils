#ifndef TESTVOID_HPP
#define TESTVOID_HPP

#include "TestBase.hpp"

class TestVoid : public TestBase {
   public:
    TestVoid(ControllerBase* controllerBaseValue);

    char getGroup() const override { return '\0'; }
    void sendData() override;
    void receiveData() override;

   private:

};

#endif  // TESTVOID_HPP