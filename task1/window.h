#ifndef WINDOW_H
#define WINDOW_H
#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <chrono>
#include <sstream>
#include "QComboBox"
#include "QInputDialog"
#include "QLabel"
#include "QMessageBox"
#include "QString"
#include "binarysearch.h"
#include "bits/stdc++.h"
#include "heapsort.h"
#include "mergesort.h"
#include "quicksort.h"
constexpr int kNumIterations = 100;
constexpr int kValidSize = 100;
constexpr int kValueRange = 100;
constexpr int kWindowSize = 1600;
constexpr int kButtonWidth = 300;
constexpr int kButtonHeigth = 55;


class Window : public QWidget {
    Q_OBJECT

   public:
    Window();
    void SizeOpen();
    void SortAndDisplay();
    void FindElement();

   private:
    int size_ = 0;
    int target_ = 0;
    int* arr_original_;
};


#endif	//WINDOW_H
