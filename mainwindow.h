#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include "System.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addCat_clicked();

    void on_ShowSubcats_clicked();

    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_addSubcat_clicked();

    void on_addGoods_clicked();

    void on_catList_itemDoubleClicked(QListWidgetItem *item);

    void on_subcatList_itemDoubleClicked(QListWidgetItem *item);

    void on_showGoods_clicked();

    void on_catDelete_clicked();

    void on_subcatDelete_clicked();

    void on_goodsDelete_clicked();

private:
    Ui::MainWindow *ui;
    System data;
};

#endif // MAINWINDOW_H
