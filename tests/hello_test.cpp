//
// Created by been on 2022/6/16.
//
#include <gtest/gtest.h>


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

TEST_P(WithDrawAccountTest, FinalBalance) {
    auto as = GetParam();
    auto success = account->withdraw(as.withdraw_amount);
    EXPECT_EQ(as.final_balance, account->balance);
    EXPECT_EQ(as.success, success);
}

INSTANTIATE_TEST_CASE_P(Default, WithDrawAccountTest,
 testing::Values(
         account_state{100, 50, 50, true},
         account_state{100, 200, 100, false}
         ));


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