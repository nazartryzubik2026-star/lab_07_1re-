// Lab_7_1_rec.cpp
// Лабораторна робота № 7.1.
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці (рекурсивний спосіб).
// Варіант 16
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Прототипи рекурсивних та допоміжних функцій
void Create(int** a, const int rowCount, const int colCount, const int Low, const int High);
void Print(int** a, const int rowCount, const int colCount);
void Sort(int** a, int rowCount, int colCount, int currentRow = 0);
void SwapRows(int** a, const int row1, const int row2, const int colCount);
void Calculate(int** a, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0);

int main() {
    srand((unsigned)time(NULL));

    int Low = 11;
    int High = 67;
    int rowCount = 7;
    int colCount = 5;

    // Виділення пам'яті для динамічного двовимірного масиву
    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    // Формування та виведення початкової матриці
    Create(a, rowCount, colCount, Low, High);
    cout << "Initial matrix A:" << endl;
    Print(a, rowCount, colCount);

    // Впорядкування рядків матриці (рекурсивний спосіб)
    Sort(a, rowCount, colCount, 0);
    cout << "Sorted matrix A:" << endl;
    Print(a, rowCount, colCount);

    // Обчислення суми та кількості елементів за критерієм (усі, крім парних кратних 13)
    int S = 0;
    int k = 0;
    Calculate(a, rowCount, colCount, S, k);

    cout << "Sum (S) = " << S << endl;
    cout << "Count (k) = " << k << endl;

    // Виведення модифікованої матриці (де елементи за критерієм замінено на 0)
    cout << "Modified matrix A (after replacement):" << endl;
    Print(a, rowCount, colCount);

    // Звільнення динамічної пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

// Формування матриці випадковими числами
void Create(int** a, const int rowCount, const int colCount, const int Low, const int High) {
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

// Виведення матриці на екран
void Print(int** a, const int rowCount, const int colCount) {
    cout << endl;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++)
            cout << setw(5) << a[i][j];
        cout << endl;
    }
    cout << endl;
}

// Рекурсивна функція сортування рядків 
void Sort(int** a, int rowCount, int colCount, int currentRow) {
    if (currentRow == rowCount - 1)
        return;

    for (int i = 0; i < rowCount - currentRow - 1; i++) {
        // Ключі впорядкування: ↓ ↓ ↓ (за спаданням для 1-го, 2-го та 3-го стовпчиків)
        if (a[i][0] < a[i + 1][0]) {
            SwapRows(a, i, i + 1, colCount);
        }
        else if (a[i][0] == a[i + 1][0] && a[i][1] < a[i + 1][1]) {
            SwapRows(a, i, i + 1, colCount);
        }
        else if (a[i][0] == a[i + 1][0] && a[i][1] == a[i + 1][1] && a[i][2] < a[i + 1][2]) {
            SwapRows(a, i, i + 1, colCount);
        }
    }
    Sort(a, rowCount, colCount, currentRow + 1);
}

// Обмін місцями двох рядків матриці
void SwapRows(int** a, const int row1, const int row2, const int colCount) {
    for (int j = 0; j < colCount; j++) {
        int temp = a[row1][j];
        a[row1][j] = a[row2][j];
        a[row2][j] = temp;
    }
}

// Рекурсивна функція обчислення суми, кількості та заміни елементів за критерієм
void Calculate(int** a, const int rowCount, const int colCount, int& S, int& k, int i, int j) {
    if (i == rowCount)
        return;

    // умова виконання: НЕ (парне AND кратне 13) -> !(a[i][j] % 2 == 0 && a[i][j] % 13 == 0)
    if (!(a[i][j] % 2 == 0 && a[i][j] % 13 == 0)) {
        S += a[i][j];
        k++;
        a[i][j] = 0;
    }

    if (j < colCount - 1)
        Calculate(a, rowCount, colCount, S, k, i, j + 1);
    else
        Calculate(a, rowCount, colCount, S, k, i + 1, 0);
}