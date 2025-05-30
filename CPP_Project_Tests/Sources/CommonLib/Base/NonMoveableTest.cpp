#include "CommonLib/Base/NonMoveableTest.h"

#include <type_traits>

/**
 * @brief Test class derived from NonMoveable for testing purposes.
 *
 * This class is used to verify that move operations are correctly deleted
 * by inheriting from NonMoveable.
 */
class DerivedNonMoveable: public CommonLib::NonMoveable
{
    public:
        DerivedNonMoveable() = default;
        ~DerivedNonMoveable() override = default;
};

/**
 * @brief Tests that DerivedNonMoveable is not move constructible.
 *
 * This test verifies that the move constructor is deleted and
 * that objects of DerivedNonMoveable cannot be move constructed.
 */
TEST_F(NonMoveableTest, IsNotMoveConstructible)
{
    static_assert(!std::is_move_constructible_v<DerivedNonMoveable>,
                  "DerivedNonMoveable should not be move constructible");
    EXPECT_FALSE(std::is_move_constructible_v<DerivedNonMoveable>);
}

/**
 * @brief Tests that DerivedNonMoveable is not move assignable.
 *
 * This test verifies that the move assignment operator is deleted and
 * that objects of DerivedNonMoveable cannot be move assigned.
 */
TEST_F(NonMoveableTest, IsNotMoveAssignable)
{
    static_assert(!std::is_move_assignable_v<DerivedNonMoveable>,
                  "DerivedNonMoveable should not be move assignable");
    EXPECT_FALSE(std::is_move_assignable_v<DerivedNonMoveable>);
}
