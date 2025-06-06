#pragma once

#include <gtest/gtest.h>

#include "CommonLib/Patterns/Singleton.h"

class SingletonTest: public ::testing::Test
{
    protected:
        SingletonTest() = default;
        ~SingletonTest() override = default;

        void SetUp() override {}
        void TearDown() override {}
};
