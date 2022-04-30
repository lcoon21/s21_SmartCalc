#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphwindow.h"

extern "C"{
#include "s21_calculation.h"
#include "s21_stack.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GraphWindow *window2;

private slots:
    void digit_numbers();
    void on_pushButton_TOCHKA_clicked();
    void on_pushButton_EQUAL_clicked();
    void operations();
    void functions();
    void on_pushButton_DELETE_clicked();
    void on_pushButton_X_clicked();
};
#endif // MAINWINDOW_H
