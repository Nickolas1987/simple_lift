#include <later_async_call.h>
#include <gtest/gtest.h>
#include <iostream>
class TestLater : public ::testing::Test
{
protected:
    void SetUp()
    {
    }
    void TearDown()
    {
    }
    lift_np::later_async_call late;
};

TEST_F(TestLater, test1)
{
    auto f = [&](){std::cout << "function called" <<std::endl;};
    std::future<void> res = late.start(2000, f);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    late.stop();
}


