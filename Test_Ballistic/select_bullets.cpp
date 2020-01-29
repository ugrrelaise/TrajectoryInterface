#include "select_bullets.h"
#include "ui_select_bullets.h"
#include "add_bullet.h"
#include "ui_add_bullet.h"
#include "mainwindow.h"
#include<QDebug>
#include<QDir>
#include<QFile>
#include<QLabel>
#include<QList>
#include<QTableWidget>
#include<QTableWidgetItem>
Select_Bullets::Select_Bullets(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Select_Bullets)
{
    ui->setupUi(this);
    ui->tableWidget_Select->setSelectionBehavior(QAbstractItemView::SelectRows);
    Select_Bullets::initTableWidget_Select();

    //Select_Bullets::on_tableWidget_Select_itemActivated(QTableWidgetItem *item);
    connect(this,SIGNAL(Cmbx_Select_Riffle_currentText()),this, SLOT(initTableWidget_Select()));
    //connect(this,SIGNAL(Cmbx_Select_Riffle_currentText()),this, SLOT(on_tableWidget_Select_itemSelectionChanged()));

}

Select_Bullets::~Select_Bullets()
{
    delete ui;
}

void Select_Bullets::on_Cmbx_Select_Riffle_currentTextChanged()
{
    emit Cmbx_Select_Riffle_currentText();
}


void Select_Bullets::initTableWidget_Select()
{


    crrtxt = ui->Cmbx_Select_Riffle->currentText();


    QFile file("C:/Users/pc/Desktop/Test_Ballistic/"+crrtxt+".txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&file);

    ui->tableWidget_Select->clear();
    ui->tableWidget_Select->setRowCount(0);
    int rowCount=0,colCount=5;
    ui->tableWidget_Select->setHorizontalHeaderItem(0, new QTableWidgetItem("Kind"));
    ui->tableWidget_Select->setHorizontalHeaderItem(1, new QTableWidgetItem("Weight (gr)"));
    ui->tableWidget_Select->setHorizontalHeaderItem(2, new QTableWidgetItem("Bullet"));
    ui->tableWidget_Select->setHorizontalHeaderItem(3, new QTableWidgetItem("Velocity"));
    ui->tableWidget_Select->setHorizontalHeaderItem(4, new QTableWidgetItem("BC"));
    while (!in.atEnd())
    {
        ui->tableWidget_Select->insertRow(rowCount);
        ui->tableWidget_Select->verticalHeader()->hide();
        QStringList List;
        Line = in.readLine();
        List = Line.split('\t');

        for( int j = 0; j < colCount; j++ ) {
           QTableWidgetItem *item = new QTableWidgetItem(List[j]);
           item->setTextAlignment(Qt::AlignCenter);
           ui->tableWidget_Select->setItem( rowCount, j, item);
           }
        rowCount++;
    }

    selected_row_number = 0;
    ui->tableWidget_Select->selectRow(0);

    for (int col = 0 ; col < 5 ; col++)
    {
        itemList << ui->tableWidget_Select->item(selected_row_number, col);
    }

    ui->lineEdit->setText(itemList[0]->text());
    ui->lineEdit_2->setText(itemList[1]->text());
    ui->lineEdit_3->setText(itemList[2]->text());
    ui->lineEdit_4->setText(itemList[3]->text());
    ui->lineEdit_5->setText(itemList[4]->text());
}

void Select_Bullets::on_tableWidget_Select_itemSelectionChanged()
{
    selected_row_number = ui->tableWidget_Select->currentRow();
    itemList.clear();

    for (int col = 0 ; col < 5 ; col++)
    {
        itemList << ui->tableWidget_Select->item(selected_row_number, col);
    }

    ui->lineEdit->setText(itemList[0]->text());
    ui->lineEdit_2->setText(itemList[1]->text());
    ui->lineEdit_3->setText(itemList[2]->text());
    ui->lineEdit_4->setText(itemList[3]->text());
    ui->lineEdit_5->setText(itemList[4]->text());

    crrtxt = ui->Cmbx_Select_Riffle->currentText();
}


void Select_Bullets::on_pushButton_Cancel_clicked()
{
    this->close();
}


void Select_Bullets::on_pushButton_OK_clicked()
{
    ok_clicked = true;
    /* first three variable unused for now */
    fromsecond_valkind      = itemList[0]->text();   //1
    fromsecond_valweight    = itemList[1]->text();   //2
    fromsecond_valbullet    = itemList[2]->text();   //3
    fromsecond_valvelocity  = itemList[3]->text();
    fromsecond_valbc        = itemList[4]->text();

    this->close();
}



void Select_Bullets::on_pushButtonAdd_clicked()
{

    Add_Bullet new_bullet;
    new_bullet.setModal(true);
    new_bullet.show();
    new_bullet.crrrtxt = ui->Cmbx_Select_Riffle->currentText();
    new_bullet.edit_ok_clicked = 0;
    new_bullet.exec();

    initTableWidget_Select();
    //if(slct.ok_clicked)
    //{
    /*ui->LineEdit_MuzzleVelocity_2->setText(slct.fromsecond_valvelocity);
    ui->LineEdit_BalisticsCoefficient_2->setText(slct.fromsecond_valbc);
    on_LineEdit_MuzzleVelocity_2_textEdited(slct.fromsecond_valvelocity);
    on_LineEdit_MuzzleVelocity_2_returnPressed();
    on_LineEdit_BalisticsCoefficient_2_textEdited(slct.fromsecond_valbc);
    on_LineEdit_BalisticsCoefficient_2_returnPressed();*/
    //}
}

void Select_Bullets::on_pushButton_Edit_clicked()
{
    Add_Bullet new_bullet2;
    new_bullet2.setModal(true);
    new_bullet2.show();
    new_bullet2.crrrtxt = ui->Cmbx_Select_Riffle->currentText();
    new_bullet2.edit_ok_clicked = 1;
    new_bullet2.ui->lineEdit_Kind->setText(itemList[0]->text());
    new_bullet2.ui->lineEdit_Weight->setText(itemList[1]->text());
    new_bullet2.ui->lineEdit_Bullet->setText(itemList[2]->text());
    new_bullet2.ui->lineEdit_Velocity->setText(itemList[3]->text());
    new_bullet2.ui->lineEdit_BC->setText(itemList[4]->text());

    new_bullet2.str1 = itemList[0]->text();
    new_bullet2.str2 = itemList[1]->text();
    new_bullet2.str3 = itemList[2]->text();
    new_bullet2.str4 = itemList[3]->text();
    new_bullet2.str5 = itemList[4]->text();
    new_bullet2.exec();

    initTableWidget_Select();
}
