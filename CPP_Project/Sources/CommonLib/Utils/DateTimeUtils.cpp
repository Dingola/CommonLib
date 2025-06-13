#include "CommonLib/Utils/DateTimeUtils.h"

#include <ctime>
#include <iomanip>
#include <sstream>

namespace CommonLib
{

auto DateTimeUtils::now(const std::string& format) -> std::string
{
    return DateTimeUtils::format(std::chrono::system_clock::now(), format);
}

auto DateTimeUtils::now_utc(const std::string& format) -> std::string
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm_buf;
#if defined(_WIN32)
    gmtime_s(&tm_buf, &now_c);
#else
    gmtime_r(&now_c, &tm_buf);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm_buf, format.c_str());
    return oss.str();
}

auto DateTimeUtils::current_date(const std::string& format) -> std::string
{
    return now(format);
}

auto DateTimeUtils::current_time(const std::string& format) -> std::string
{
    return now(format);
}

auto DateTimeUtils::format(const std::chrono::system_clock::time_point& tp,
                           const std::string& format) -> std::string
{
    std::time_t time_c = std::chrono::system_clock::to_time_t(tp);
    std::tm tm_buf;
#if defined(_WIN32)
    localtime_s(&tm_buf, &time_c);
#else
    localtime_r(&time_c, &tm_buf);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm_buf, format.c_str());
    return oss.str();
}

auto DateTimeUtils::timer_now() -> std::chrono::steady_clock::time_point
{
    return std::chrono::steady_clock::now();
}

auto DateTimeUtils::elapsed_s(const std::chrono::steady_clock::time_point& start,
                              const std::chrono::steady_clock::time_point& end) -> double
{
    return std::chrono::duration<double>(end - start).count();
}

auto DateTimeUtils::elapsed_ms(const std::chrono::steady_clock::time_point& start,
                               const std::chrono::steady_clock::time_point& end) -> double
{
    return std::chrono::duration<double, std::milli>(end - start).count();
}

auto DateTimeUtils::elapsed_us(const std::chrono::steady_clock::time_point& start,
                               const std::chrono::steady_clock::time_point& end) -> double
{
    return std::chrono::duration<double, std::micro>(end - start).count();
}

auto DateTimeUtils::to_string(const std::chrono::system_clock::time_point& tp,
                              const std::string& format) -> std::string
{
    return DateTimeUtils::format(tp, format);
}

auto DateTimeUtils::from_string(const std::string& str,
                                const std::string& format) -> std::chrono::system_clock::time_point
{
    std::tm tm_buf = {};
    std::istringstream iss(str);
    iss >> std::get_time(&tm_buf, format.c_str());

    if (iss.fail())
    {
        throw std::runtime_error("Failed to parse date/time string: " + str);
    }

    std::time_t time_c = std::mktime(&tm_buf);

    if (time_c == -1)
    {
        throw std::runtime_error("Failed to convert tm to time_t: " + str);
    }

    return std::chrono::system_clock::from_time_t(time_c);
}

}  // namespace CommonLib
