#include "pch.h"
#include "CppUnitTest.h"
#include "../PR10.2.A.cpp"  

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        // ���� ��� CompareStudents
        TEST_METHOD(TestCompareStudents)
        {
            // ��������� ���� �������� ��� ���������
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

            // �������� ��������� ��������
            bool result = CompareStudents(student1, student2);

            // ����������, �� ��������� ����������: student1 �� ����� ������ � �����������
            Assert::IsTrue(result == false);
        }

        // ���� ��� BinarySearch � ������� ���������
        TEST_METHOD(TestBinarySearchNotFound)
        {
            // ��������� ����� ��������
            Student students[] = {
                {"Ivanov", 1, COMPUTER_SCIENCE, 5, 4, 3},
                {"Petrov", 2, MATHEMATICS, 4, 5, 4},
                {"Sidorov", 3, PHYSICS, 3, 3, 5}
            };

            int N = sizeof(students) / sizeof(students[0]);

            // �������, ����� ������, �� ���� � �����
            string surname = "NonExistent";
            double average = 5.0;  // ������� ��� 5.0, ��� ����� �������� ���� � ������
            int informatics = 5;

            // ����������, �� ������� �� ���������
            bool found = BinarySearch(students, N, surname, average, informatics);

            // ����������, �� ����� �������� ���������� ��������� (�� ��������)
            Assert::IsTrue(found == false);
        }
    };
}
