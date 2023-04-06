// 6_GoogleTest.cpp

// xUnit Test Framework
// 1) Fixture
// 2) Assertion
// 3) Google Test 옵션

#include <gtest/gtest.h>

int foo() { return 42; }
int goo() { return 100; }

// 1. ASSERT_
// - 단언문이 실패할 경우, 이후의 코드를 수행하지 않습니다.
//   하나의 테스트케이스 안에 여러개의 단언문이 존재할 경우
//   이후의 단언문이 수행되지 않는 문제가 있습니다.
//   "죽은 단언문"
//   > 하나의 테스트케이스 안에 여러개의 단언문을 두지 말자.(xUnit Test Pattern)
//    - "중복된 테스트 케이스가 발생하고 유지 보수 비용이 증가합니다."
//   => Google Test는 새로운 단언문을 제공합니다.
//      EXPECT_EQ / NE / LT / GT / LE / GE / TRUE / FALSE ...
TEST(SampleTest1, Sample1)
{
    // 검증
    ASSERT_EQ(42, foo());
    ASSERT_EQ(100, goo());
    ASSERT_EQ(42, foo());
    ASSERT_EQ(100, goo());
    ASSERT_EQ(42, foo());
    ASSERT_EQ(100, goo());
}

// EXPECT_XX
// - 단언문이 실패할 경우, 테스트의 결과는 실패입니다.
//   이후의 검증을 계속 수행합니다.
TEST(SampleTest, Sample2)
{
    // 검증
    EXPECT_EQ(42, foo());
    EXPECT_EQ(100, goo());
    EXPECT_EQ(42, foo());
    EXPECT_EQ(100, goo());
    EXPECT_EQ(42, foo());
    EXPECT_EQ(100, goo());
}

//-----
class User {
    std::string name = "Tom";
    int age = 42;

public:
    std::string GetName() const { return name; }
    int GetAge() const { return age; }
};

User* GetUser() { return new User; }
// User* GetUser() { return nullptr; }

TEST(UserTest, Sample3)
{
    User* user = GetUser();

    ASSERT_NE(user, nullptr); // 사전 조건 단언문

    EXPECT_EQ(user->GetName(), "Tom");
    EXPECT_EQ(user->GetAge(), 42);
}

// 2. 문자열 비교 단언문
// => const char* / char[] 형태의 문자열 비교에서 사용해야 합니다.
// - EXPECT_STREQ / EXPECT_STRNE
// - EXPECT_STRCASEEQ / EXPECT_STRCASENE : 대소문자 무시
TEST(SampleTest2, Sample1)
{
    std::string s1 = "hello";
    std::string s2 = "hello";
    EXPECT_EQ(s1, s2);

    char s3[] = "HELLO";
    const char* s4 = "hello";
    // EXPECT_EQ(s3, s4);
    // EXPECT_STREQ(s3, s4);
    EXPECT_STRCASEEQ(s3, s4);
}

// 3. 부동소수점 비교 단언문
//  - float, double
//   EXPECT_FLOAT_EQ / EXPECT_DOUBLE_EQ

//  - 오차 범위를 직접 지정하고 싶다.
//   EXPECT_NEAR

TEST(SampleTest3, Sample1)
{
    double a = 0.7;
    double b = 0.1 * 7;

    // EXPECT_EQ(a, b);
    EXPECT_DOUBLE_EQ(a, b);
    EXPECT_NEAR(a, b, 0.00000001); // !!
}