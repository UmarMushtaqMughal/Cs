
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data.cpp"
#include <fstream>
#include <sstream>
#include <QString>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveInventoryToFile(const string &filename);
    void loadInventoryFromFile(const string &filename);
    Inventory inventory;

private slots:
    void on_OptionCB_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_AddPB_clicked();

    void on_RemovePB_clicked();

    void on_LoadPB_clicked();

    void on_SavePB_clicked();

    void on_SalePB_clicked();

private:
    Ui::MainWindow *ui;
    QStatusBar *statusBar;
};

#endif // MAINWINDOW_H
