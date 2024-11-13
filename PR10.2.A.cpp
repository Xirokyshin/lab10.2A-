#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>  // Для std::binary_search
#include <Windows.h>

using namespace std;

// Перелік спеціальностей
enum Specialization { COMPUTER_SCIENCE, MATHEMATICS, PHYSICS, ENGINEERING, BIOLOGY };
string specializationStr[] = { "Комп'ютерні науки", "Математика", "Фізика", "Інженерія", "Біологія" };

// Структура для представлення студента
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

// Функції для введення, виведення, сортування та обчислення середнього балу
void InputStudents(Student* students, int N);
void PrintStudents(const Student* students, int N);
void SortStudents(Student* students, int N);
bool CompareStudents(const Student& a, const Student& b);
bool BinarySearch(const Student* students, int N, const string& surname, double average, int informatics);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int numStudents;
    cout << "Введіть кількість студентів: ";
    cin >> numStudents;

    // Використовуємо масив фіксованої довжини
    Student* students = new Student[numStudents];

    int menuItem;
    do {
        cout << "\nМеню:\n";
        cout << "1 - Введення даних студентів\n";
        cout << "2 - Вивід даних студентів\n";
        cout << "3 - Фізичне сортування студентів\n";
        cout << "4 - Пошук студента\n";
        cout << "0 - Вихід\n";
        cout << "Виберіть дію: ";
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
            cout << "Список студентів відсортовано.\n";
            break;
        case 4:
        {
            string surname;
            double average;
            int informatics;
            cout << "Введіть прізвище студента: ";
            cin >> surname;
            cout << "Введіть середній бал: ";
            cin >> average;
            cout << "Введіть оцінку з інформатики: ";
            cin >> informatics;
            if (BinarySearch(students, numStudents, surname, average, informatics)) {
                cout << "Студента знайдено.\n";
            }
            else {
                cout << "Студента не знайдено.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Неправильний вибір. Спробуйте ще раз.\n";
        }
    } while (menuItem != 0);

    delete[] students;  // Звільнення пам'яті
    return 0;
}

void InputStudents(Student* students, int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":\n";
        cin.ignore();
        cout << " Прізвище: "; getline(cin, students[i].surname);
        cout << " Курс: "; cin >> students[i].course;
        cout << " Спеціальність (0 - Комп'ютерні науки, 1 - Математика, 2 - Фізика, 3 - Інженерія, 4 - Біологія): ";
        cin >> spec;
        students[i].specialization = static_cast<Specialization>(spec);
        cout << " Оцінка з фізики: "; cin >> students[i].physics;
        cout << " Оцінка з математики: "; cin >> students[i].mathematics;
        cout << " Оцінка з інформатики: "; cin >> students[i].informatics;
    }
}

void PrintStudents(const Student* students, int N) {
    cout << "=============================================================================================\n";
    cout << "| № | Прізвище         | Курс | Спеціальність           | Фізика | Математика | Інформатика |\n";
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

bool CompareStudents(const Student& a, const Student& b) { // Функція порівняння студентів
    double avgA = a.average(), avgB = b.average();
    if (avgA != avgB) return avgA > avgB; // За середнім балом
    if (a.informatics != b.informatics) return a.informatics > b.informatics; // За оцінкою з інформатики
    return a.surname > b.surname; // За прізвищем (спадання)
}

bool BinarySearch(const Student* students, int N, const string& surname, double average, int informatics) { // Бінарний пошук
    // Створюємо масив індексів для впорядкування студентів
    int* indices = new int[N];
    for (int i = 0; i < N; ++i) indices[i] = i;

    // Сортуємо індекси за трьома критеріями
    sort(indices, indices + N, [&students](int a, int b) {
        const Student& studentA = students[a], studentB = students[b];
        double avgA = studentA.average(), avgB = studentB.average();
        if (avgA != avgB) return avgA > avgB;
        if (studentA.informatics != studentB.informatics) return studentA.informatics > studentB.informatics;
        return studentA.surname > studentB.surname;
        });

    // Пошук за допомогою бінарного пошуку
    bool found = false;
    for (int i = 0; i < N; ++i) {
        const Student& student = students[indices[i]];
        if (student.surname == surname && student.average() == average && student.informatics == informatics) {
            found = true;
            break;
        }
    }

    delete[] indices;  // Звільняємо пам'ять
    return found;
}

/*
Студент № 1:
 Прізвище: Іванов
 Курс: 2
 Спеціальність (0 - Комп'ютерні науки, 1 - Математика, 2 - Фізика, 3 - Інженерія, 4 - Біологія): 0
 Оцінка з фізики: 5
 Оцінка з математики: 4
 Оцінка з інформатики: 3

Студент № 2:
 Прізвище: Петров
 Курс: 3
 Спеціальність (0 - Комп'ютерні науки, 1 - Математика, 2 - Фізика, 3 - Інженерія, 4 - Біологія): 1
 Оцінка з фізики: 4
 Оцінка з математики: 5
 Оцінка з інформатики: 2

Студент № 3:
 Прізвище: Сидоров
 Курс: 1
 Спеціальність (0 - Комп'ютерні науки, 1 - Математика, 2 - Фізика, 3 - Інженерія, 4 - Біологія): 2
 Оцінка з фізики: 3
 Оцінка з математики: 5
 Оцінка з інформатики: 4
 */