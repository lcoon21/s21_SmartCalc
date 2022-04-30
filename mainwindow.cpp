#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    window2 = new GraphWindow(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_LEFT_SKOBKA, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_RIGHT_SKOBKA, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_MINUS, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_PLUS, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_MUL, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_DIVIDE, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_MOD, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_POW, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_SIN, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_ASIN, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_COS, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_ACOS, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_TAN, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_ATAN, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_LN, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_SQRT, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_LOG, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_DELETE, SIGNAL(clicked()), this, SLOT(on_pushButton_DELETE_clicked()));

//    connect(ui->pushButton_EQUAL, SIGNAL(clicked()), this, SLOT(on_pushButton_EQUAL_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_numbers()
{
    QPushButton *button = (QPushButton *)sender();


    QString new_label = ui->result_show->text() + button->text();


    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_TOCHKA_clicked()
{
    if (!(ui->result_show->text().endsWith('.')))
        ui->result_show->setText(ui->result_show->text() + ".");
}


void MainWindow::on_pushButton_EQUAL_clicked()
{
    char* str = new char(ui->result_show->text().length());
    QByteArray barr = ui->result_show->text().toLatin1();
    strlcpy(str, barr, ui->result_show->text().length() + 1);

    if (check(str) == 0) {
        ui->result_show->setText("Invalid Input");
    } else if (ui->result_show->text().contains("x")) {
        window2->on_to_draw_button_clicked(str);
        window2->show();
    } else {
        double result = readStr(str, 0.0);

        QString numberResult = QString::number(result, 'g', 15);
        ui->result_show->setText(numberResult);
    }
    delete(str);
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton *)sender();

    QString new_label;

    new_label = ui->result_show->text();

    if (button->text() == "÷" && !(ui->result_show->text().endsWith("÷")) && !(ui->result_show->text().endsWith("/"))) {
        new_label += "/";
    } else if (button->text() == "x" && !(ui->result_show->text().endsWith("x")) && !(ui->result_show->text().endsWith("*"))) {
        new_label += "*";
    } else if (button->text() == "+" && !(ui->result_show->text().endsWith("+"))) {
        new_label += "+";
    } else if (button->text() == "-" && !(ui->result_show->text().endsWith("-"))) {
        new_label += "-";
    } else if (button->text() == "^" && !(ui->result_show->text().endsWith("^"))) {
        new_label += "^";
    } else if (button->text() == "mod" && !(ui->result_show->text().endsWith("mod"))) {
        new_label += "mod";
    } else if (button->text() == "(") {
        new_label += "(";
    } else if (button->text() == ")") {
        new_label += ")";
    }

    ui->result_show->setText(new_label);
}

void MainWindow::functions()
{
    QPushButton *button = (QPushButton *)sender();

    QString new_label;

    new_label = ui->result_show->text() + button->text() + "(";

    ui->result_show->setText(new_label);

}



void MainWindow::on_pushButton_DELETE_clicked()
{
    ui->result_show->setText("");
}


void MainWindow::on_pushButton_X_clicked()
{

    QString new_label;

    if (!(ui->result_show->text().endsWith("x")))
        new_label = ui->result_show->text() + "x";

    ui->result_show->setText(new_label);
}

