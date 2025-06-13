#pragma once

#include <chrono>
#include <string>

#include "CommonLib/ApiMacro.h"

namespace CommonLib
{
/**
 * @class DateTimeUtils
 * @brief Utility class for date and time formatting and duration measurement.
 *
 * Provides static methods for obtaining the current date and time in various formats,
 * formatting time points, and measuring elapsed time between two time points.
 */
class COMMONLIB_API DateTimeUtils
{
    public:
        /**
         * @brief Returns the current local date and time as a string.
         * @param format The format string (default: "%Y-%m-%d %H:%M:%S").
         * @return The formatted date and time string.
         */
        static auto now(const std::string& format = "%Y-%m-%d %H:%M:%S") -> std::string;

        /**
         * @brief Returns the current UTC date and time as a string.
         * @param format The format string (default: "%Y-%m-%d %H:%M:%S").
         * @return The formatted UTC date and time string.
         */
        static auto now_utc(const std::string& format = "%Y-%m-%d %H:%M:%S") -> std::string;

        /**
         * @brief Returns the current local date as a string.
         * @param format The format string (default: "%Y-%m-%d").
         * @return The formatted date string.
         */
        static auto current_date(const std::string& format = "%Y-%m-%d") -> std::string;

        /**
         * @brief Returns the current local time as a string.
         * @param format The format string (default: "%H:%M:%S").
         * @return The formatted time string.
         */
        static auto current_time(const std::string& format = "%H:%M:%S") -> std::string;

        /**
         * @brief Formats a given time_point as a string.
         * @param tp The time point to format.
         * @param format The format string.
         * @return The formatted date and time string.
         */
        static auto format(const std::chrono::system_clock::time_point& tp,
                           const std::string& format) -> std::string;

        /**
         * @brief Returns the current steady clock time point for duration measurement.
         * @return The current steady clock time point.
         */
        static auto timer_now() -> std::chrono::steady_clock::time_point;

        /**
         * @brief Returns the elapsed time in seconds between two time points.
         * @param start The start time point.
         * @param end The end time point.
         * @return The elapsed time in seconds.
         */
        static auto elapsed_s(const std::chrono::steady_clock::time_point& start,
                              const std::chrono::steady_clock::time_point& end) -> double;

        /**
         * @brief Returns the elapsed time in milliseconds between two time points.
         * @param start The start time point.
         * @param end The end time point.
         * @return The elapsed time in milliseconds.
         */
        static auto elapsed_ms(const std::chrono::steady_clock::time_point& start,
                               const std::chrono::steady_clock::time_point& end) -> double;

        /**
         * @brief Returns the elapsed time in microseconds between two time points.
         * @param start The start time point.
         * @param end The end time point.
         * @return The elapsed time in microseconds.
         */
        static auto elapsed_us(const std::chrono::steady_clock::time_point& start,
                               const std::chrono::steady_clock::time_point& end) -> double;

        /**
         * @brief Converts a time_point to a string using the given format.
         * @param tp The time point to convert.
         * @param format The format string.
         * @return The formatted date and time string.
         */
        static auto to_string(const std::chrono::system_clock::time_point& tp,
                              const std::string& format) -> std::string;

        /**
         * @brief Parses a string to a time_point using the given format.
         * @param str The date/time string.
         * @param format The format string.
         * @return The parsed time_point.
         * @throws std::runtime_error if parsing fails.
         */
        static auto from_string(const std::string& str,
                                const std::string& format) -> std::chrono::system_clock::time_point;
};

}  // namespace CommonLib
