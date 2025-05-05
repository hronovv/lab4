#include "window.h"


Window::Window() {
    QString button_style = R"(
        QPushButton {
            background-color: #ffffff;
            border: 2px solid #000000;
            color: #000000;
            padding: 10px 20px;
            font-size: 17px;
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
        font-size: 17px;
        color: #FFFFFF;
    )";

    QString text_edit_style = R"(
        font-size: 14px;
        background-color: #f9f9f9;
        color: #000000;
        border: 2px solid #000000;
        border-radius: 5px;
    )";

    auto* overall_layout = new QVBoxLayout(this);

    auto* text_info = new QLabel(this);
    text_info->setText(
        "This program works with the "
        "vector\nvector<pair<vector<int>,vector<pair<int,double>>>>");
    text_info->setStyleSheet(text_style);
    overall_layout->addWidget(text_info);

    auto* button_layout = new QVBoxLayout();

    auto* capacity_button = new QPushButton("Show capacity", this);
    capacity_button->setFixedSize(kWindowWidth, kWindowHeigth);
    capacity_button->setStyleSheet(button_style);
    connect(capacity_button, &QPushButton::clicked, this,
            &Window::ShowCapacity);
    button_layout->addWidget(capacity_button);

    auto* size_button = new QPushButton("Show size", this);
    size_button->setFixedSize(kWindowWidth, kWindowHeigth);
    size_button->setStyleSheet(button_style);
    connect(size_button, &QPushButton::clicked, this, &Window::ShowSize);
    button_layout->addWidget(size_button);

    auto* max_size_button = new QPushButton("Show max size", this);
    max_size_button->setFixedSize(kWindowWidth, kWindowHeigth);
    max_size_button->setStyleSheet(button_style);
    connect(max_size_button, &QPushButton::clicked, this, &Window::ShowMaxSize);
    button_layout->addWidget(max_size_button);

    auto* empty_button = new QPushButton("Show if empty", this);
    empty_button->setFixedSize(kWindowWidth, kWindowHeigth);
    empty_button->setStyleSheet(button_style);
    connect(empty_button, &QPushButton::clicked, this, &Window::ShowEmpty);
    button_layout->addWidget(empty_button);

    auto* clear_button = new QPushButton("Clear vector", this);
    clear_button->setFixedSize(kWindowWidth, kWindowHeigth);
    clear_button->setStyleSheet(button_style);
    connect(clear_button, &QPushButton::clicked, this, &Window::Clear);
    button_layout->addWidget(clear_button);

    auto* reserve_button = new QPushButton("Reserve capacity", this);
    reserve_button->setFixedSize(kWindowWidth, kWindowHeigth);
    reserve_button->setStyleSheet(button_style);
    connect(reserve_button, &QPushButton::clicked, this, &Window::Reserve);
    button_layout->addWidget(reserve_button);

    auto* resize_button = new QPushButton("Resize vector", this);
    resize_button->setFixedSize(kWindowWidth, kWindowHeigth);
    resize_button->setStyleSheet(button_style);
    connect(resize_button, &QPushButton::clicked, this, &Window::Resize);
    button_layout->addWidget(resize_button);

    auto* push_back_button = new QPushButton("Push back", this);
    push_back_button->setFixedSize(kWindowWidth, kWindowHeigth);
    push_back_button->setStyleSheet(button_style);
    connect(push_back_button, &QPushButton::clicked, this, &Window::PushBack);
    button_layout->addWidget(push_back_button);

    auto* pop_back_button = new QPushButton("Pop back", this);
    pop_back_button->setFixedSize(kWindowWidth, kWindowHeigth);
    pop_back_button->setStyleSheet(button_style);
    connect(pop_back_button, &QPushButton::clicked, this, &Window::PopBack);
    button_layout->addWidget(pop_back_button);

    auto* insert_button = new QPushButton("Insert", this);
    insert_button->setFixedSize(kWindowWidth, kWindowHeigth);
    insert_button->setStyleSheet(button_style);
    connect(insert_button, &QPushButton::clicked, this, &Window::Insert);
    button_layout->addWidget(insert_button);

    auto* erase_button = new QPushButton("Erase", this);
    erase_button->setFixedSize(kWindowWidth, kWindowHeigth);
    erase_button->setStyleSheet(button_style);
    connect(erase_button, &QPushButton::clicked, this, &Window::Erase);
    button_layout->addWidget(erase_button);

    auto* first_elem_layout = new QVBoxLayout();
    auto* first_element_button = new QPushButton("1st element of pair", this);
    first_element_button->setFixedSize(kFieldWidth, kFieldHeigtht);
    first_element_button->setStyleSheet(button_style);
    connect(first_element_button, &QPushButton::clicked, this,
            &Window::PrintIntVector);
    first_elem_layout->addWidget(first_element_button);

    firstElementEdit_ = new QTextEdit(this);
    firstElementEdit_->setStyleSheet(text_edit_style);
    firstElementEdit_->setReadOnly(true);
    first_elem_layout->addWidget(firstElementEdit_);

    auto* second_elem_layout = new QVBoxLayout();
    auto* second_element_button = new QPushButton("2nd element of pair", this);
    second_element_button->setFixedSize(kFieldWidth, kFieldHeigtht);
    second_element_button->setStyleSheet(button_style);
    connect(second_element_button, &QPushButton::clicked, this,
            &Window::PrintPairVector);
    second_elem_layout->addWidget(second_element_button);

    secondElementEdit_ = new QTextEdit(this);
    secondElementEdit_->setStyleSheet(text_edit_style);
    secondElementEdit_->setReadOnly(true);
    second_elem_layout->addWidget(secondElementEdit_);

    auto* main_layout = new QHBoxLayout();
    main_layout->addLayout(button_layout);
    main_layout->addLayout(first_elem_layout);
    main_layout->addLayout(second_elem_layout);

    overall_layout->addLayout(main_layout);

    setLayout(overall_layout);
}

