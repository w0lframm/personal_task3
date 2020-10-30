#include <iostream>
#include <locale.h>
#include <assert.h>
#include <limits.h>
#include <fstream>

using std::cin;
using std::cout;

int iInputTest(const std::string& sPrompt);
int iSizeTest(const std::string& sPrompt);
unsigned int GetNumAliquot(int* pArray, size_t nSize, int aliquot);
int* GenerateRandomArray(size_t nSize);
bool LoadArrayFromFile(const char* pszFileName, int*& pFileArray, size_t& nSize);

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Задание 14. В массиве целых чисел найти количество элементов, которые делятся на заданное число без остатка\n";
    std::string func_result = "Количество элементов массива, которые делятся на заданное число без остатка: ";
    
    int cArray[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    const size_t cSize = sizeof(cArray) / sizeof(cArray[0]);
    int aliquot = iInputTest("Введите число для определения количества кратных ему элементов массива");

    cout << "1) Массив констант:\n";
    cout << func_result << GetNumAliquot(cArray, cSize, aliquot) << "\n\n";
    

    cout << "2) Динамический массив случайных элементов\n";

    size_t rSize = iSizeTest("Введите количество элементов массива");
    int* rArray = GenerateRandomArray(rSize);

    if (rArray) {
        cout << func_result << GetNumAliquot(rArray, rSize, aliquot) << "\n\n";
        delete[] rArray;
        rArray = nullptr;
    }
    else {
        cout << "Ошибка!";
    }

    int* pFileArray = nullptr;
    size_t nSize = 0;

    cout << "3) Массив загружен из файла\n";

    if (LoadArrayFromFile("fff.txt", pFileArray, nSize)) {
        cout << func_result << GetNumAliquot(pFileArray, nSize, aliquot) << "\n\n";

        delete pFileArray;
        pFileArray = nullptr;
    }
    else {
        cout << "Ошибка загрузки массива из файла :( \n";
    }

    int* pFileArray_2 = nullptr;

    cout << "4) Массив загружен из файла\n";

    if (LoadArrayFromFile("fff2.txt", pFileArray_2, nSize)) {
        cout << func_result << GetNumAliquot(pFileArray_2, nSize, aliquot) << "\n\n";

        delete pFileArray_2;
        pFileArray_2 = nullptr;
    }
    else {
        cout << "Ошибка загрузки массива из файла :( ";
    }
}

int iInputTest(const std::string& sPrompt)
{
    std::cout << sPrompt << ":\n";
    bool correct_input = false;
    int myInput = 0;
    while (correct_input == false) {
        cin >> myInput;
        if (!cin) {
            cout << "Ошибка ввода! Повторите попытку: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            assert(cin);
            continue;
        }
        correct_input = true;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return myInput;
}

int iSizeTest(const std::string& sPrompt)
{
    std::cout << sPrompt << ":\n";
    bool correct_input = false;
    int mySize = 0;
    while (correct_input == false) {
        cin >> mySize;
        if (!cin) {
            cout << "Ошибка ввода! Повторите попытку: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            assert(cin);
            continue;
        }
        if (mySize <= 0) {
            cout << "Введённое число должно быть положительным! Повторите попытку: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            assert(cin);
            continue;
        }
        correct_input = true;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return mySize;
}

unsigned int GetNumAliquot(int* pArray, size_t nSize, int aliquot)
{
    int num_of_aliquot = 0;

    for (int i = 0; i < nSize; i++) {
        if (pArray[i] % aliquot == 0) {
            num_of_aliquot++;
        }
    }
    return num_of_aliquot;
}

int* GenerateRandomArray(size_t nSize)
{
    int* rArray = new int[nSize];
    if (rArray) {
        for (int i = 0; i < nSize; i++) {
            rArray[i] = rand();
        }
    }
    return rArray;
}

bool LoadArrayFromFile(const char* pszFileName, int*& pFileArray, size_t& nSize)
{
    pFileArray = nullptr;
    nSize = 0;

    std::ifstream fin;
    fin.open(pszFileName, std::ios::in);
    if (fin) {
        fin >> nSize;
        if (fin) {
            try {
                pFileArray = new int[nSize];
                if (pFileArray) {
                    for (int i = 0; i < nSize; i++) {
                        fin >> pFileArray[i];
                        if (fin.fail()) {
                            std::cout << "Ошибка чтения элемента массива [" << i << "]\n";
                            delete[] pFileArray;
                            pFileArray = nullptr;
                            nSize = 0;
                            break;
                        }
                    }
                }
                else {
                    std::cout << "Не могу выделить " << nSize << " элементов типа int\n";
                }
            }
            catch (...) {
                // Allocation failed
                std::cout << "Исключение: Не могу выделить " << nSize << " элементов типа int\n";
            }
        }
        else {
            std::cout << "Ошибка чтения размера массива из файла\n";
        }
    }
    else {
        std::cout << "Не могу открыть файл " << pszFileName << std::endl;
    }
    return (pFileArray != nullptr);
}