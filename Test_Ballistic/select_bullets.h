#ifndef SELECT_BULLETS_H
#define SELECT_BULLETS_H

#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFile>
#include <QTextStream>
#include <mainwindow.h>
#include "lib_ballistic.h"
#include "Lib_Ballistic_global.h"

namespace Ui {
class Select_Bullets;
}

class Select_Bullets : public QDialog
{
    Q_OBJECT

public:
    explicit Select_Bullets(QWidget *parent = nullptr);
    ~Select_Bullets();


    int selected_row_number = 0,rowCount=0,colCount=5;
    bool ok_clicked = false;
    QList<QTableWidgetItem*> itemList;
    QString crrtxt="Riffle",Line,fromsecond_valvelocity,fromsecond_valbc,fromsecond_valkind,fromsecond_valweight,fromsecond_valbullet;

signals:
    void Cmbx_Select_Riffle_currentText();

public slots:
    void initTableWidget_Select();
    void on_tableWidget_Select_itemSelectionChanged();
    void on_Cmbx_Select_Riffle_currentTextChanged();
    void on_pushButton_Cancel_clicked();
    void on_pushButton_OK_clicked();
    void on_pushButtonAdd_clicked();
    void on_pushButton_Edit_clicked();
public:
    Ui::Select_Bullets *ui;

};

#endif // SELECT_BULLETS_H
