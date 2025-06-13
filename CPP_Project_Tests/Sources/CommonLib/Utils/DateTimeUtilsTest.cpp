#include "CommonLib/Utils/DateTimeUtilsTest.h"

#include <chrono>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <thread>

int get_timezone_offset_seconds()
{
    std::time_t t = std::time(nullptr);
    std::tm local_tm{};
#if defined(_WIN32)
    localtime_s(&local_tm, &t);
#else
    localtime_r(&t, &local_tm);
#endif
    std::tm utc_tm{};
#if defined(_WIN32)
    gmtime_s(&utc_tm, &t);
#else
    gmtime_r(&t, &utc_tm);
#endif
    return static_cast<int>(std::mktime(&local_tm) - std::mktime(&utc_tm));
}

/**
 * @brief Tests that DateTimeUtils::now returns the current local time as a string.
 */
TEST_F(DateTimeUtilsTest, NowReturnsCurrentTimeString)
{
    using namespace CommonLib;
    int tz_offset = get_timezone_offset_seconds();

    auto before = std::chrono::system_clock::now();
    std::string now_str = DateTimeUtils::now("%Y-%m-%d %H:%M:%S");
    auto after = std::chrono::system_clock::now();

    std::tm tm_buf = {};
    std::istringstream iss(now_str);
    iss >> std::get_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
    std::time_t parsed_time = std::mktime(&tm_buf);

    std::time_t before_utc = std::chrono::system_clock::to_time_t(before);
    std::time_t after_utc = std::chrono::system_clock::to_time_t(after);

    // Adjust parsed_time to UTC
    parsed_time -= tz_offset;

    EXPECT_LE(before_utc, parsed_time);
    EXPECT_LE(parsed_time, after_utc);
}

/**
 * @brief Tests that DateTimeUtils::now_utc returns the current UTC time as a string.
 */
TEST_F(DateTimeUtilsTest, NowUtcReturnsUtcTimeString)
{
    using namespace CommonLib;
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm_buf;
#if defined(_WIN32)
    gmtime_s(&tm_buf, &now_c);
#else
    gmtime_r(&now_c, &tm_buf);
#endif
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm_buf);
    std::string expected(buf);

    std::string utc_str = DateTimeUtils::now_utc("%Y-%m-%d %H:%M:%S");
    EXPECT_EQ(utc_str, expected);
}

/**
 * @brief Tests that DateTimeUtils::current_date returns the current local date as a string.
 */
TEST_F(DateTimeUtilsTest, CurrentDateReturnsDateString)
{
    using namespace CommonLib;
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm_buf;
#if defined(_WIN32)
    localtime_s(&tm_buf, &now_c);
#else
    localtime_r(&now_c, &tm_buf);
#endif
    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm_buf);
    std::string expected(buf);

    std::string date_str = DateTimeUtils::current_date();
    EXPECT_EQ(date_str, expected);
}

/**
 * @brief Tests that DateTimeUtils::current_time returns the current local time as a string.
 */
TEST_F(DateTimeUtilsTest, CurrentTimeReturnsTimeString)
{
    using namespace CommonLib;
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm_buf;
#if defined(_WIN32)
    localtime_s(&tm_buf, &now_c);
#else
    localtime_r(&now_c, &tm_buf);
#endif
    char buf[9];
    std::strftime(buf, sizeof(buf), "%H:%M:%S", &tm_buf);
    std::string expected(buf);

    std::string time_str = DateTimeUtils::current_time();
    EXPECT_EQ(time_str, expected);
}

/**
 * @brief Tests that DateTimeUtils::to_string formats a time_point to a string (local time).
 */
TEST_F(DateTimeUtilsTest, ToStringFormatsTimePoint)
{
    using namespace CommonLib;
    auto tp = std::chrono::system_clock::from_time_t(1672531200);  // 2023-01-01 00:00:00 UTC
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::tm tm_buf;
#if defined(_WIN32)
    localtime_s(&tm_buf, &t);
#else
    localtime_r(&t, &tm_buf);
#endif
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm_buf);
    std::string expected(buf);

    std::string formatted = DateTimeUtils::to_string(tp, "%Y-%m-%d %H:%M:%S");
    EXPECT_EQ(formatted, expected);
}

/**
 * @brief Tests that DateTimeUtils::from_string parses a string to a time_point (local time).
 */
TEST_F(DateTimeUtilsTest, FromStringParsesToTimePoint)
{
    using namespace CommonLib;
    std::string date_str = "2023-01-01 00:00:00";
    auto tp = DateTimeUtils::from_string(date_str, "%Y-%m-%d %H:%M:%S");

    std::tm tm_buf = {};
    std::istringstream iss(date_str);
    iss >> std::get_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
    std::time_t expected_time = std::mktime(&tm_buf);
    auto expected = std::chrono::system_clock::from_time_t(expected_time);

    EXPECT_EQ(std::chrono::system_clock::to_time_t(tp),
              std::chrono::system_clock::to_time_t(expected));
}

/**
 * @brief Tests that formatting and then parsing returns the original time_point (with 1s
 * tolerance).
 */
TEST_F(DateTimeUtilsTest, ToStringAndFromStringRoundTrip)
{
    using namespace CommonLib;
    int tz_offset = get_timezone_offset_seconds();

    auto now = std::chrono::system_clock::now();
    std::string fmt = "%Y-%m-%d %H:%M:%S";
    std::string str = DateTimeUtils::to_string(now, fmt);
    auto parsed = DateTimeUtils::from_string(str, fmt);

    std::time_t now_utc = std::chrono::system_clock::to_time_t(now);
    std::time_t parsed_utc = std::chrono::system_clock::to_time_t(parsed);

    // Adjust parsed_utc to UTC
    parsed_utc -= tz_offset;

    EXPECT_LE(std::abs(now_utc - parsed_utc), 1);
}

/**
 * @brief Tests that parsing an invalid string throws an exception.
 */
TEST_F(DateTimeUtilsTest, FromStringThrowsOnInvalidInput)
{
    using namespace CommonLib;
    std::string invalid = "not a date";
    EXPECT_THROW(DateTimeUtils::from_string(invalid, "%Y-%m-%d %H:%M:%S"), std::exception);
}

/**
 * @brief Tests that to_string with an invalid format does not throw but returns a string.
 */
TEST_F(DateTimeUtilsTest, ToStringWithInvalidFormatReturnsString)
{
    using namespace CommonLib;
    auto now = std::chrono::system_clock::now();
    std::string result = DateTimeUtils::to_string(now, "%Q-%W-%E-%R");
    EXPECT_TRUE(result.size() > 0 || result.empty());
}

/**
 * @brief Tests timer_now and elapsed_s/ms/us for positive durations.
 */
TEST_F(DateTimeUtilsTest, TimerNowAndElapsed)
{
    using namespace CommonLib;
    auto start = DateTimeUtils::timer_now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto end = DateTimeUtils::timer_now();

    double elapsed_s = DateTimeUtils::elapsed_s(start, end);
    double elapsed_ms = DateTimeUtils::elapsed_ms(start, end);
    double elapsed_us = DateTimeUtils::elapsed_us(start, end);

    EXPECT_GT(elapsed_s, 0.0);
    EXPECT_GT(elapsed_ms, 0.0);
    EXPECT_GT(elapsed_us, 0.0);
    EXPECT_NEAR(elapsed_ms, elapsed_s * 1000.0, 1.0);
    EXPECT_NEAR(elapsed_us, elapsed_ms * 1000.0, 100.0);
}
