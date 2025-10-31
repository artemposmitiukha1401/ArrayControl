#include <iostream>

constexpr int MIN_RAND = -50;
constexpr int MAX_RAND = 150;

int GenerateInt() { return rand() % (MAX_RAND - MIN_RAND + 1) + MIN_RAND; }

void PrintArr(int*& arr, const int SIZE) {
    try {
        if (arr == nullptr) throw std::invalid_argument("Arr is nullptr");
        if (SIZE <= 0) throw std::invalid_argument("Invalid size");

        for (int i = 0; i < SIZE; i++)
            std::cout << arr[i] << " | ";
        std::cout << std::endl;
    }
    catch (const std::exception &e) {std::cerr << e.what() << std::endl; }
}

void FillArr(int*& arr, const int SIZE) {
    try {
        if (arr == nullptr) throw std::invalid_argument("Arr is nullptr");
        if (SIZE <= 0) throw std::invalid_argument("Invalid size");

        for (int i = 0; i < SIZE; i++)
            arr[i] = GenerateInt();

    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Resize(int*& arr, int &SIZE, const int grow, bool outer_resize) {
    try {
        if (arr == nullptr) throw std::invalid_argument("Arr is nullptr");
        if (SIZE <= 0) throw std::invalid_argument("Invalid size");

        const int NEW_SIZE = SIZE + grow;
        int* buffer_arr = new int[NEW_SIZE] {0};
        if (outer_resize) {
            for (int i = 0; i < SIZE; i++)
                buffer_arr[i] = arr[i];
        }
        else {
            for (int i = grow; i < NEW_SIZE; i++)
                buffer_arr[i] = arr[i - grow];
        }

        delete[] arr;
        arr = buffer_arr;
        SIZE = NEW_SIZE;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

}

void PushBack(int*& arr, int& SIZE, const int value) {
    try {
        if (arr == nullptr) throw std::invalid_argument("Arr is nullptr");
        if (SIZE <= 0) throw std::invalid_argument("Invalid size");

        Resize(arr, SIZE, 1, true);
        arr[SIZE - 1] = value;

    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
void PushStart(int*& arr, int& SIZE, const int value) {
    try {
        if (arr == nullptr) throw std::invalid_argument("Arr is nullptr");
        if (SIZE <= 0) throw std::invalid_argument("Invalid size");

        Resize(arr, SIZE, 1, false);
        arr[0] = value;

    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
void Insert(int*& arr, int& SIZE, const int value, const int index) {
    try {
        if (arr == nullptr) throw std::invalid_argument("Arr is nullptr");
        if (SIZE <= 0) throw std::invalid_argument("Invalid size");
        if (index >= SIZE || index < 0) throw std::invalid_argument("Invalid index");

        Resize(arr, SIZE, 1, true);
        for (int i = SIZE; i > index; i--) arr[i] = arr[i - 1];
        arr[index] = value;


    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
void Concatenate(int*& initial_arr, int& INITIAL_SIZE, int*& additional_arr, int ADDITIONAL_SIZE) {
   try {
       if (initial_arr == nullptr || additional_arr == nullptr) throw std::invalid_argument("Arr is nullptr");
       if (INITIAL_SIZE <= 0 || ADDITIONAL_SIZE <= 0) throw std::invalid_argument("Invalid size");
       const int INITIAL_SIZE_COPY = INITIAL_SIZE;
       Resize(initial_arr, INITIAL_SIZE, ADDITIONAL_SIZE, true);
       for (int i = INITIAL_SIZE_COPY, j = 0; i < INITIAL_SIZE; i++) initial_arr[i] = additional_arr[j++];

   }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
void RemoveSubarr(int*& arr, int& SIZE, int*& subarr, const int SUBARR_SIZE) {
    try {
        if (arr == nullptr || subarr == nullptr) throw std::invalid_argument("Arr is nullptr");
        if (SIZE <= 0 || SUBARR_SIZE <= 0) throw std::invalid_argument("Invalid size");

        int start_index = -1, end_index = -1;
        for (int i = 0; i <= SIZE - SUBARR_SIZE; i++) {
            bool isFound = true;
            for (int j = 0; j < SUBARR_SIZE; j++) {
                if (arr[i + j] != subarr[j]) {
                    isFound = false;
                    break;
                }
            }
            if (isFound) {
                start_index = i;
                end_index = i + SUBARR_SIZE - 1;
                break;
            }
        }
        if (start_index == -1) {
            throw std::runtime_error("No subarray was fount");
        }
        const int NEW_SIZE = SIZE - SUBARR_SIZE;
        int* buffer_arr = new int[NEW_SIZE];
        for (int i = 0; i < start_index; i++) buffer_arr[i] = arr[i];
        for (int i = start_index; i < NEW_SIZE; i++) buffer_arr[i] = arr[i + SUBARR_SIZE];

        delete[] arr;
        arr = buffer_arr;
        SIZE = NEW_SIZE;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
void Menu() {
    std::cout << "<==== ARRAY CONTROL ====>\n";
    std::cout << "[1]> Initialize;"
    << "\n[2]> Print;"
    << "\n[3]> Add to the end;"
    << "\n[4]> Add to the start;"
    << "\n[5]> Insert;"
    << "\n[6]> Concatenate"
    << "\n[7]> Remove last element;"
    << "\n[8]> Remove first element"
    << "\n[9]> Remove subarray\n";
}
int main() {
    //  Написать следующие функции для работы с динамическим массивом:
    //  Базовый уровень:
    // 1. Инициализация случ числами
    // 2. Вывод на экран
    // 3. Добавление новго элемента в конец массива, значение передается как параметр
    // Продвинутый уровень:
    // Все функции базового уровня + новые:
    // 4. Добавление элемента в начало массива
    // 5. Добавление элемента по индексу(индекс и новое значение передаем как параметр)
    // 6. Добавление массива в массив
    // 8. Удаление последнего элемента
    // 9. удаление первого элемента
    // 10 удаление подмассива(например 1 2 3 4 5 6 7, удаляем 3 4 5) результат 1 2 6 7
    srand(time(nullptr));
    int choice;
    int size = 20;
    int value = 0;
    int position = 0;

    int concatenate_size = 0;
    int* additional_arr = nullptr;

    int* arr = new int[size]{};
    while (true) {
        PrintArr(arr, size);
        Menu();
        std::cout << "> "; std::cin >> choice;
        switch (choice) {
            case 1:
                FillArr(arr, size);
                break;
            case 2:
                PrintArr(arr, size);
                break;
            case 3:
                std::cout << "Enter value to add: "; std::cin >> value;
                PushBack(arr, size, value);
                break;
            case 4:
                std::cout << "Enter value to add: "; std::cin >> value;
                PushStart(arr, size, value);
                break;
            case 5:
                std::cout << "Enter value to insert: ";std::cin >> value;
                std::cout << "Enter position of the value: "; std::cin >> position;
                Insert(arr, size, value, position);
                break;
            case 6:
                std::cout << "Enter size of the subarray: "; std::cin >> concatenate_size;
                additional_arr = new int[concatenate_size];
                for (int i = 0; i < concatenate_size; i++) {
                    std::cout << "Ente value [" << i << "]: "; std::cin >> additional_arr[i];
                }
                Concatenate(arr, size, additional_arr, concatenate_size);
                delete[] additional_arr;
                break;
            case 7:
                Resize(arr, size, -1, true);
                break;
            case 8:
                Resize(arr, size, -1, false);
                break;
            case 9:
                std::cout << "Enter size of the subarray: "; std::cin >> concatenate_size;
                additional_arr = new int[concatenate_size];
                for (int i = 0; i < concatenate_size; i++) {
                    std::cout << "Ente value [" << i << "]: "; std::cin >> additional_arr[i];
                }
                RemoveSubarr(arr, size, additional_arr, concatenate_size);
                delete[] additional_arr;
                break;
            case -1:
                return 0;
            default:
                std::cerr << "Invalid chocie\n";
                break;
        }
    }
    delete[] arr;
    delete[] additional_arr;
    return 0;
}