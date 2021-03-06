//
// Created by been on 2022/6/16.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <string>

using namespace std;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;


struct BankAccount {
    int balance = 0;

    BankAccount(int balance) : balance(balance) {}

    BankAccount() {}

    inline void deposit(int amount) {
        balance += amount;
    }

    bool withdraw(int amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

struct BankAccountTest : testing::Test {
    BankAccount *account;

    BankAccountTest() {
        account = new BankAccount;
    }

    virtual ~BankAccountTest() {
        delete account;
    }
};

struct account_state {
    int initial_balance;
    int withdraw_amount;
    int final_balance;
    bool success;
};

struct WithDrawAccountTest : BankAccountTest, testing::WithParamInterface<account_state> {
    WithDrawAccountTest() {
        account->balance = GetParam().initial_balance;
    }

};

INSTANTIATE_TEST_CASE_P
(Default, WithDrawAccountTest,
 testing::Values(
         account_state{100, 50, 50, true},
         account_state{100, 200, 100, false}
 ));


TEST_P(WithDrawAccountTest, FinalBalance) {
    auto as = GetParam();
    auto success = account->withdraw(as.withdraw_amount);
    EXPECT_EQ(as.final_balance, account->balance);
    EXPECT_EQ(as.success, success);
}


TEST_F(BankAccountTest, BankAccountTestStartsByTEST_F) {
    EXPECT_EQ(0, account->balance);
}

TEST_F(BankAccountTest, CanDepositMoney) {
    account->deposit(100);
    EXPECT_EQ(100, account->balance);
}

TEST(AccountTest, BankAccountStartsEmpty) {
    BankAccount account;
    EXPECT_EQ(0, account.balance);
}
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
// Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");

// Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

class MyClass {
private:
    int baseValue;
public:
    MyClass(int baseValue) : baseValue(baseValue) {}

    void Increment(int byValue) {
        baseValue += byValue;
    }

    int getValue() {
        return baseValue;
    }
};

struct MyClassTest : public testing::Test {
    MyClass *mc;

    void SetUp() override {
        mc = new MyClass(100);
    }

    void TearDown() override {
        delete mc;
    }
};


class Stack {
    std::vector<int> vstack = {};
public:
    void push(int value) {
        vstack.push_back(value);
    }

    int pop() {
        if (vstack.size() > 0) {
            int value = vstack.back();
            vstack.pop_back();
            return value;
        } else {
            return -1;
        }
    }

    int size() {
        return vstack.size();
    }
};

struct stackTest : public testing::Test {
    Stack s1;

    void SetUp() override {
        int value[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (auto &val: value) {
            s1.push(val);
        }
    }

    void TearDown() override {

    }
};

TEST_F(stackTest, PopTest) {
    int last = 9;
    while (last != 1) {
        ASSERT_EQ(s1.pop(), last--);
    }
}


// test fixture
TEST_F(MyClassTest, Increment_by_5) {
    // act
    mc->Increment(5);
    // assert
    ASSERT_EQ(mc->getValue(), 105);
}


class DatabaseConnect {
public:
    virtual bool login(std::string username, std::string password) {
        return true;
    }

    virtual bool logout(std::string username) {
        return true;
    }

    virtual int fetchRecord() {
        return -1;
    }
};

class MockDB : public DatabaseConnect {
public:
    MOCK_METHOD0(fetchRecord, int());
    MOCK_METHOD1(logout, bool (std::string username));
    MOCK_METHOD2(login, bool (std::string username, std::string password));
};

class MyDatabase {
    DatabaseConnect &connect;
public:
    MyDatabase(DatabaseConnect &connect) : connect(connect) {}

    int Init(std::string username, std::string password) {
        if (connect.login(username, password) != true) {
            std::cout << "DB Failure" << std::endl;
            return -1;
        } else {
            std::cout << "DB success" << std::endl;
            return 1;
        }
    }
};

TEST(MyDBTest, LoginTest) {
    // arrange
    MockDB mdb;
    MyDatabase db(mdb);

    // mock
    EXPECT_CALL(mdb, login("Terminator", "I'm Back"))
            .Times(1)
            .WillOnce(Return(true));
    // act
    int retValue = db.Init("Terminator", "I'm Back");
    // assert
    EXPECT_EQ(retValue, 1);
}


