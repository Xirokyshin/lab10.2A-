#include "pch.h"
#include "CppUnitTest.h"
#include "../PR10.2.A.cpp"  

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        // Тест для CompareStudents
        TEST_METHOD(TestCompareStudents)
        {
            // Створюємо двох студентів для порівняння
            Student student1;
            student1.surname = "Ivanov";
            student1.physics = 5;
            student1.mathematics = 4;
            student1.informatics = 3;

            Student student2;
            student2.surname = "Petrov";
            student2.physics = 5;
            student2.mathematics = 4;
            student2.informatics = 4;

            // Виконуємо порівняння студентів
            bool result = CompareStudents(student1, student2);

            // Перевіряємо, чи результат правильний: student1 має нижчу оцінку з інформатики
            Assert::IsTrue(result == false);
        }

        // Тест для BinarySearch з відсутнім студентом
        TEST_METHOD(TestBinarySearchNotFound)
        {
            // Створюємо масив студентів
            Student students[] = {
                {"Ivanov", 1, COMPUTER_SCIENCE, 5, 4, 3},
                {"Petrov", 2, MATHEMATICS, 4, 5, 4},
                {"Sidorov", 3, PHYSICS, 3, 3, 5}
            };

            int N = sizeof(students) / sizeof(students[0]);

            // Студент, якого шукаємо, не існує в масиві
            string surname = "NonExistent";
            double average = 5.0;  // Середній бал 5.0, але цього студента немає в списку
            int informatics = 5;

            // Перевіряємо, чи студент не знайдений
            bool found = BinarySearch(students, N, surname, average, informatics);

            // Перевіряємо, чи пошук повернув правильний результат (не знайдено)
            Assert::IsTrue(found == false);
        }
    };
}
