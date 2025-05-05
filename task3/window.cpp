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
        font-size: 20px;
        color: #FFFFFF;
    )";

    QString text_edit_style = R"(
            font-size: 14px;
            background-color: #f9f9f9;
            color: #000000;
            border: 2px solid #000000; /* Черная рамка */
            border-radius: 5px; /* Немного закругленные углы */
        )";

    auto* text_info = new QLabel(this);
    text_info->setText(
        "Эта программа выводит медиану последовательности(массива).\nМассив "
        "заполняется случайным образом числами от -50 до 50.");
    text_info->setStyleSheet(text_style);

    auto* open_button = new QPushButton("Ввести размер массива: ", this);
    open_button->setFixedSize(kWidth, kButtonHeigth);
    open_button->setStyleSheet(button_style);
    connect(open_button, &QPushButton::clicked, this, &Window::SizeOpen);

    auto* median_button = new QPushButton("Вывести медиану", this);
    median_button->setFixedSize(kWidth, kButtonHeigth);
    median_button->setStyleSheet(button_style);
    connect(median_button, &QPushButton::clicked, this,
            &Window::OutputSequence);

    original_field_ = new QTextEdit(this);
    original_field_->setReadOnly(true);
    original_field_->setStyleSheet(text_edit_style);
    original_field_->setFixedSize(kWidth, kFieldHeigth);

    sequence_field_ = new QTextEdit(this);
    sequence_field_->setReadOnly(true);
    sequence_field_->setStyleSheet(text_edit_style);
    sequence_field_->setFixedSize(kWidth, kFieldHeigth);

    auto* button_layout = new QHBoxLayout();
    button_layout->addWidget(open_button);
    button_layout->addWidget(median_button);

    auto* field_layout = new QHBoxLayout();
    field_layout->addWidget(original_field_);
    field_layout->addWidget(sequence_field_);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(text_info);
    layout->addLayout(button_layout);
    layout->addLayout(field_layout);
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


        if (n_ok && size_ > 0) {
            QMessageBox::information(this, "Успех", "Размер установлен!");
            delete[] arr_original_;
            arr_original_ = new int[size_];
            std::generate(arr_original_, arr_original_ + size_, []() {
                return (std::rand() % kValueRange) - (kValueRange / 2);
            });
            original_field_->clear();
            sequence_field_->clear();
            for (int i = 0; i < size_; ++i) {
                original_field_->append(QString::number(arr_original_[i]));
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

void Window::OutputSequence() {


    if (size_ > 0) {
        sequence_field_->clear();
        std::vector<double> sequence;
        for (size_t i = 0; i < size_; i += 3) {
            std::vector<int> group;
            for (size_t j = i; j < i + 3 && j < size_; ++j) {
                group.push_back(arr_original_[j]);
            }
            double median = calculateMedian(group);
            sequence.push_back(median);
        }

        for (size_t i = 0; i < sequence.size(); ++i) {
            sequence_field_->append(QString::number(sequence[i]));
        }
    } else {
        QMessageBox::warning(nullptr, "Ошибка",
                             "Введите положительный размер массива!");
    }
}
