/** @file
 *  @brief This file contains the definition of the Singleton class.
 */

#pragma once

#include "ApiMacro.h"
#include "Base/NonCopyable.h"
#include "Base/NonMoveable.h"

namespace CommonLib
{
/**
 * @class Singleton
 * @brief Meyers Singleton Pattern using CRTP
 *
 * This class implements the Meyers Singleton Pattern using the Curiously Recurring Template Pattern
 * (CRTP). Note: Derived classes need to declare 'friend class Singleton<T>'. Derived classes must
 * also have their constructor set to private to prevent instantiation.
 */
template<typename T>
class COMMONLIB_API Singleton: public NonCopyable, public NonMoveable
{
    protected:
        /**
         * @brief Constructs a Singleton object.
         *
         * The constructor is protected to allow derived classes to construct the object.
         */
        Singleton() = default;

        /**
         * @brief Destroys the Singleton object.
         *
         * The destructor is virtual to ensure proper cleanup of derived classes.
         */
        ~Singleton() override = default;

    public:
        /**
         * @brief Returns the singleton instance of the class.
         *
         * This function returns the singleton instance of the class, creating it if it does not
         * already exist. The instance is created in a thread-safe manner.
         *
         * @return The singleton instance of the class.
         */
        static auto get_instance() -> T&
        {
            static T instance;  // Thread-safe in C++11 and later
            return instance;
        }
};
}  // namespace CommonLib
