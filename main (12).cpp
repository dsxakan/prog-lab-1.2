#include <iostream>
#include <stdexcept>

class DynArray {
private:
    int* mas; // Указатель на массив
    int size; // Размер массива

public:
    // Конструктор по умолчанию и с параметром
    DynArray(int sz = 8) {
        size = sz;
        mas = new int[size]; // Выделение памяти под массив
        for (int i = 0; i < size; ++i) {
            mas[i] = 0; // Инициализация массива нулями
        }
    }

    // Конструктор инициализации объекта с помощью значений из массива
    DynArray(int* P, int sz) {
        size = sz;
        mas = new int[size]; // Выделение памяти под массив
        for (int i = 0; i < size; ++i) {
            mas[i] = P[i]; // Копирование значений из переданного массива
        }
    }

    // Конструктор копирования
    DynArray(const DynArray& obj) {
        size = obj.size;
        mas = new int[size]; // Выделение памяти под массив
        for (int i = 0; i < size; ++i) {
            mas[i] = obj.mas[i]; // Копирование значений из объекта obj
        }
    }

    // Деструктор
    ~DynArray() {
        delete[] mas; // Освобождение памяти
    }

    // Оператор присвоения
    DynArray& operator=(const DynArray& obj) {
        if (this != &obj) {
            delete[] mas; // Освобождение памяти
            size = obj.size;
            mas = new int[size]; // Выделение памяти под массив
            for (int i = 0; i < size; ++i) {
                mas[i] = obj.mas[i]; // Копирование значений из объекта obj
            }
        }
        return *this;
    }

    // Перегрузка оператора + , который выполняет объединение массивов
    DynArray operator+(const DynArray& obj) {
        DynArray result(size + obj.size); // Создание нового объекта суммарного размера
        for (int i = 0; i < size; ++i) {
            result.mas[i] = mas[i]; // Копирование элементов текущего массива
        }
        for (int i = 0; i < obj.size; ++i) {
            result.mas[size + i] = obj.mas[i]; // Копирование элементов массива obj
        }
        return result;
    }

    // Перегрузка оператора [], который выполняет обращение к заданному элементу
    int& operator[](int ix) {
        if (ix < 0 || ix >= size) {
            throw std::out_of_range("Index out of range"); // Выброс исключения при выходе за границы массива
        }
        return mas[ix];
    }

    // Перегрузка потокового вывода
    friend std::ostream& operator<<(std::ostream& os, const DynArray& arr) {
        os << "[";
        for (int i = 0; i < arr.size; ++i) {
            os << arr.mas[i];
            if (i != arr.size - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};

int main() {
    try {
        // Тестирование конструктора по умолчанию и с параметром
        DynArray arr1; // Используется конструктор по умолчанию
        DynArray arr2(5); // Используется конструктор с параметром
        std::cout << "arr1: " << arr1 << std::endl;
        std::cout << "arr2: " << arr2 << std::endl;

        // Тестирование конструктора инициализации объекта с помощью значений из массива
        int initArray[] = {1, 2, 3, 4, 5};
        DynArray arr3(initArray, 5);
        std::cout << "arr3: " << arr3 << std::endl;

        // Тестирование конструктора копирования
        DynArray arr4 = arr3;
        std::cout << "arr4: " << arr4 << std::endl;

        // Тестирование оператора присвоения
        arr1 = arr3;
        std::cout << "arr1 after assignment: " << arr1 << std::endl;

        // Тестирование оператора +
        DynArray arr5 = arr2 + arr4;
        std::cout << "arr5 (arr2 + arr4): " << arr5 << std::endl;

        // Тестирование оператора []
        std::cout << "arr3[2]: " << arr3[2] << std::endl;
        arr3[2] = 10;
        std::cout << "arr3 after modification: " << arr3 << std::endl;

        // Тестирование исключительной ситуации при выходе за границы массива
        std::cout << "Trying to access arr3[10]: ";
        std::cout << arr3[10] << std::endl; // Вызовет исключение
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
