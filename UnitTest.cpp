#include <gtest/gtest.h>
#include "TestContent.h"

// Перевірка логіки "Множини": дублікати не мають додаватися
TEST(LogicTest, NoDuplicates) {
    TestContent tc(5);
    Task t = {"Скільки 2+2?", {"3","4","5","6","7"}, 2, 5};
    tc.addTask(t);
    tc.addTask(t); // Спроба додати те саме питання вдруге
    EXPECT_EQ(tc.count(), 1);
}

// Перевірка перетину множин
TEST(LogicTest, Intersection) {
    TestContent a(5), b(5);
    Task t1 = {"Q1", {}, 1, 1}, t2 = {"Q2", {}, 1, 1};
    a.addTask(t1); a.addTask(t2);
    b.addTask(t2);

    TestContent res = a * b; // Перетин має містити тільки Q2
    EXPECT_EQ(res.count(), 1);
    EXPECT_EQ(res[0].question, "Q2");
}