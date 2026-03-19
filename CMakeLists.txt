cmake_minimum_required(VERSION 3.14)
project(TestProject)

# Стандарт C++17 для коректної роботи сучасних бібліотек
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- АВТОМАТИЧНЕ ЗАВАНТАЖЕННЯ GOOGLE TEST ---
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
# Запобігає конфліктам бібліотек на різних ОС
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- СТРУКТУРА ПРОЕКТУ ---

# 1. Створюємо бібліотеку з вашого класу.
# Включаємо сюди і .cpp і .h, щоб CMake знав, де шукати реалізацію методів.
add_library(TestLib TestContent.cpp TestContent.h)

# 2. Основна програма (App)
add_executable(App main.cpp)
target_link_libraries(App PRIVATE TestLib)

# 3. Юніт-тести (UnitTest)
# Ми лінкуємо (з'єднуємо) UnitTest.cpp з нашою бібліотекою TestLib та GTest
add_executable(UnitTest UnitTest.cpp)
target_link_libraries(UnitTest PRIVATE TestLib gtest_main)

# --- НАЛАШТУВАННЯ ТЕСТУВАЛЬНИКА ---
include(CTest)
enable_testing()
add_test(NAME AllTests COMMAND UnitTest)