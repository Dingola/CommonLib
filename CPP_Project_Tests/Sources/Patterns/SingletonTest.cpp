#include "Patterns/SingletonTest.h"

#include <type_traits>

/**
 * @brief Test singleton class for verifying Singleton behavior.
 *
 * This class is used to test the Singleton CRTP implementation.
 * The constructor is private and Singleton is a friend.
 */
class TestSingleton: public CommonLib::Singleton<TestSingleton>
{
        friend class CommonLib::Singleton<TestSingleton>;

    private:
        TestSingleton() = default;
        ~TestSingleton() override = default;

    public:
        int value = 0;
};

/**
 * @brief Tests that get_instance always returns the same instance.
 *
 * This test verifies that multiple calls to get_instance return the same address.
 */
TEST_F(SingletonTest, ReturnsSameInstance)
{
    auto& instance1 = TestSingleton::get_instance();
    auto& instance2 = TestSingleton::get_instance();
    EXPECT_EQ(&instance1, &instance2);
}

/**
 * @brief Tests that the singleton instance can store and retrieve data.
 *
 * This test verifies that changes to the singleton instance persist across calls.
 */
TEST_F(SingletonTest, StoresAndRetrievesData)
{
    auto& instance = TestSingleton::get_instance();
    instance.value = 42;
    EXPECT_EQ(TestSingleton::get_instance().value, 42);
}

/**
 * @brief Tests that the singleton is neither copyable nor moveable.
 *
 * This test verifies that the singleton type is not copy or move constructible/assignable.
 */
TEST_F(SingletonTest, IsNotCopyOrMoveable)
{
    static_assert(!std::is_copy_constructible_v<TestSingleton>,
                  "Singleton should not be copy constructible");
    static_assert(!std::is_copy_assignable_v<TestSingleton>,
                  "Singleton should not be copy assignable");
    static_assert(!std::is_move_constructible_v<TestSingleton>,
                  "Singleton should not be move constructible");
    static_assert(!std::is_move_assignable_v<TestSingleton>,
                  "Singleton should not be move assignable");

    EXPECT_FALSE(std::is_copy_constructible_v<TestSingleton>);
    EXPECT_FALSE(std::is_copy_assignable_v<TestSingleton>);
    EXPECT_FALSE(std::is_move_constructible_v<TestSingleton>);
    EXPECT_FALSE(std::is_move_assignable_v<TestSingleton>);
}
