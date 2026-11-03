#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_7_1.rec/Lab_7_1.rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest71rec
{
    TEST_CLASS(UnitTest71rec)
    {
    public:

        TEST_METHOD(TestCalculate)
        {
            const int rowCount = 2;
            const int colCount = 2;
            int S = 0;
            int k = 0;

            int** q = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                q[i] = new int[colCount];

            // Заповнення тестовими значеннями:
            q[0][0] = 26; // парне і кратне 13 -> ВИКЛЮЧАЄТЬСЯ (не змінюється на 0, не додається)
            q[0][1] = 15; // непарне -> включається
            q[1][0] = 14; // парне, але НЕ кратне 13 -> включається
            q[1][1] = 11; // непарне -> включається

            Calculate(q, rowCount, colCount, S, k);

            // Перевірка результатів:
            Assert::AreEqual(3, k);               // Кількість елементів = 3 (15, 14, 11)
            Assert::AreEqual(40, S);              // Сума = 15 + 14 + 11 = 40
            Assert::AreEqual(26, q[0][0]);        // 26 не змінилося (не задовольняє критерій)
            Assert::AreEqual(0, q[0][1]);         // 15 замінено на 0

            // Звільнення пам'яті
            for (int i = 0; i < rowCount; i++)
                delete[] q[i];
            delete[] q;
        }
    };
}