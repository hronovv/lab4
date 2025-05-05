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
#include "vector.h"
constexpr int kWindowSize = 1600;
constexpr int kWindowWidth = 200;
constexpr int kWindowHeigth = 55;
constexpr int kFieldWidth = 400;
constexpr int kFieldHeigtht = 55;


class Window : public QWidget {
    Q_OBJECT

   public:
    Window();
    void ShowCapacity();
    void ShowSize();
    void ShowMaxSize();
    void ShowEmpty();
    void Clear();
    void Reserve();
    void Resize();
    void PushBack();
    void PopBack();
    void Insert();
    void Erase();
    void PrintIntVector();
    void PrintPairVector();

   private:
    QTextEdit* firstElementEdit_;
    QTextEdit* secondElementEdit_;
    GoodVector<GoodPair<GoodVector<int>, GoodVector<GoodPair<int, double>>>>
        my_vector_;
};


#endif	//WINDOW_H
