#include <lift_cabine.h>
#include <open_door_strategy.h>
#include <close_door_strategy.h>
#include <lift_move_strategy.h>
#include <pubsub.h>
#include <gtest/gtest.h>
#include <iostream>
#include <thread>
#include <chrono>
class TestCabine : public ::testing::Test
{
protected:
    void SetUp()
    {
      cabine = std::make_shared<lift_np::lift_cabine>(static_cast<size_t>(2000),1);
      cabine->set_open_door_strategy(std::make_shared<lift_np::open_door_strategy>("door opened "));
      cabine->set_close_door_strategy(std::make_shared<lift_np::close_door_strategy>("door closed ", static_cast<size_t>(1000)));
      cabine->set_move_strategy(std::make_shared<lift_np::lift_move_strategy>("lift moved "));
      pub.subscribe(*(cabine.get()));
    }
    void TearDown()
    {
    }
    std::shared_ptr<lift_np::ilift_cabine> cabine;
    lift_np::publisher<lift_np::lift_message> pub;
};

TEST_F(TestCabine, test1)
{
    lift_np::lift_message first_call(10,lift_np::MESSAGE_TYPE::PULT_CALL);
    lift_np::lift_message second_call(2,lift_np::MESSAGE_TYPE::PULT_CALL);
    lift_np::lift_message third_call(12,lift_np::MESSAGE_TYPE::CABINE_CALL);
    pub.send(first_call);
    std::this_thread::sleep_for(std::chrono::milliseconds(6000));
    pub.send(second_call);
    pub.send(third_call);
    std::this_thread::sleep_for(std::chrono::milliseconds(40000));
}


