#ifndef SETTINGQUANTITY_H
#define SETTINGQUANTITY_H

#include <QDialog>

namespace Ui {
class SettingQuantity;
}

class SettingQuantity : public QDialog
{
    Q_OBJECT

public:
    explicit SettingQuantity(QWidget *parent = 0);
    ~SettingQuantity();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SettingQuantity *ui;
};

#endif // SETTINGQUANTITY_H
