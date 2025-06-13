#pragma once

#include <gtest/gtest.h>

#include "CommonLib/Utils/DateTimeUtils.h"

/**
 * @file DateTimeUtilsTest.h
 * @brief Test fixture for CommonLib::DateTimeUtils and its core functionality.
 */
class DateTimeUtilsTest: public ::testing::Test
{
    protected:
        DateTimeUtilsTest() = default;
        ~DateTimeUtilsTest() override = default;

        void SetUp() override {}
        void TearDown() override {}
};
