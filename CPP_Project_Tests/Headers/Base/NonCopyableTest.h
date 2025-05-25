#pragma once

#include <gtest/gtest.h>

#include "Base/NonCopyable.h"

class NonCopyableTest: public ::testing::Test
{
    protected:
        NonCopyableTest() = default;
        ~NonCopyableTest() override = default;

        void SetUp() override {}
        void TearDown() override {}
};
