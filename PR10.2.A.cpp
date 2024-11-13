#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>  // ��� std::binary_search
#include <Windows.h>

using namespace std;

// ������ ��������������
enum Specialization { COMPUTER_SCIENCE, MATHEMATICS, PHYSICS, ENGINEERING, BIOLOGY };
string specializationStr[] = { "����'����� �����", "����������", "Գ����", "��������", "�������" };

// ��������� ��� ������������� ��������
struct Student {
    string surname;
    unsigned course;
    Specialization specialization;
    int physics;
    int mathematics;
    int informatics;

    double average() const {
        return (physics + mathematics + informatics) / 3.0;
    }
};

// ������� ��� ��������, ���������, ���������� �� ���������� ���������� ����
void InputStudents(Student* students, int N);
void PrintStudents(const Student* students, int N);
void SortStudents(Student* students, int N);
bool CompareStudents(const Student& a, const Student& b);
bool BinarySearch(const Student* students, int N, const string& surname, double average, int informatics);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int numStudents;
    cout << "������ ������� ��������: ";
    cin >> numStudents;

    // ������������� ����� ��������� �������
    Student* students = new Student[numStudents];

    int menuItem;
    do {
        cout << "\n����:\n";
        cout << "1 - �������� ����� ��������\n";
        cout << "2 - ���� ����� ��������\n";
        cout << "3 - Գ����� ���������� ��������\n";
        cout << "4 - ����� ��������\n";
        cout << "0 - �����\n";
        cout << "������� ��: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            InputStudents(students, numStudents);
            break;
        case 2:
            PrintStudents(students, numStudents);
            break;
        case 3:
            SortStudents(students, numStudents);
            cout << "������ �������� �����������.\n";
            break;
        case 4:
        {
            string surname;
            double average;
            int informatics;
            cout << "������ ������� ��������: ";
            cin >> surname;
            cout << "������ ������� ���: ";
            cin >> average;
            cout << "������ ������ � �����������: ";
            cin >> informatics;
            if (BinarySearch(students, numStudents, surname, average, informatics)) {
                cout << "�������� ��������.\n";
            }
            else {
                cout << "�������� �� ��������.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "������������ ����. ��������� �� ���.\n";
        }
    } while (menuItem != 0);

    delete[] students;  // ��������� ���'��
    return 0;
}

void InputStudents(Student* students, int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":\n";
        cin.ignore();
        cout << " �������: "; getline(cin, students[i].surname);
        cout << " ����: "; cin >> students[i].course;
        cout << " ������������ (0 - ����'����� �����, 1 - ����������, 2 - Գ����, 3 - ��������, 4 - �������): ";
        cin >> spec;
        students[i].specialization = static_cast<Specialization>(spec);
        cout << " ������ � ������: "; cin >> students[i].physics;
        cout << " ������ � ����������: "; cin >> students[i].mathematics;
        cout << " ������ � �����������: "; cin >> students[i].informatics;
    }
}

void PrintStudents(const Student* students, int N) {
    cout << "=============================================================================================\n";
    cout << "| � | �������         | ���� | ������������           | Գ���� | ���������� | ����������� |\n";
    cout << "---------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << "| ";
        cout << setw(15) << left << students[i].surname;
        cout << "  | " << setw(4) << right << students[i].course;
        cout << " | " << setw(21) << left << specializationStr[students[i].specialization];
        cout << "   | " << setw(6) << right << students[i].physics;
        cout << " | " << setw(10) << right << students[i].mathematics;
        cout << " | " << setw(11) << right << students[i].informatics << " |\n";
    }

    cout << "=============================================================================================\n";
}

void SortStudents(Student* students, int N) {
    sort(students, students + N, CompareStudents);
}

bool CompareStudents(const Student& a, const Student& b) { // ������� ��������� ��������
    double avgA = a.average(), avgB = b.average();
    if (avgA != avgB) return avgA > avgB; // �� ������� �����
    if (a.informatics != b.informatics) return a.informatics > b.informatics; // �� ������� � �����������
    return a.surname > b.surname; // �� �������� (��������)
}

bool BinarySearch(const Student* students, int N, const string& surname, double average, int informatics) { // �������� �����
    // ��������� ����� ������� ��� ������������� ��������
    int* indices = new int[N];
    for (int i = 0; i < N; ++i) indices[i] = i;

    // ������� ������� �� ������ ���������
    sort(indices, indices + N, [&students](int a, int b) {
        const Student& studentA = students[a], studentB = students[b];
        double avgA = studentA.average(), avgB = studentB.average();
        if (avgA != avgB) return avgA > avgB;
        if (studentA.informatics != studentB.informatics) return studentA.informatics > studentB.informatics;
        return studentA.surname > studentB.surname;
        });

    // ����� �� ��������� �������� ������
    bool found = false;
    for (int i = 0; i < N; ++i) {
        const Student& student = students[indices[i]];
        if (student.surname == surname && student.average() == average && student.informatics == informatics) {
            found = true;
            break;
        }
    }

    delete[] indices;  // ��������� ���'���
    return found;
}

/*
������� � 1:
 �������: ������
 ����: 2
 ������������ (0 - ����'����� �����, 1 - ����������, 2 - Գ����, 3 - ��������, 4 - �������): 0
 ������ � ������: 5
 ������ � ����������: 4
 ������ � �����������: 3

������� � 2:
 �������: ������
 ����: 3
 ������������ (0 - ����'����� �����, 1 - ����������, 2 - Գ����, 3 - ��������, 4 - �������): 1
 ������ � ������: 4
 ������ � ����������: 5
 ������ � �����������: 2

������� � 3:
 �������: �������
 ����: 1
 ������������ (0 - ����'����� �����, 1 - ����������, 2 - Գ����, 3 - ��������, 4 - �������): 2
 ������ � ������: 3
 ������ � ����������: 5
 ������ � �����������: 4
 */