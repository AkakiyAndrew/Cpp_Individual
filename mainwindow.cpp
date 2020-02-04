#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoggoods.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);

    QStringList names;
    names<<"Name"<<"Amount"<<"Price";
    ui->tableWidget->setHorizontalHeaderLabels(names);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addCat_clicked()
{
    QString catName;
    bool check;

    catName=QInputDialog::getText(this, "Enter name of new category", "Name: ", QLineEdit::Normal, "Category", &check);

    if(check&&!catName.isEmpty())
    {
        if(data.addCategory((char*)catName.toStdString().data())!=nullptr)
        {
            ui->catList->addItem(catName);
        }
        else
        {
            QMessageBox msg;
            msg.setText("Category "+catName+" already exist!");
            msg.exec();
        }
    }
}

void MainWindow::on_addSubcat_clicked()
{
    QString catName, subcatName;
    bool check;

    QListWidgetItem *item=ui->catList->currentItem();
    if(!(item==nullptr))
    {
        catName=ui->catList->currentItem()->text();


    subcatName=QInputDialog::getText(this, "Enter name of new subcategory", "Name: ", QLineEdit::Normal, "Subcategory", &check);

    if(check&&!catName.isEmpty())
    {
        if(data.addSubcategory((char*)subcatName.toStdString().data(), (char*)catName.toStdString().data())!=nullptr)
        {
            ui->subcatList->addItem(subcatName);
        }
        else
        {
            QMessageBox msg;
            msg.setText("Subcategory "+subcatName+" already exist!");
            msg.exec();
        }
    }
    }
    else
    {
        QMessageBox msg;
        msg.setText("You must select category from list!");
        msg.exec();
    }
}

void MainWindow::on_addGoods_clicked()
{
    int result, goodsAmount;
    QString goodsName, catName, subcatName;
    double goodsPrice;

    QListWidgetItem *item=ui->catList->currentItem();
    if(!(item==nullptr))
    {
        catName=ui->catList->currentItem()->text();
    }
    else
    {
        QMessageBox msg;
        msg.setText("You must select category from list!");
        msg.exec();
        return;
    }

    item=ui->subcatList->currentItem();
    if(!(item==nullptr))
    {
        subcatName=ui->subcatList->currentItem()->text();
    }
    else
    {
        QMessageBox msg;
        msg.setText("You must select subcategory from list!");
        msg.exec();
        return;
    }

    DialogGoods dialog(this);
    dialog.setWindowTitle("Goods name");
    result= dialog.exec();

    if(result== QDialog::Rejected) return;

    goodsAmount= dialog.amount();
    goodsName=dialog.name();
    goodsPrice=dialog.price();

    if(!(catName.isEmpty()&&subcatName.isEmpty()&&goodsName.isEmpty()))
    {
        if(data.addGoods(goodsAmount, goodsPrice, (char*)goodsName.toStdString().data(), (char*)subcatName.toStdString().data(), (char*)catName.toStdString().data()) !=nullptr)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(goodsName));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(QString::number(goodsAmount)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(QString::number(goodsPrice)));
        }
        else
        {
            QMessageBox msg;
            msg.setText("Goods "+goodsName+" already exist!");
            msg.exec();
        }
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionOpen_triggered()
{
    //удаление текущих элементов перед загрузкой новых:
    if(data.firstCategory!=nullptr)
    {
        for(int i = 0; i < ui->catList->count(); ++i)
        {
            QListWidgetItem* item = ui->catList->item(i);
            data.deleteCategory((char*)item->text().toStdString().data());
        }
    }
    this->data.numberOfCategories=0;

    //загрузка из файла:
    data.loadFromFile();

    //очистка списков:
    ui->catList->clear();
    ui->subcatList->clear();
    while(ui->tableWidget->rowCount()>0)
    {
        ui->tableWidget->removeRow(0);
    }

    //вывод категорий из файла в список:
    Category *link=data.firstCategory;
    if(link!=nullptr)
    {
        for(int i=0; i<data.numberOfCategories; i++)
        {
            ui->catList->addItem(link->getName());
            link=link->nextItem;
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    data.saveToFile();
}

void MainWindow::on_catList_itemDoubleClicked(QListWidgetItem *item)
{
    QString catName;
    bool check;

    catName=QInputDialog::getText(this, "Enter new name of category", "Name: ", QLineEdit::Normal, "Category", &check);

    if(check&&!catName.isEmpty())
    {
        for(int i = 0; i < ui->catList->count(); ++i)
        {
            QListWidgetItem* cat = ui->catList->item(i);
            if(cat->text()==catName)
            {
                QMessageBox msg;
                msg.setText("Category "+catName+" already exist!");
                msg.exec();
                return;
            }
        }
        data.findCategory((char*)item->text().toStdString().data())->setName((char*)catName.toStdString().data());
        item->setText(catName);
    }
}

void MainWindow::on_subcatList_itemDoubleClicked(QListWidgetItem *item)
{
    //Поправить для открытия параметров подкатегории
    QString catName;
    bool check;

    catName=QInputDialog::getText(this, "Enter new name of category", "Name: ", QLineEdit::Normal, "Category", &check);

    if(check&&!catName.isEmpty())
    {
        for(int i = 0; i < ui->catList->count(); ++i)
        {
            QListWidgetItem* cat = ui->catList->item(i);
            if(cat->text()==catName)
            {
                QMessageBox msg;
                msg.setText("Category "+catName+" already exist!");
                msg.exec();
                return;
            }
        }
        data.findCategory((char*)item->text().toStdString().data())->setName((char*)catName.toStdString().data());
        item->setText(catName);
    }
}

void MainWindow::on_ShowSubcats_clicked()
{
    QListWidgetItem *item=ui->catList->currentItem();
    if(item==nullptr)
    {
        QMessageBox msg;
        msg.setText("You must select category from list!");
        msg.exec();
        return;
    }
    ui->subcatList->clear();
    while(ui->tableWidget->rowCount()>0)
    {
        ui->tableWidget->removeRow(0);
    }
    Category *parent=data.findCategory((char*)item->text().toStdString().data());
    if(parent->numbersOfSubcategories>0)
    {
        Subcategory *link=parent->firstSubcategory;
        for(int i=0; i<parent->numbersOfSubcategories; i++)
        {
            ui->subcatList->addItem(link->getName());
            link=link->nextItem;
        }
    }
}

void MainWindow::on_showGoods_clicked()
{
    QString catName;
    QListWidgetItem *item=ui->subcatList->currentItem();
    if(item==nullptr)
    {
        QMessageBox msg;
        msg.setText("You must select subcategory from list!");
        msg.exec();
        return;
    }
    QListWidgetItem *cat=ui->catList->currentItem();
    if(!(cat==nullptr))
    {
        catName=ui->catList->currentItem()->text();
    }
    else
    {
        QMessageBox msg;
        msg.setText("You must select category from list!");
        msg.exec();
        return;
    }

    while(ui->tableWidget->rowCount()>0)
    {
        ui->tableWidget->removeRow(0);
    }

    Subcategory *parent=data.findSubcategory((char*)item->text().toStdString().data(), (char*)catName.toStdString().data());
    if(parent->numberOfGoods>0)
    {
        Goods *link=parent->firstGoods;
        for(int i=0; i<parent->numberOfGoods; i++)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(link->getName()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(QString::number(link->getAmountOfGoods())));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(QString::number(link->getPriceOfGoods())));

            link=link->nextItem;
        }
    }
}

