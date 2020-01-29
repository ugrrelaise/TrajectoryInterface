#include "add_bullet.h"
#include "ui_add_bullet.h"
#include "select_bullets.h"
#include "ui_select_bullets.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>
Add_Bullet::Add_Bullet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_Bullet)
{
    ui->setupUi(this);
}

Add_Bullet::~Add_Bullet()
{
    delete ui;
}

void Add_Bullet::on_buttonBox_OK_clicked()
{

    QString kind,weight,bullet,velocity,bc,drag_function;
    kind            = ui->lineEdit_Kind->displayText();
    weight          = ui->lineEdit_Weight->displayText();
    bullet          = ui->lineEdit_Bullet->displayText();
    velocity        = ui->lineEdit_Velocity->displayText();
    bc              = ui->lineEdit_BC->displayText();
    drag_function   = ui->comboBox_DragFunction->currentText();

    Select_Bullets selected;




    int offset;

    if(edit_ok_clicked == 0)
    {
    if(kind != "" && weight != "",bullet != "",velocity != "",bc != "" )
    {
    QFile file("C:/Users/pc/Desktop/Test_Ballistic/"+crrrtxt+".txt");
    if (!file.open(QFile::Append | QFile::Text)) return;
    else
    {
    QTextStream out(&file);
    out << "\n "+ kind + "\t" + weight + "\t" + bullet + "\t" + velocity + "\t" + bc;
    Select_Bullets slct;
    slct.initTableWidget_Select();
    }
    file.close();
    }
    else {QMessageBox::warning(this,"Warning","Please, fill all box, then add item");}
    }


    if(edit_ok_clicked == 1)
    {


    }




    this->close();
}

void Add_Bullet::on_buttonBox_Cancel_clicked()
{
    this->close();
}
