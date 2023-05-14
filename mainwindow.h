
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void sellItem();
private slots:
    void on_AddItem_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Load_clicked();

    void on_sellButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
