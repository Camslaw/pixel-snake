#include <iostream>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    std::cout << "Welcome to Pixel Snake!" << '\n';

    QApplication a(argc, argv);
    
    QMainWindow window;
    window.resize(900, 700);
    window.setWindowTitle("Pixel Snake");
    window.setStyleSheet("background-color: turquoise;");
    window.show();

    return a.exec();
}