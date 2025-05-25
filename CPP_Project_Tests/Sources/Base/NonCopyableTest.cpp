#include "Base/NonCopyableTest.h"

#include <type_traits>

/**
 * @brief Test class derived from NonCopyable for testing purposes.
 *
 * This class is used to verify that copy operations are correctly deleted
 * by inheriting from NonCopyable.
 */
class DerivedNonCopyable: public CommonLib::NonCopyable
{
    public:
        DerivedNonCopyable() = default;
        ~DerivedNonCopyable() override = default;
        DerivedNonCopyable(DerivedNonCopyable&&) = default;
        DerivedNonCopyable& operator=(DerivedNonCopyable&&) = default;
};

/**
 * @brief Tests that DerivedNonCopyable is not copy constructible.
 *
 * This test verifies that the copy constructor is deleted and
 * that objects of DerivedNonCopyable cannot be copy constructed.
 */
TEST_F(NonCopyableTest, IsNotCopyConstructible)
{
    static_assert(!std::is_copy_constructible_v<DerivedNonCopyable>,
                  "DerivedNonCopyable should not be copy constructible");
    EXPECT_FALSE(std::is_copy_constructible_v<DerivedNonCopyable>);
}

/**
 * @brief Tests that DerivedNonCopyable is not copy assignable.
 *
 * This test verifies that the copy assignment operator is deleted and
 * that objects of DerivedNonCopyable cannot be copy assigned.
 */
TEST_F(NonCopyableTest, IsNotCopyAssignable)
{
    static_assert(!std::is_copy_assignable_v<DerivedNonCopyable>,
                  "DerivedNonCopyable should not be copy assignable");
    EXPECT_FALSE(std::is_copy_assignable_v<DerivedNonCopyable>);
}

/**
 * @brief Tests that DerivedNonCopyable is move constructible.
 *
 * This test verifies that the move constructor is available and
 * that objects of DerivedNonCopyable can be move constructed.
 */
TEST_F(NonCopyableTest, IsMoveConstructible)
{
    EXPECT_TRUE(std::is_move_constructible_v<DerivedNonCopyable>);
}

/**
 * @brief Tests that DerivedNonCopyable is move assignable.
 *
 * This test verifies that the move assignment operator is available and
 * that objects of DerivedNonCopyable can be move assigned.
 */
TEST_F(NonCopyableTest, IsMoveAssignable)
{
    EXPECT_TRUE(std::is_move_assignable_v<DerivedNonCopyable>);
}