void MainWindow::on_catDelete_clicked()
{
    QList<QListWidgetItem*> items = ui->catList->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        data.deleteCategory((char*)item->text().toStdString().data());
        delete ui->catList->takeItem(ui->catList->row(item));
    }
}

void MainWindow::on_subcatDelete_clicked()
{
    QListWidgetItem *parent=ui->catList->currentItem();
    if(parent==nullptr)
    {
        QMessageBox msg;
        msg.setText("You must select category from list!");
        msg.exec();
        return;
    }
    QList<QListWidgetItem*> items = ui->subcatList->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        data.deleteSubcategory((char*)item->text().toStdString().data(), (char*)parent->text().toStdString().data());
        delete ui->subcatList->takeItem(ui->subcatList->row(item));
    }
}

void MainWindow::on_goodsDelete_clicked()
{
    QString catName, subcatName, goodsName;

    QListWidgetItem *category=ui->catList->currentItem();
    if(category==nullptr)
    {
        QMessageBox msg;
        msg.setText("You must select category from list!");
        msg.exec();
        return;
    }
    else
    {
        catName=category->text();
    }

    QListWidgetItem *subcategory=ui->subcatList->currentItem();
    if(subcategory==nullptr)
    {
        QMessageBox msg;
        msg.setText("You must select subcategory from list!");
        msg.exec();
        return;
    }
    else
    {
        subcatName=subcategory->text();
    }

    goodsName=ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text();

    if(goodsName.size()!=0)
    {
        data.deleteGoods((char*)goodsName.toStdString().data(), (char*)subcatName.toStdString().data(), (char*)catName.toStdString().data());
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    }
    else
    {
        QMessageBox msg;
        msg.setText("You must select goods from table!");
        msg.exec();
        return;
    }
}
