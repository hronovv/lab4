#ifndef WINDOW_H
#define WINDOW_H
#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <sstream>
#include "QComboBox"
#include "QInputDialog"
#include "QLabel"
#include "QMessageBox"
#include "QString"
#include "bits/stdc++.h"
#include "median.h"
#include "quicksort.h"
constexpr int kWidth = 300;
constexpr int kButtonHeigth = 55;
constexpr int kFieldHeigth = 600;
constexpr int kWindowSize = 1600;
constexpr int kValueRange = 100;


class Window : public QWidget {
    Q_OBJECT

   public:
    Window();
    void SizeOpen();
    void OutputSequence();

   private:
    QTextEdit* original_field_;
    QTextEdit* sequence_field_;
    int size_ = 0;
    int target_ = 0;
    int* arr_original_;
};


#endif	//WINDOW_H
