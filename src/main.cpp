#include <iostream>
#include <string>
#include <limits>
#include <windows.h>
#include <vector>

#include "Train.h"
#include "TextProcessor.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

int readInt(const string& prompt) {
    int num;
    cout << prompt;
    while (!(cin >> num)) {
        cout << "Ошибка: введите целое число. Повторите: ";
        clearInput();
    }
    clearInput();
    return num;
}

void runTrainTask() {
    int capacity = 2;
    int count = 0;
    Train* trains = new Train[capacity];

    cout << "\n--- Ввод поездов ---\n";
    int n = readInt("Сколько поездов вы хотите добавить? ");
    
    for (int i = 0; i < n; ++i) {
        cout << "\nПоезд " << (i + 1) << ":\n";
        if (count == capacity) {
            capacity *= 2;
            Train* newArr = new Train[capacity];
            for (int j = 0; j < count; ++j) newArr[j] = trains[j];
            delete[] trains;
            trains = newArr;
        }

        cin >> trains[count];
        count++;
    }

    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (trains[j].getDepartureTime() > trains[j + 1].getDepartureTime()) {
                Train temp = trains[j];
                trains[j] = trains[j + 1];
                trains[j + 1] = temp;
            }
        }
    }

    cout << "\n--- Все поезда (отсортированы по времени) ---\n";
    for (int i = 0; i < count; ++i) {
        cout << trains[i] << "\n";
    }

    string searchDest;
    cout << "\nВведите пункт назначения для поиска: ";
    cin >> searchDest;

    bool found = false;
    cout << "\nРезультаты поиска по направлению '" << searchDest << "':\n";
    for (int i = 0; i < count; ++i) {
        if (trains[i].getDestination() == searchDest) {
            cout << trains[i] << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Поездов в данном направлении не найдено.\n";
    }

    delete[] trains;
}

void runTextTask() {
    cout << "\n--- Обработка текста ---\n";
    string filename;
    cout << "Введите имя файла (например, data/input.txt): ";
    cin >> filename;

    int wordsCount = readInt("Введите количество слов в предложении для поиска: ");

    int result = TextProcessor::printSentencesWithWordCount(filename, wordsCount);
    
    if (result == -1) {
        cout << "Не удалось прочитать файл. Проверьте, что он существует.\n";
    } else if (result == 0) {
        cout << "Предложений с таким количеством слов не найдено.\n";
    } else {
        cout << "\nНайдено предложений: " << result << "\n";
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice;
    do {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
        cout << "1. Задание 1 (Работа с поездами)\n";
        cout << "2. Задание 2 (Обработка текста из файла)\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";

        cin >> choice;
        clearInput();

        switch (choice) {
            case 1: runTrainTask(); break;
            case 2: runTextTask(); break;
            case 0: cout << "Выход...\n"; break;
            default: cout << "Неверный пункт.\n"; break;
        }

        if (choice != 0) {
            cout << "\nНажмите Enter, чтобы продолжить...";
            cin.get();
        }

    } while (choice != 0);

    return 0;
}