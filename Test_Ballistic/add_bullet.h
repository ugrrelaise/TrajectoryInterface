#ifndef ADD_BULLET_H
#define ADD_BULLET_H

#include <QDialog>
#include "select_bullets.h"
#include "ui_select_bullets.h"
namespace Ui {
class Add_Bullet;
}

class Add_Bullet : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Bullet(QWidget *parent = nullptr);
    ~Add_Bullet();

    Ui::Add_Bullet *ui;

    QList<QTableWidgetItem*> itemList;
    QString crrrtxt;
    int edit_ok_clicked = 0;

    QString str1,str2,str3,str4,str5;
public slots:
    void on_buttonBox_OK_clicked();
    void on_buttonBox_Cancel_clicked();

};

#endif // ADD_BULLET_H
