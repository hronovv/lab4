#include "window.h"


Window::Window() {
    QString button_style = R"(
        QPushButton {
            background-color: #ffffff;
            border: 2px solid #000000;
            color: #000000;
            padding: 10px 20px;
            font-size: 20px;
            margin: 5px;
            border-radius: 5px;
        }
        QPushButton:hover {
            background-color: #f0f0f0;
        }
        QPushButton:pressed {
            background-color: #d0d0d0;
            color: #333333;
        }
    )";

    QString text_style = R"(
        font-size: 16px;
        color: #FFFFFF;
    )";
    auto* text_info = new QLabel(this);
    text_info->setText(
        "Эта программа выводит скорость работы quicksort, mergesort, "
        "heapsort.\nМассив заполняется случайным образом числами от -50 до "
        "50.\nСортировка бует повторяться 100 раз для более корректного "
        "измерения времени.\nРазмер массива лучше вводить >=100");
    text_info->setStyleSheet(text_style);

    auto* open_button = new QPushButton("Ввести размер массива: ", this);
    open_button->setFixedSize(kButtonWidth, kButtonHeigth);
    open_button->setStyleSheet(button_style);
    connect(open_button, &QPushButton::clicked, this, &Window::SizeOpen);

    auto* sort_button = new QPushButton("Отсортировать: ", this);
    sort_button->setFixedSize(kButtonWidth, kButtonHeigth);
    sort_button->setStyleSheet(button_style);
    connect(sort_button, &QPushButton::clicked, this, &Window::SortAndDisplay);

    auto* find_button = new QPushButton("Найти элемент в массиве: ", this);
    find_button->setFixedSize(kButtonWidth, kButtonHeigth);
    find_button->setStyleSheet(button_style);
    connect(find_button, &QPushButton::clicked, this, &Window::FindElement);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(text_info);
    layout->addWidget(open_button);
    layout->addWidget(sort_button);
    layout->addWidget(find_button);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setLayout(layout);
}

void Window::SizeOpen() {
    bool ok = false;
    QString number = QInputDialog::getText(
        nullptr, "", "Введите размер массива:", QLineEdit::Normal, "", &ok);
    if (ok && !number.isEmpty()) {
        bool n_ok;
        size_ = number.toInt(&n_ok);


        if (n_ok && size_ > 0 && size_ < kValidSize) {
            QMessageBox::warning(
                nullptr, "Ошибка",
                "Введи размер побольше, я очень быстро сортирую!");
        } else if (n_ok && size_ >= kValidSize) {
            QMessageBox::information(this, "Успех", "Массив успешно создан");
            arr_original_ = new int[size_];
            std::generate(arr_original_, arr_original_ + size_, []() {
                return (std::rand() % kValueRange) - (kValueRange / 2);
            });
            for (int i = 0; i < size_; i++) {
                cout << arr_original_[i] << " ";
            }
        } else {
            QMessageBox::warning(
                nullptr, "Ошибка",
                "Введите целое положительное число с учетом диапазона");
        }
    } else {
        QMessageBox::warning(nullptr, "Ошибка",
                             "Введите целое положительное число");
    }
}

void Window::SortAndDisplay() {


    if (size_ >= kValidSize) {
        long long total_duration_quick_sort = 0, total_duration_mergesort = 0,
                  total_duration_heap_sort = 0;
        for (int iter = 0; iter < kNumIterations; ++iter) {
            int* arr = new int[size_];
            std::copy(arr_original_, arr_original_ + size_, arr);
            auto start = std::chrono::high_resolution_clock::now();
            quickSort(arr, 0, size_ - 1);
            auto end = std::chrono::high_resolution_clock::now();
            total_duration_quick_sort +=
                std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                      start)
                    .count();
            delete[] arr;
        }
        for (int iter = 0; iter < kNumIterations; ++iter) {
            int* arr = new int[size_];
            std::copy(arr_original_, arr_original_ + size_, arr);
            auto start = std::chrono::high_resolution_clock::now();
            mergeSort(arr, 0, size_ - 1);
            auto end = std::chrono::high_resolution_clock::now();
            total_duration_mergesort +=
                std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                      start)
                    .count();
            delete[] arr;
        }
        for (int iter = 0; iter < kNumIterations; ++iter) {
            int* arr = new int[size_];
            std::copy(arr_original_, arr_original_ + size_, arr);
            auto start = std::chrono::high_resolution_clock::now();
            heapSort(arr, size_);
            auto end = std::chrono::high_resolution_clock::now();
            total_duration_heap_sort +=
                std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                      start)
                    .count();
            delete[] arr;
        }
        QString info =
            "Среднее время выполнения quicksort: " +
            QString::number(total_duration_quick_sort / kNumIterations) +
            "mcs" + "\nСреднее время выполнения mergesort: " +
            QString::number(total_duration_mergesort / kNumIterations) + "mcs" +
            "\nСреднее время выполнения heapsort: " +
            QString::number(total_duration_heap_sort / kNumIterations) + "mcs";
        QMessageBox::information(this, "Результаты", info);
    } else {
        QMessageBox::warning(
            nullptr, "Ошибка",
            "Введи нормальный и не слишком маленький размер массива!");
    }
}

void Window::FindElement() {


    if (size_ >= kValidSize) {
        bool ok = false;
        QString number = QInputDialog::getText(
            nullptr, "", "Введите размер массива:", QLineEdit::Normal, "", &ok);
        if (ok && !number.isEmpty()) {
            bool n_ok;
            target_ = number.toInt(&n_ok);
            if (n_ok) {
                int* arr_for_binary_search = new int[size_];
                std::copy(arr_original_, arr_original_ + size_,
                          arr_for_binary_search);
                quickSort(arr_for_binary_search, 0, size_ - 1);
                int searched_number_index =
                    binarySearch(arr_for_binary_search, target_, size_);
                if (searched_number_index == -1) {
                    QMessageBox::information(this, "Результаты",
                                             "Такого элемента нет в массиве");
                } else {
                    QMessageBox::information(
                        this, "Результаты",
                        "Индекс элемента " + QString::number(target_) + " - " +
                            QString::number(searched_number_index));
                }
            }
        } else {
            QMessageBox::warning(nullptr, "Ошибка",
                                 "Введите число, которое хотите найти!");
        }
    } else {
        QMessageBox::warning(
            nullptr, "Ошибка",
            "Введи нормальный и не слишком маленький размер массива!");
    }
}