void Window::ShowCapacity() {
    QMessageBox::information(
        this, "Capacity",
        "Capacity of the vector is " + QString::number(my_vector_.capacity()));
}

void Window::ShowSize() {
    QMessageBox::information(
        this, "Size",
        "Size of the vector is " + QString::number(my_vector_.size()));
}

void Window::ShowMaxSize() {
    QMessageBox::information(
        this, "Max Size",
        "Max size of the vector is " + QString::number(my_vector_.max_size()));
}

void Window::ShowEmpty() {
    if (my_vector_.empty()) {
        QMessageBox::information(this, "Empty", "Your vector is empty");
    } else {
        QMessageBox::information(this, "Not Empty", "Your vector isn't empty");
    }
}

void Window::Clear() {
    my_vector_.clear();
    QMessageBox::information(this, "Success", "Your vector is cleared");
}

void Window::Reserve() {
    bool ok = false;
    unsigned long long new_capacity = -1;
    QString number = QInputDialog::getText(
        nullptr, "New Capacity", "Input new capacity:", QLineEdit::Normal, "",
        &ok);
    if (ok && !number.isEmpty()) {
        bool n_ok;
        new_capacity = number.toULongLong(&n_ok);
        if (n_ok && new_capacity >= my_vector_.size()) {
            my_vector_.reserve(new_capacity);
            QMessageBox::information(this, "Success", "New capacity is set");
        } else {
            QMessageBox::warning(nullptr, "Error", "Incorrect capacity");
        }
    } else {
        QMessageBox::warning(nullptr, "Error", "Input proper capacity");
    }
}

void Window::Resize() {
    bool ok = false;
    unsigned long long new_size = -1;
    QString number = QInputDialog::getText(
        nullptr, "New Size", "Input new size:", QLineEdit::Normal, "", &ok);
    if (ok && !number.isEmpty()) {
        bool n_ok;
        new_size = number.toULongLong(&n_ok);


        if (n_ok && new_size >= 0) {
            my_vector_.resize(new_size);
            QMessageBox::information(this, "Success", "New size is set");
        } else {
            QMessageBox::warning(nullptr, "Error", "Incorrect size");
        }
    } else {
        QMessageBox::warning(nullptr, "Error", "Input proper size");
    }
}

