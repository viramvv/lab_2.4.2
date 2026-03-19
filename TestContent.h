#ifndef TEST_CONTENT_H
#define TEST_CONTENT_H

#include <iostream>
#include <string>
#include <vector>

// Структура одного питання
struct Task {
    std::string question;      // Текст питання
    std::string answers[5];    // 5 варіантів відповіді
    int correctAnswer;         // Номер правильної відповіді (1-5)
    int points;                // Бали

    // Оператор порівняння для перевірки на дублікати (логіка множини)
    bool operator==(const Task& other) const {
        return question == other.question;
    }
};

const int MAX_LIMIT = 100;

class TestContent {
private:
    Task* tasks;      // Динамічний масив (вимога частини 2)
    int size_val;     // Максимальна місткість (поле size)
    int count_val;    // Поточна кількість (поле count)

public:
    // Конструктори та деструктор
    TestContent();
    TestContent(int s);                          // Контролює розмір
    TestContent(const TestContent& other);       // Глибоке копіювання
    ~TestContent();                              // Звільнення пам'яті

    // Методи доступу
    int size() const { return size_val; }
    int count() const { return count_val; }

    bool addTask(const Task& t);
    TestContent generateTest(int k) const;       // Генерація вибірки K питань

    // Оператори-методи (згідно з таблицею обов'язково методи класу)
    TestContent& operator=(const TestContent& other);
    Task& operator[](int index);                 // Індексування для запису
    const Task& operator[](int index) const;     // Індексування для читання (UnitTest)
    operator std::string() const;                // Приведення до рядка

    // Унарні оператори (Методи класу)
    TestContent& operator++();    // Префіксний ++
    TestContent operator++(int);  // Постфіксний ++
    TestContent& operator--();    // Префіксний --
    TestContent operator--(int);  // Постфіксний --

    // Бінарні оператори (Зовнішні дружні функції)
    friend TestContent operator+(const TestContent& a, const TestContent& b); // Злиття
    friend TestContent operator*(const TestContent& a, const TestContent& b); // Перетин
    friend TestContent operator-(const TestContent& a, const TestContent& b); // Різниця

    friend std::ostream& operator<<(std::ostream& out, const TestContent& tc);
    friend std::istream& operator>>(std::istream& in, TestContent& tc);
};

#endif