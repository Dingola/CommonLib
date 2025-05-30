#pragma once

#include <gtest/gtest.h>

#include "CommonLib/Base/NonMoveable.h"

class NonMoveableTest: public ::testing::Test
{
    protected:
        NonMoveableTest() = default;
        ~NonMoveableTest() override = default;

        void SetUp() override {}
        void TearDown() override {}
};