void Window::PushBack() {
    GoodVector<int> temp_int_vector;
    GoodVector<GoodPair<int, double>> temp_pair_vector;
    bool ok;
    QString int_input = QInputDialog::getText(
        this, "Input Integer Vector",
        "Input integer numbers, separated by the comma:", QLineEdit::Normal, "",
        &ok);
    if (!ok || int_input.isEmpty()) {
        QMessageBox::warning(this, "Error",
                             "Invalid input for integer vector.");
        return;
    }
    QStringList int_strings = int_input.split(',', Qt::SkipEmptyParts);


    for (const auto& str : int_strings) {
        bool valid;
        int value = str.trimmed().toInt(&valid);
        if (valid) {
            temp_int_vector.push_back(value);
        } else {
            QMessageBox::warning(this, "Error",
                                 "Invalid value in integer vector.");
            return;
        }
    }
    QString pair_input =
        QInputDialog::getText(this, "Input Pair Vector",
                              "Input pairs (int,double), separated by the "
                              "comma, for example: 1,2.5,3,4.0",
                              QLineEdit::Normal, "", &ok);
    if (!ok || pair_input.isEmpty()) {
        QMessageBox::warning(this, "Error", "Invalid input for pair vector");
        return;
    }
    QStringList pair_strings = pair_input.split(',', Qt::SkipEmptyParts);
    for (int i = 0; i < pair_strings.size(); i += 2) {
        if (i + 1 >= pair_strings.size()) {
            QMessageBox::warning(
                this, "Error",
                "Invalid input, the size doesn't match pairs total size.");
            return;
        }
        QString int_string = pair_strings[i].trimmed();
        QString double_string = pair_strings[i + 1].trimmed();
        bool valid_int, valid_double;
        int int_value = int_string.toInt(&valid_int);
        double double_value = double_string.toDouble(&valid_double);


        if (valid_int && valid_double) {
            temp_pair_vector.push_back({int_value, double_value});
        } else {
            QMessageBox::warning(this, "Error",
                                 "Invalid values in pair (int,double)");
            return;
        }
    }
    GoodPair<GoodVector<int>, GoodVector<GoodPair<int, double>>> temp_pair = {
        temp_int_vector, temp_pair_vector};
    my_vector_.push_back(temp_pair);
    QMessageBox::information(
        this, "Success", "Element has been successfully added to the vector!");
}

void Window::PopBack() {
    if (!my_vector_.empty()) {
        my_vector_.pop_back();
        QMessageBox::information(
            this, "Success",
            "Last element has been successfully deleted from the vector!");
    } else {
        QMessageBox::warning(this, "Error",
                             "Calling pop-back for empty vector is UB");
    }
}

void Window::Insert() {
    bool ok_pos = false;
    unsigned long long position = -1;
    QString number = QInputDialog::getText(
        nullptr, "Insert", "Input position:", QLineEdit::Normal, "", &ok_pos);
    if (ok_pos && !number.isEmpty()) {
        bool n_ok;
        position = number.toULongLong(&n_ok);
        if (n_ok && position >= 0 &&
            ((my_vector_.size() > 0 && position <= my_vector_.size() ||
              (my_vector_.size() == 0 && position == my_vector_.size())))) {
            QMessageBox::information(this, "Success", "Position is set");
        } else {
            QMessageBox::warning(nullptr, "Error", "Incorrect position");
            return;
        }
    } else {
        QMessageBox::warning(nullptr, "Error", "Input proper position");
        return;
    }
    GoodVector<int> temp_int_vector;
    GoodVector<GoodPair<int, double>> temp_pair_vector;
    bool ok;
    QString int_input = QInputDialog::getText(
        this, "Input Integer Vector",
        "Input integer numbers, separated by the comma:", QLineEdit::Normal, "",
        &ok);
    if (!ok || int_input.isEmpty()) {
        QMessageBox::warning(this, "Error",
                             "Invalid input for integer vector.");
        return;
    }
    QStringList int_strings = int_input.split(',', Qt::SkipEmptyParts);


    for (const auto& str : int_strings) {
        bool valid;
        int value = str.trimmed().toInt(&valid);
        if (valid) {
            temp_int_vector.push_back(value);
        } else {
            QMessageBox::warning(this, "Error",
                                 "Invalid value in integer vector.");
            return;
        }
    }
    QString pair_input =
        QInputDialog::getText(this, "Input Pair Vector",
                              "Input pairs (int,double), separated by the "
                              "comma, for example: 1,2.5,3,4.0",
                              QLineEdit::Normal, "", &ok);
    if (!ok || pair_input.isEmpty()) {
        QMessageBox::warning(this, "Error", "Invalid input for pair vector");
        return;
    }
    QStringList pair_strings = pair_input.split(',', Qt::SkipEmptyParts);
    for (int i = 0; i < pair_strings.size(); i += 2) {
        if (i + 1 >= pair_strings.size()) {
            QMessageBox::warning(
                this, "Error",
                "Invalid input, the size doesn't match pairs total size.");
            return;
        }
        QString int_string = pair_strings[i].trimmed();
        QString double_string = pair_strings[i + 1].trimmed();
        bool valid_int, valid_double;
        int int_value = int_string.toInt(&valid_int);
        double double_value = double_string.toDouble(&valid_double);


        if (valid_int && valid_double) {
            temp_pair_vector.push_back({int_value, double_value});
        } else {
            QMessageBox::warning(this, "Error",
                                 "Invalid values in pair (int,double)");
            return;
        }
    }
    GoodPair<GoodVector<int>, GoodVector<GoodPair<int, double>>> temp_pair = {
        temp_int_vector, temp_pair_vector};
    my_vector_.insert(my_vector_.cbegin() + position, temp_pair);
    QMessageBox::information(
        this, "Success",
        "Element has been successfully inserted in the vector!");
}

