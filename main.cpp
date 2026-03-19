#include <iostream>
#include "TestContent.h"

// Вимога: вивід розміру класу з пакуванням та без
void showMemoryInfo() {
    std::cout << "--- Memory Analysis ---" << std::endl;
    std::cout << "Size of TestContent (default): " << sizeof(TestContent) << " bytes" << std::endl;

#pragma pack(push, 1)
    struct PackedTC {
        void* ptr; // імітація Task*
        int s;
        int c;
    };
#pragma pack(pop)
    std::cout << "Size of TestContent (pragma pack 1): " << sizeof(PackedTC) << " bytes" << std::endl;
    std::cout << "-----------------------" << std::endl;
}

int main() {
    showMemoryInfo();

    // 1. Створення об'єктів
    TestContent setA(5);
    TestContent setB(5);

    // Створення тестових завдань
    Task t1 = {"What is C++?", {"Lang", "Food", "City", "Pet", "Car"}, 1, 10};
    Task t2 = {"2+2=?", {"3", "4", "5", "6", "7"}, 2, 5};
    Task t3 = {"What is AI?", {"Logic", "Magic", "Movie", "Bird", "None"}, 1, 15};

    // 2. Додавання (Логіка множин)
    setA.addTask(t1);
    setA.addTask(t2); // setA = {t1, t2}

    setB.addTask(t2);
    setB.addTask(t3); // setB = {t2, t3}

    std::cout << "Set A:\n" << setA << std::endl;
    std::cout << "Set B:\n" << setB << std::endl;

    // 3. Операції множин
    TestContent merged = setA + setB; // Злиття (t1, t2, t3)
    std::cout << "Merged (A + B):\n" << merged << std::endl;

    TestContent intersection = setA * setB; // Перетин (t2)
    std::cout << "Intersection (A * B):\n" << intersection << std::endl;

    TestContent difference = setA - setB; // Різниця (t1)
    std::cout << "Difference (A - B):\n" << difference << std::endl;

    // 4. Масив об'єктів
    TestContent examGroups[2] = { TestContent(2), TestContent(2) };
    examGroups[0].addTask(t1);

    std::cout << "Array element 0:\n" << examGroups[0] << std::endl;

    return 0;
}