/** @file
 *  @brief This file contains the definition of the NonCopyable class.
 */

#pragma once

#include "CommonLib/ApiMacro.h"

namespace CommonLib
{
/**
 * @class NonCopyable
 * @brief A base class to prevent copying of derived classes.
 *
 * This class is used to prevent copying of derived classes by deleting
 * the copy constructor and copy assignment operator. Move operations are
 * explicitly defaulted to allow moving.
 */
class COMMONLIB_API NonCopyable
{
    protected:
        /**
         * @brief Constructs a NonCopyable object.
         *
         * The constructor is protected to allow derived classes to construct the object.
         */
        NonCopyable() = default;

        /**
         * @brief Destroys the NonCopyable object.
         *
         * The destructor is virtual to ensure proper cleanup of derived classes.
         */
        virtual ~NonCopyable() = default;

    public:
        /**
         * @brief Deleted copy constructor.
         *
         * Prevents copying of the object.
         *
         * @param other The object to copy from.
         */
        NonCopyable(const NonCopyable&) = delete;

        /**
         * @brief Deleted copy assignment operator.
         *
         * Prevents copying of the object.
         *
         * @param other The object to copy from.
         * @return A reference to this object.
         */
        auto operator=(const NonCopyable&) -> NonCopyable& = delete;

        /**
         * @brief Defaulted move constructor.
         *
         * Allows moving of the object.
         *
         * @param other The object to move from.
         */
        NonCopyable(NonCopyable&&) = default;

        /**
         * @brief Defaulted move assignment operator.
         *
         * Allows moving of the object.
         *
         * @param other The object to move from.
         * @return A reference to this object.
         */
        auto operator=(NonCopyable&&) -> NonCopyable& = default;
};
}  // namespace CommonLib