void Window::Erase() {
    bool ok_beg = false, ok_end = false;
    unsigned long long position_beg = -1, position_end = -1;
    QString number = QInputDialog::getText(
        nullptr, "Erase", "Input start position:", QLineEdit::Normal, "",
        &ok_beg);
    if (ok_beg && !number.isEmpty()) {
        bool n_ok;
        position_beg = number.toULongLong(&n_ok);
        if (n_ok && position_beg >= 0 && position_beg < my_vector_.size()) {
            QMessageBox::information(this, "Success", "Start position is set");
        } else {
            QMessageBox::warning(nullptr, "Error", "Incorrect start position");
            return;
        }
    } else {
        QMessageBox::warning(nullptr, "Error", "Input proper start position");
        return;
    }
    QString number_end = QInputDialog::getText(
        nullptr, "Erase", "Input end position:", QLineEdit::Normal, "",
        &ok_end);
    if (ok_end && !number.isEmpty()) {
        bool n_ok;
        position_end = number_end.toULongLong(&n_ok);
        if (n_ok && position_end >= 0 && position_end <= my_vector_.size()) {
            QMessageBox::information(this, "Success", "End position is set");
        } else {
            QMessageBox::warning(nullptr, "Error", "Incorrect end position");
            return;
        }
    } else {
        QMessageBox::warning(nullptr, "Error", "Input proper end position");
        return;
    }


    if (position_beg > position_end) {
        QMessageBox::warning(
            nullptr, "Error",
            "Beginning position can't be larger than end position");
        return;
    } else {
        my_vector_.erase(my_vector_.begin() + position_beg,
                         my_vector_.begin() + position_end);
        QMessageBox::information(
            this, "Success",
            "Elements has been successfully erased from the vector!");
    }
}

void Window::PrintIntVector() {
    firstElementEdit_->clear();
    firstElementEdit_->append("Int Vector: ");
    QString output;
    for (size_t i = 0; i < my_vector_.size(); ++i) {
        output = "";
        const auto& pair = my_vector_[i];
        const auto& int_vector = pair.first;

        for (size_t j = 0; j < int_vector.size(); ++j) {
            output += QString::number(int_vector[j]) + " ";
        }
        firstElementEdit_->append(output.trimmed());
    }
}

void Window::PrintPairVector() {
    secondElementEdit_->clear();
    secondElementEdit_->append("Pair Vector: ");
    QString output;
    for (size_t i = 0; i < my_vector_.size(); ++i) {
        output = "";
        const auto& pair = my_vector_[i];
        const auto& pair_vector = pair.second;
        for (size_t j = 0; j < pair_vector.size(); ++j) {
            output += "(" + QString::number(pair_vector[j].first) + ", " +
                      QString::number(pair_vector[j].second) + ") ";
        }
        secondElementEdit_->append(output.trimmed());
    }
}
