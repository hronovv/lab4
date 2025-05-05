#include <QApplication>
#include "window.h"


int main(int argc, char* argv[]) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    QApplication a(argc, argv);
    auto* window = new Window();
    window->setWindowTitle("Vector, hopefully.");
    window->resize(kWindowSize, kWindowSize);
    window->show();
    return a.exec();
}
