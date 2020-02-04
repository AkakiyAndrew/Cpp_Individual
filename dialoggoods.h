#ifndef DIALOGGOODS_H
#define DIALOGGOODS_H

#include <QDialog>

namespace Ui {
class DialogGoods;
}

class DialogGoods : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGoods(QWidget *parent = nullptr);
    ~DialogGoods();
    QString name() const;
    int amount() const;
    double price() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DialogGoods *ui;
};

#endif // DIALOGGOODS_H
