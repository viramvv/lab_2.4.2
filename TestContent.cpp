#include "TestContent.h"
#include <algorithm>
#include <random>

// Конструктор: виділяємо пам'ять через new
TestContent::TestContent(int s) : count_val(0) {
    size_val = (s > 0 && s <= MAX_LIMIT) ? s : 10;
    tasks = new Task[size_val];
}

TestContent::TestContent() : size_val(10), count_val(0) {
    tasks = new Task[size_val];
}

// Конструктор копіювання: виділяємо нову пам'ять для копії (Глибоке копіювання)
TestContent::TestContent(const TestContent& other) {
    size_val = other.size_val;
    count_val = other.count_val;
    tasks = new Task[size_val];
    for (int i = 0; i < count_val; i++) tasks[i] = other.tasks[i];
}

// Деструктор: обов'язково звільняємо пам'ять
TestContent::~TestContent() { delete[] tasks; }

// Додавання: реалізація логіки Множини (без повторів)
bool TestContent::addTask(const Task& t) {
    for (int i = 0; i < count_val; i++) {
        if (tasks[i] == t) return false; // Якщо таке питання вже є — вихід
    }
    if (count_val < size_val) {
        tasks[count_val++] = t;
        return true;
    }
    return false;
}

// Оператор присвоєння (=)
TestContent& TestContent::operator=(const TestContent& other) {
    if (this == &other) return *this;
    delete[] tasks; // Видаляємо стару пам'ять
    size_val = other.size_val;
    count_val = other.count_val;
    tasks = new Task[size_val]; // Виділяємо нову
    for (int i = 0; i < count_val; i++) tasks[i] = other.tasks[i];
    return *this;
}

// РЕАЛІЗАЦІЯ ОПЕРАТОРА РІЗНИЦІ (-)
TestContent operator-(const TestContent& a, const TestContent& b) {
    TestContent res(a.size_val);
    for (int i = 0; i < a.count_val; i++) {
        bool inB = false;
        for (int j = 0; j < b.count_val; j++) {
            if (a.tasks[i] == b.tasks[j]) { inB = true; break; }
        }
        if (!inB) res.addTask(a.tasks[i]); // Тільки ті, яких немає в B
    }
    return res;
}

// РЕАЛІЗАЦІЯ ПЕРЕТИНУ (*)
TestContent operator*(const TestContent& a, const TestContent& b) {
    TestContent res(std::max(a.size_val, b.size_val));
    for (int i = 0; i < a.count_val; i++) {
        for (int j = 0; j < b.count_val; j++) {
            if (a.tasks[i] == b.tasks[j]) res.addTask(a.tasks[i]);
        }
    }
    return res;
}

// РЕАЛІЗАЦІЯ ЗЛИТТЯ (+)
TestContent operator+(const TestContent& a, const TestContent& b) {
    TestContent res(a.size_val + b.size_val);
    for (int i = 0; i < a.count_val; i++) res.addTask(a.tasks[i]);
    for (int i = 0; i < b.count_val; i++) res.addTask(b.tasks[i]);
    return res;
}

// Методи доступу через індекс
Task& TestContent::operator[](int index) { return tasks[index]; }
const Task& TestContent::operator[](int index) const { return tasks[index]; }

// Приведення до рядка
TestContent::operator std::string() const {
    return "Test Set: " + std::to_string(count_val) + " unique tasks";
}

// Генерація вибірки
TestContent TestContent::generateTest(int k) const {
    int n = (k > count_val) ? count_val : k;
    TestContent res(n);
    std::vector<int> idx(count_val);
    for(int i=0; i<count_val; ++i) idx[i] = i;
    std::shuffle(idx.begin(), idx.end(), std::mt19937(std::random_device()()));
    for(int i=0; i<n; ++i) res.addTask(tasks[idx[i]]);
    return res;
}

// Унарні інкременти
TestContent& TestContent::operator++() { if (count_val < size_val) count_val++; return *this; }
TestContent TestContent::operator++(int) { TestContent t(*this); ++(*this); return t; }
TestContent& TestContent::operator--() { if (count_val > 0) count_val--; return *this; }
TestContent TestContent::operator--(int) { TestContent t(*this); --(*this); return t; }

// Ввід/Вивід
std::ostream& operator<<(std::ostream& out, const TestContent& tc) {
    out << (std::string)tc << "\n";
    for(int i=0; i<tc.count_val; i++) out << i+1 << ". " << tc.tasks[i].question << "\n";
    return out;
}

std::istream& operator>>(std::istream& in, TestContent& tc) {
    Task t;
    std::cout << "Question: "; std::getline(in >> std::ws, t.question);
    std::cout << "Points: "; in >> t.points;
    tc.addTask(t);
    return in;
}