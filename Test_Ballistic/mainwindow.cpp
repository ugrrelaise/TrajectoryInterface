#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib_ballistic.h"
#include "Lib_Ballistic_global.h"
#include <QString>


#include "AirDensity.h"
#include "select_bullets.h"
#include "ui_select_bullets.h"
#include <QMouseEvent>
#include <QStringList>
#include <QDebug>
#include <math.h>
#include <iostream>
#include <string>
#include "DragFunction.h"
#include "BallisticProjector.h"
#include "BallisticTrajectory.h"
#include "BulletCondition.h"
#include "Atmosphere.h"
#include "Gun.h"
#include "Kilinc2000.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);

    dragfunc_cmbx_index = ui->Cmbx_DragFunction_2->findText(QString::fromStdString(fpr_dragfunction));
    ui->Cmbx_DragFunction_2->setCurrentIndex(dragfunc_cmbx_index);
    ui->LineEdit_MuzzleVelocity_2->setText(QString::number(fpr_muzzle_velocity) + " m/sec");
    ui->LineEdit_BalisticsCoefficient_2->setText(QString::number(fpr_balcoefficient));
    ui->LineEdit_HeightofSight_2->setText(QString::number(fpr_heightofsight) + " cm");
    ui->LineEdit_GunElevation1_2->setText(QString::number(fpr_gunelevation1,'f',2));
    ui->LineEdit_GunElevation2_2->setText(QString::number(fpr_gunelevation1,'f',2));
    ui->LineEdit_AirTemperature_2->setText(QString::number(fpr_airtemperature,'f',1) + " °C");
    ui->LineEdit_AirPressure_2->setText(QString::number(fpr_airpressure) + " mmHg");
    ui->LineEdit_Humidity_2->setText(QString::number(fpr_humidity) + " %");
    ui->LineEdit_Altitude_2->setText(QString::number(fpr_altitude) + " m");
    ui->LineEdit_HeadWindSpeed_2->setText(QString::number(fpr_headwindspeed) + " km/h");
    ui->LineEdit_CrossWindSpeed_2->setText(QString::number(fpr_crosswindspeed) + " km/h");
    ui->LineEdit_GraphXEnd_2->setText(QString::number(fpr_graphXend) + " m");
    ui->LineEdit_Interval_2->setText(QString::number(fpr_step) + " m");
    ui->LineEdit_GridXm_2->setText(QString::number(fpr_gridxm) + " m");
    ui->LineEdit_TrajRange_2->setText(QString::number(fpr_traj_range) + " m");
    ui->LineEdit_Range2_2->setText(QString::number(fpr_range2) + " m");
    ui->LineEdit_Wall_2->setText(QString::number(fpr_wall) + " m");
    ui->LineEdit_AirTemperature_3->setText(QString::number(fpr_airtemperature,'f',1) + " °C");
    ui->LineEdit_AirPressure_3->setText(QString::number(fpr_airpressure) + " mmHg");
    ui->LineEdit_Humidity_3->setText(QString::number(fpr_humidity) + " %");
    ui->LineEdit_Altitude_3->setText(QString::number(fpr_altitude) + " m");
    ui->LineEdit_HeadWindSpeed_3->setText(QString::number(fpr_headwindspeed) + " km/h");
    ui->LineEdit_CrossWindSpeed_3->setText(QString::number(fpr_crosswindspeed) + " km/h");
    MainWindow::makePlot(delement_order);
    MainWindow::initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);





    value_TrajRange_edited = ui->LineEdit_TrajRange_2->displayText();
    TrajRange_edited = value_TrajRange_edited.split(' ');
    fpr_traj_range = TrajRange_edited[0].toInt();

    order= 18;
    delement_order[0] = TrajRange_edited[0].toDouble();
    delement_order[1] = order;





    makePlot(delement_order);


    // First values for first plotting

    /* add value_RatioofAirDensity */
    //this->value_Wall_edited = "2000";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{

}

void MainWindow::on_lineEdit_returnPressed()
{
   ui->lineEdit->setText(QString::number(libbb.Calculate()));
}

void MainWindow::on_pushButton_Select_2_clicked()
{
    Select_Bullets slct;
    slct.setModal(false);
    slct.show();
    slct.exec();

    if(slct.ok_clicked)
    {
    ui->LineEdit_MuzzleVelocity_2->setText(slct.fromsecond_valvelocity);
    ui->LineEdit_BalisticsCoefficient_2->setText(slct.fromsecond_valbc);
    on_LineEdit_MuzzleVelocity_2_textEdited(slct.fromsecond_valvelocity);
    on_LineEdit_MuzzleVelocity_2_returnPressed();
    on_LineEdit_BalisticsCoefficient_2_textEdited(slct.fromsecond_valbc);
    on_LineEdit_BalisticsCoefficient_2_returnPressed();
    }
}

void MainWindow::on_LineEdit_MuzzleVelocity_2_textEdited(const QString &arg1)
{
    value_muzzlevelocity_edited = arg1;
    if((value_muzzlevelocity_edited == "")){}else{
    muzzlevelocity_edited = value_muzzlevelocity_edited.split(' ');
    ui->LineEdit_MuzzleVelocity_2->setText(muzzlevelocity_edited[0]);
    order= 1;
    delement_order[0] = muzzlevelocity_edited[0].toDouble();
    delement_order[1] = order;
    fpr_muzzle_velocity   = muzzlevelocity_edited[0].toDouble();
    }
}

void MainWindow::on_LineEdit_MuzzleVelocity_2_returnPressed()
{
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_muzzlevelocity  = ui->LineEdit_MuzzleVelocity_2->displayText();
    muzzle_velocity       = value_muzzlevelocity.split('m');
    if(muzzle_velocity[0] == "" || muzzle_velocity[0] == "m" || muzzle_velocity[0] == "m/" || muzzle_velocity[0] == "m/s" || muzzle_velocity[0] == "m/s" || muzzle_velocity[0] == "m/se" ||  muzzle_velocity[0] == "m/sec") {ui->LineEdit_MuzzleVelocity_2->setText("1 m/sec");}
    else{ui->LineEdit_MuzzleVelocity_2->setText(muzzle_velocity[0] + " m/sec");}
}

void MainWindow::on_LineEdit_BalisticsCoefficient_2_textEdited(const QString &arg1)
{
    value_BalisticsCoefficient = arg1;
    if(value_BalisticsCoefficient == "" || value_BalisticsCoefficient == "0" || value_BalisticsCoefficient == "0." || value_BalisticsCoefficient == "0.0"){}else{
    ballisticcoefficient_edited = value_BalisticsCoefficient.split(' ');
    ui->LineEdit_BalisticsCoefficient_2->setText(ballisticcoefficient_edited[0]);
    order= 2;
    delement_order[0]  = ballisticcoefficient_edited[0].toDouble();
    delement_order[1]  = order;
    fpr_balcoefficient = ballisticcoefficient_edited[0].toDouble();
    }
}

void MainWindow::on_LineEdit_BalisticsCoefficient_2_returnPressed()
{
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);


    value_BalisticsCoefficient = ui->LineEdit_BalisticsCoefficient_2->displayText();
    if(value_BalisticsCoefficient == "") {ui->LineEdit_BalisticsCoefficient_2->setText("0.000");}
    else{ui->LineEdit_BalisticsCoefficient_2->setText(value_BalisticsCoefficient);}
}

void MainWindow::on_LineEdit_HeightofSight_2_textEdited(const QString &arg1)
{
    value_HeightofSight_edited = arg1;
    HeightofSight_edited = value_HeightofSight_edited.split(' ');
    ui->LineEdit_HeightofSight_2->setText(HeightofSight_edited[0]);
    order= 3;
    delement_order[0] = HeightofSight_edited[0].toDouble();
    delement_order[1] = order;
    fpr_heightofsight = HeightofSight_edited[0].toDouble();
}

void MainWindow::on_LineEdit_HeightofSight_2_returnPressed()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_HeightofSight = ui->LineEdit_HeightofSight_2->displayText();
    HeightofSight = value_HeightofSight.split(' ');
    if(HeightofSight[0] == "" || HeightofSight[0] == "c" || HeightofSight[0] == "cm") {ui->LineEdit_HeightofSight_2->setText("1.00 cm");}
    else{ui->LineEdit_HeightofSight_2->setText(HeightofSight[0] + " cm");}
}

void MainWindow::on_LineEdit_GunElevation1_2_textEdited(const QString &arg1)
{
    value_GunElevation1_edited = arg1;
    GunElevation1_edited = value_GunElevation1_edited.split(' ');
    ui->LineEdit_GunElevation1_2->setText(GunElevation1_edited[0]);
    order= 4;
    delement_order[0] = GunElevation1_edited[0].toDouble();
    delement_order[1] = order;
    fpr_gunelevation1 = GunElevation1_edited[0].toDouble();
}

void MainWindow::on_LineEdit_GunElevation1_2_returnPressed()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_GunElevation1 = ui->LineEdit_GunElevation1_2->displayText();
    if(value_GunElevation1 == "") {ui->LineEdit_GunElevation1_2->setText("0.00");}
    else{ui->LineEdit_GunElevation1_2->setText(QString::number(fpr_gunelevation1, 'f', 2));}
    ui->LineEdit_GunElevation2_2->setText(QString::number(fpr_gunelevation1, 'f', 2));
}

void MainWindow::on_LineEdit_GunElevation2_2_textEdited(const QString &arg1)
{
    value_GunElevation2 = arg1;
    order= 5;
    delement_order[0] = value_GunElevation2.toDouble();
    delement_order[1] = order;
    makePlot(delement_order);
}

void MainWindow::on_LineEdit_GunElevation2_2_returnPressed()
{
    /* do somethings */
    value_GunElevation2 = ui->LineEdit_GunElevation2_2->displayText();
    if(value_GunElevation2 == "") {ui->LineEdit_GunElevation2_2->setText("0.000");}
    else{ui->LineEdit_GunElevation2_2->setText((value_GunElevation2));}
}

void MainWindow::on_Cmbx_mindegmil_2_currentTextChanged(const QString &arg1)
{
    /* do somethings */
    QString a= arg1;
}

void MainWindow::on_LineEdit_AirTemperature_2_textEdited(const QString &arg1)
{
    value_AirTemperature_edited = arg1;
    AirTemperature_edited = value_AirTemperature_edited.split(' ');
    ui->LineEdit_AirTemperature_2->setText(AirTemperature_edited[0]);
    ui->LineEdit_AirTemperature_3->setText(AirTemperature_edited[0]);
    order= 6;
    delement_order[0] = AirTemperature_edited[0].toDouble();
    delement_order[1] = order;
    fpr_airtemperature = AirTemperature_edited[0].toDouble();
}

void MainWindow::on_LineEdit_AirTemperature_2_returnPressed()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_AirTemperature = ui->LineEdit_AirTemperature_2->displayText();
    AirTemperature = value_AirTemperature.split(' ');
    if(AirTemperature[0] == "°" ||AirTemperature[0] == "C") {ui->LineEdit_AirTemperature_2->setText("1.00 °C");}
    else{ui->LineEdit_AirTemperature_2->setText(QString::number(fpr_airtemperature,'f',1)+" °C");}
    if(AirTemperature[0] == "°" ||AirTemperature[0] == "C") {ui->LineEdit_AirTemperature_3->setText("1.00 °C");}
    else{ui->LineEdit_AirTemperature_3->setText(QString::number(fpr_airtemperature,'f',1)+" °C");}
}

void MainWindow::on_LineEdit_AirTemperature_3_textEdited(const QString &arg1)
{
    value_AirTemperature_edited = arg1;
    AirTemperature_edited = value_AirTemperature_edited.split(' ');
    ui->LineEdit_AirTemperature_2->setText(AirTemperature_edited[0]);
    ui->LineEdit_AirTemperature_3->setText(AirTemperature_edited[0]);
    order= 6;
    delement_order[0] = AirTemperature_edited[0].toDouble();
    delement_order[1] = order;
    fpr_airtemperature = AirTemperature_edited[0].toDouble();
}

void MainWindow::on_LineEdit_AirTemperature_3_returnPressed()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_AirTemperature = ui->LineEdit_AirTemperature_3->displayText();
    AirTemperature = value_AirTemperature.split(' ');
    if(AirTemperature[0] == "°" ||AirTemperature[0] == "C") {ui->LineEdit_AirTemperature_2->setText("1.00 °C");}
    else{ui->LineEdit_AirTemperature_2->setText(QString::number(fpr_airtemperature,'f',1)+" °C");}
    if(AirTemperature[0] == "°" ||AirTemperature[0] == "C") {ui->LineEdit_AirTemperature_3->setText("1.00 °C");}
    else{ui->LineEdit_AirTemperature_3->setText(QString::number(fpr_airtemperature,'f',1)+" °C");}
}

void MainWindow::on_LineEdit_AirPressure_2_textEdited(const QString &arg1)
{
    value_AirPressure_edited = arg1;
    if(value_AirPressure_edited == "") {} else {
    AirPressure_edited = value_AirPressure_edited.split(' ');
    ui->LineEdit_AirPressure_2->setText(AirPressure_edited[0]);
    ui->LineEdit_AirPressure_3->setText(AirPressure_edited[0]);
    order= 7;
    delement_order[0] = AirPressure_edited[0].toDouble();
    delement_order[1] = order;
    fpr_airpressure = AirPressure_edited[0].toDouble();
    }
}

void MainWindow::on_LineEdit_AirPressure_2_returnPressed()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_AirPressure = ui->LineEdit_AirPressure_2->displayText();
    AirPressure = value_AirPressure.split(' ');
    if(AirPressure[0] == "" || AirPressure[0] == "m" || AirPressure[0] == "mm" || AirPressure[0] == "mmH" || AirPressure[0] == "mmHg") {ui->LineEdit_AirPressure_2->setText("1.00 mmHg");}
    else{ui->LineEdit_AirPressure_2->setText(AirPressure[0] + " mmHg");}
    if(AirPressure[0] == "" || AirPressure[0] == "m" || AirPressure[0] == "mm" || AirPressure[0] == "mmH" || AirPressure[0] == "mmHg") {ui->LineEdit_AirPressure_3->setText("1.00 mmHg");}
    else{ui->LineEdit_AirPressure_3->setText(AirPressure[0] + " mmHg");}

}

void MainWindow::on_LineEdit_AirPressure_3_textEdited(const QString &arg1)
{
    value_AirPressure_edited = arg1;
    if(value_AirPressure_edited == "") {} else {
    AirPressure_edited = value_AirPressure_edited.split(' ');
    ui->LineEdit_AirPressure_2->setText(AirPressure_edited[0]);
    ui->LineEdit_AirPressure_3->setText(AirPressure_edited[0]);
    order= 7;
    delement_order[0] = AirPressure_edited[0].toDouble();
    delement_order[1] = order;
    fpr_airpressure = AirPressure_edited[0].toDouble();
    }
}

void MainWindow::on_LineEdit_AirPressure_3_returnPressed()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_AirPressure = ui->LineEdit_AirPressure_3->displayText();
    AirPressure = value_AirPressure.split(' ');
    if(AirPressure[0] == "" || AirPressure[0] == "m" || AirPressure[0] == "mm" || AirPressure[0] == "mmH" || AirPressure[0] == "mmHg") {ui->LineEdit_AirPressure_2->setText("1.00 mmHg");}
    else{ui->LineEdit_AirPressure_2->setText(AirPressure[0] + " mmHg");}
    if(AirPressure[0] == "" || AirPressure[0] == "m" || AirPressure[0] == "mm" || AirPressure[0] == "mmH" || AirPressure[0] == "mmHg") {ui->LineEdit_AirPressure_3->setText("1.00 mmHg");}
    else{ui->LineEdit_AirPressure_3->setText(AirPressure[0] + " mmHg");}
}


void MainWindow::on_LineEdit_Humidity_2_textEdited(const QString &arg1)
{
    value_Humidity_edited = arg1;
    Humidity_edited = value_Humidity_edited.split(' ');
    ui->LineEdit_Humidity_2->setText(Humidity_edited[0]);
    ui->LineEdit_Humidity_3->setText(Humidity_edited[0]);
    order= 8;
    delement_order[0] = Humidity_edited[0].toDouble();
    delement_order[1] = order;
    fpr_humidity = Humidity_edited[0].toDouble();

}

void MainWindow::on_LineEdit_Humidity_2_returnPressed()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_Humidity = ui->LineEdit_Humidity_2->displayText();
    Humidityy = value_Humidity.split(' ');
    if(Humidityy[0] == "" || Humidityy[0] == "%") {ui->LineEdit_Humidity_2->setText("1 %");}
    else{ui->LineEdit_Humidity_2->setText(Humidityy[0] + " %");}
    if(Humidityy[0] == "" || Humidityy[0] == "%") {ui->LineEdit_Humidity_3->setText("1 %");}
    else{ui->LineEdit_Humidity_3->setText(Humidityy[0] + " %");}
}

void MainWindow::on_LineEdit_Humidity_3_textEdited(const QString &arg1)
{
    value_Humidity_edited = arg1;
    Humidity_edited = value_Humidity_edited.split(' ');
    ui->LineEdit_Humidity_2->setText(Humidity_edited[0]);
    ui->LineEdit_Humidity_3->setText(Humidity_edited[0]);
    order= 8;
    delement_order[0] = Humidity_edited[0].toDouble();
    delement_order[1] = order;
    fpr_humidity = Humidity_edited[0].toDouble();
}

void MainWindow::on_LineEdit_Humidity_3_returnPressed()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_Humidity = ui->LineEdit_Humidity_3->displayText();
    Humidityy = value_Humidity.split(' ');
    if(Humidityy[0] == "" || Humidityy[0] == "%") {ui->LineEdit_Humidity_2->setText("1 %");}
    else{ui->LineEdit_Humidity_2->setText(Humidityy[0] + " %");}
    if(Humidityy[0] == "" || Humidityy[0] == "%") {ui->LineEdit_Humidity_3->setText("1 %");}
    else{ui->LineEdit_Humidity_3->setText(Humidityy[0] + " %");}
}


void MainWindow::on_LineEdit_Altitude_2_textEdited(const QString &arg1)
{
    value_Altitude_edited = arg1;
    Altitude_edited = value_Altitude_edited.split(' ');
    ui->LineEdit_Altitude_2->setText(Altitude_edited[0]);
    ui->LineEdit_Altitude_3->setText(Altitude_edited[0]);
    order= 9;
    delement_order[0] = Altitude_edited[0].toDouble();
    delement_order[1] = order;
    fpr_altitude = Altitude_edited[0].toDouble();

}

void MainWindow::on_LineEdit_Altitude_2_returnPressed()
{
    /*** changement of air temperature and air pressure ***/
    if(ui->LineEdit_Altitude_2->displayText() == "" || ui->LineEdit_Altitude_2->displayText() == "1" || ui->LineEdit_Altitude_2->displayText() == "2" || ui->LineEdit_Altitude_2->displayText() == "3" )
    {
    fpr_airpressure = 750;
    fpr_airtemperature = 15;
    ui->LineEdit_AirPressure_2->setText(QString::number(fpr_airpressure));
    ui->LineEdit_AirTemperature_2->setText(QString::number(fpr_airtemperature));
    on_LineEdit_AirPressure_2_returnPressed();
    on_LineEdit_AirTemperature_2_returnPressed();
    }

    fpr_airpressure = fpr_airpressure - round((fpr_altitude / 11));
    fpr_airtemperature = fpr_airtemperature - ((fpr_altitude / 100) * 0.5);
    ui->LineEdit_AirPressure_2->setText(QString::number(fpr_airpressure));
    on_LineEdit_AirPressure_2_returnPressed();
    ui->LineEdit_AirTemperature_2->setText(QString::number(fpr_airtemperature, 'f', 1));
    on_LineEdit_AirTemperature_2_returnPressed();


    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    /*** end changement of air pressure ***/
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_Altitude = ui->LineEdit_Altitude_2->displayText();
    Altitudee = value_Altitude.split(' ');
    if(Altitudee[0] == "" || Altitudee[0] == "m") {ui->LineEdit_Altitude_2->setText("1 m");}
    else{ui->LineEdit_Altitude_2->setText(Altitudee[0] + " m");}
    if(Altitudee[0] == "" || Altitudee[0] == "m") {ui->LineEdit_Altitude_3->setText("1 m");}
    else{ui->LineEdit_Altitude_3->setText(Altitudee[0] + " m");}
}

void MainWindow::on_LineEdit_Altitude_3_textEdited(const QString &arg1)
{
    value_Altitude_edited = arg1;
    Altitude_edited = value_Altitude_edited.split(' ');
    ui->LineEdit_Altitude_2->setText(Altitude_edited[0]);
    ui->LineEdit_Altitude_3->setText(Altitude_edited[0]);
    order= 9;
    delement_order[0] = Altitude_edited[0].toDouble();
    delement_order[1] = order;
    fpr_altitude = Altitude_edited[0].toDouble();
}

void MainWindow::on_LineEdit_Altitude_3_returnPressed()
{
    /*** changement of air temperature and air pressure ***/
    if(ui->LineEdit_Altitude_3->displayText() == "" || ui->LineEdit_Altitude_3->displayText() == "1" || ui->LineEdit_Altitude_3->displayText() == "2" || ui->LineEdit_Altitude_3->displayText() == "3" )
    {
    fpr_airpressure = 750;
    fpr_airtemperature = 15;
    ui->LineEdit_AirPressure_3->setText(QString::number(fpr_airpressure));
    ui->LineEdit_AirTemperature_3->setText(QString::number(fpr_airtemperature));
    on_LineEdit_AirPressure_3_returnPressed();
    on_LineEdit_AirTemperature_3_returnPressed();
    }

    fpr_airpressure = fpr_airpressure - round((fpr_altitude / 11));
    fpr_airtemperature = fpr_airtemperature - ((fpr_altitude / 100) * 0.5);
    ui->LineEdit_AirPressure_3->setText(QString::number(fpr_airpressure));
    on_LineEdit_AirPressure_3_returnPressed();
    ui->LineEdit_AirTemperature_3->setText(QString::number(fpr_airtemperature, 'f', 1));
    on_LineEdit_AirTemperature_3_returnPressed();


    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    /*** end changement of air pressure ***/
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_Altitude = ui->LineEdit_Altitude_3->displayText();
    Altitudee = value_Altitude.split(' ');
    if(Altitudee[0] == "" || Altitudee[0] == "m") {ui->LineEdit_Altitude_2->setText("1 m");}
    else{ui->LineEdit_Altitude_2->setText(Altitudee[0] + " m");}
    if(Altitudee[0] == "" || Altitudee[0] == "m") {ui->LineEdit_Altitude_3->setText("1 m");}
    else{ui->LineEdit_Altitude_3->setText(Altitudee[0] + " m");}
}

void MainWindow::on_LineEdit_HeadWindSpeed_2_textEdited(const QString &arg1)
{
    value_HeadWindSpeed_edited = arg1;
    if(value_HeadWindSpeed_edited == ""){} else{
    HeadWindSpeed_edited = value_HeadWindSpeed_edited.split(' ');
    ui->LineEdit_HeadWindSpeed_2->setText(HeadWindSpeed_edited[0]);
    ui->LineEdit_HeadWindSpeed_3->setText(HeadWindSpeed_edited[0]);
    order= 10;
    delement_order[0] = HeadWindSpeed_edited[0].toDouble();
    delement_order[1] = order;
    fpr_headwindspeed = HeadWindSpeed_edited[0].toDouble();
    }
}

void MainWindow::on_LineEdit_HeadWindSpeed_2_returnPressed()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_HeadWindSpeed = ui->LineEdit_HeadWindSpeed_2->displayText();
    HeadWindSpeed = value_HeadWindSpeed.split(' ');
    if(HeadWindSpeed[0] == "" || HeadWindSpeed[0] == "k" || HeadWindSpeed[0] == "km" || HeadWindSpeed[0] == "km/" || HeadWindSpeed[0] == "km/h") {ui->LineEdit_HeadWindSpeed_2->setText("1 km/h");}
    else{ui->LineEdit_HeadWindSpeed_2->setText(HeadWindSpeed[0] + " km/h");}
    if(HeadWindSpeed[0] == "" || HeadWindSpeed[0] == "k" || HeadWindSpeed[0] == "km" || HeadWindSpeed[0] == "km/" || HeadWindSpeed[0] == "km/h") {ui->LineEdit_HeadWindSpeed_3->setText("1 km/h");}
    else{ui->LineEdit_HeadWindSpeed_3->setText(HeadWindSpeed[0] + " km/h");}
}

void MainWindow::on_LineEdit_HeadWindSpeed_3_textEdited(const QString &arg1)
{
    value_HeadWindSpeed_edited = arg1;
    if(value_HeadWindSpeed_edited == ""){} else{
    HeadWindSpeed_edited = value_HeadWindSpeed_edited.split(' ');
    ui->LineEdit_HeadWindSpeed_2->setText(HeadWindSpeed_edited[0]);
    ui->LineEdit_HeadWindSpeed_3->setText(HeadWindSpeed_edited[0]);
    order= 10;
    delement_order[0] = HeadWindSpeed_edited[0].toDouble();
    delement_order[1] = order;
    fpr_headwindspeed = HeadWindSpeed_edited[0].toDouble();
    }
}

void MainWindow::on_LineEdit_HeadWindSpeed_3_returnPressed()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_HeadWindSpeed = ui->LineEdit_HeadWindSpeed_3->displayText();
    HeadWindSpeed = value_HeadWindSpeed.split(' ');
    if(HeadWindSpeed[0] == "" || HeadWindSpeed[0] == "k" || HeadWindSpeed[0] == "km" || HeadWindSpeed[0] == "km/" || HeadWindSpeed[0] == "km/h") {ui->LineEdit_HeadWindSpeed_2->setText("1 km/h");}
    else{ui->LineEdit_HeadWindSpeed_2->setText(HeadWindSpeed[0] + " km/h");}
    if(HeadWindSpeed[0] == "" || HeadWindSpeed[0] == "k" || HeadWindSpeed[0] == "km" || HeadWindSpeed[0] == "km/" || HeadWindSpeed[0] == "km/h") {ui->LineEdit_HeadWindSpeed_3->setText("1 km/h");}
    else{ui->LineEdit_HeadWindSpeed_3->setText(HeadWindSpeed[0] + " km/h");}
}

void MainWindow::on_LineEdit_CrossWindSpeed_2_textEdited(const QString &arg1)
{
    value_CrossWindSpeed_edited = arg1;
    if(value_CrossWindSpeed_edited == ""){} else{
    CrossWindSpeed_edited = value_CrossWindSpeed_edited.split(' ');
    ui->LineEdit_CrossWindSpeed_2->setText(CrossWindSpeed_edited[0]);
    ui->LineEdit_CrossWindSpeed_3->setText(CrossWindSpeed_edited[0]);
    order= 11;
    delement_order[0] = CrossWindSpeed_edited[0].toDouble();
    delement_order[1] = order;
    }
}

void MainWindow::on_LineEdit_CrossWindSpeed_2_returnPressed()
{
    fpr_crosswindspeed = CrossWindSpeed_edited[0].toDouble();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_CrossWindSpeed = ui->LineEdit_CrossWindSpeed_2->displayText();
    CrossWindSpeed = value_CrossWindSpeed.split(' ');
    if(CrossWindSpeed[0] == "" || CrossWindSpeed[0] == "k" || CrossWindSpeed[0] == "km" || CrossWindSpeed[0] == "km/" || CrossWindSpeed[0] == "km/h") {ui->LineEdit_CrossWindSpeed_2->setText("1 km/h");}
    else{ui->LineEdit_CrossWindSpeed_2->setText(CrossWindSpeed[0] + " km/h");}
    if(CrossWindSpeed[0] == "" || CrossWindSpeed[0] == "k" || CrossWindSpeed[0] == "km" || CrossWindSpeed[0] == "km/" || CrossWindSpeed[0] == "km/h") {ui->LineEdit_CrossWindSpeed_3->setText("1 km/h");}
    else{ui->LineEdit_CrossWindSpeed_3->setText(CrossWindSpeed[0] + " km/h");}
}

void MainWindow::on_LineEdit_CrossWindSpeed_3_textEdited(const QString &arg1)
{
    value_CrossWindSpeed_edited = arg1;
    if(value_CrossWindSpeed_edited == ""){} else{
    CrossWindSpeed_edited = value_CrossWindSpeed_edited.split(' ');
    ui->LineEdit_CrossWindSpeed_2->setText(CrossWindSpeed_edited[0]);
    ui->LineEdit_CrossWindSpeed_3->setText(CrossWindSpeed_edited[0]);
    order= 11;
    delement_order[0] = CrossWindSpeed_edited[0].toDouble();
    delement_order[1] = order;
    }
}

void MainWindow::on_LineEdit_CrossWindSpeed_3_returnPressed()
{
    fpr_crosswindspeed = CrossWindSpeed_edited[0].toDouble();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_CrossWindSpeed = ui->LineEdit_CrossWindSpeed_3->displayText();
    CrossWindSpeed = value_CrossWindSpeed.split(' ');
    if(CrossWindSpeed[0] == "" || CrossWindSpeed[0] == "k" || CrossWindSpeed[0] == "km" || CrossWindSpeed[0] == "km/" || CrossWindSpeed[0] == "km/h") {ui->LineEdit_CrossWindSpeed_2->setText("1 km/h");}
    else{ui->LineEdit_CrossWindSpeed_2->setText(CrossWindSpeed[0] + " km/h");}
    if(CrossWindSpeed[0] == "" || CrossWindSpeed[0] == "k" || CrossWindSpeed[0] == "km" || CrossWindSpeed[0] == "km/" || CrossWindSpeed[0] == "km/h") {ui->LineEdit_CrossWindSpeed_3->setText("1 km/h");}
    else{ui->LineEdit_CrossWindSpeed_3->setText(CrossWindSpeed[0] + " km/h");}
}



void MainWindow::on_LineEdit_Range_2_textEdited(const QString &arg1)
{
    value_Range_edited = arg1;
    Range_edited = value_Range_edited.split(' ');
    ui->LineEdit_Range_2->setText(Range_edited[0]);
    order= 12;
    delement_order[0] = Range_edited[0].toDouble();
    delement_order[1] = order;
    makePlot(delement_order);
}

void MainWindow::on_LineEdit_Range_2_returnPressed()
{
    value_Range = ui->LineEdit_Range_2->displayText();
    Range = value_Range.split(' ');
    if(Range[0] == "" || Range[0] == "c" || Range[0] == "cm") {ui->LineEdit_Range_2->setText("1 cm");}
    else{ui->LineEdit_Range_2->setText(Range[0] + " cm");}
}

void MainWindow::on_LineEdit_TargetHeight_2_textEdited(const QString &arg1)
{
    value_TargetHeight_edited = arg1;
    TargetHeight_edited = value_TargetHeight_edited.split(' ');
    ui->LineEdit_TargetHeight_2->setText(TargetHeight_edited[0]);
    order= 13;
    delement_order[0] = TargetHeight_edited[0].toDouble();
    delement_order[1] = order;
    makePlot(delement_order);
}

void MainWindow::on_LineEdit_TargetHeight_2_returnPressed()
{
    value_TargetHeight = ui->LineEdit_TargetHeight_2->displayText();
    TargetHeight = value_TargetHeight.split(' ');
    if(TargetHeight[0] == "" || TargetHeight[0] == "c" || TargetHeight[0] == "cm") {ui->LineEdit_TargetHeight_2->setText("1 cm");}
    else{ui->LineEdit_TargetHeight_2->setText(TargetHeight[0] + " cm");}
}

void MainWindow::on_LineEdit_GraphXEnd_2_textEdited(const QString &arg1)
{
    value_GraphXEnd_edited = arg1;
    GraphXEnd_edited = value_GraphXEnd_edited.split(' ');
    ui->LineEdit_GraphXEnd_2->setText(GraphXEnd_edited[0]);
    fpr_graphXend = GraphXEnd_edited[0].toInt();
}

void MainWindow::on_LineEdit_GraphXEnd_2_returnPressed()
{
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    value_GraphXEnd = ui->LineEdit_GraphXEnd_2->displayText();
    GraphXEnd = value_GraphXEnd.split(' ');
    order= 14;
    delement_order[0] = GraphXEnd[0].toDouble();
    delement_order[1] = order;
    makePlot(delement_order);

    if(GraphXEnd[0] == "" || GraphXEnd[0] == "m") {
        ui->LineEdit_GraphXEnd_2->setText(QString::number(fpr_traj_range) + " m");
        fpr_graphXend = fpr_traj_range;
        makePlot(delement_order);
    }
    else{ui->LineEdit_GraphXEnd_2->setText(GraphXEnd[0] + " m"); makePlot(delement_order);}
}

void MainWindow::on_LineEdit_Interval_2_textEdited(const QString &arg1)
{
    value_Interval_edited = arg1;
    Interval_edited = value_Interval_edited.split(' ');
    ui->LineEdit_Interval_2->setText(Interval_edited[0]);
    order= 15;
    delement_order[0] = Interval_edited[0].toDouble();
    delement_order[1] = order;
}

void MainWindow::on_LineEdit_Interval_2_returnPressed()
{
    fpr_step = Interval_edited[0].toDouble();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_Interval = ui->LineEdit_Interval_2->displayText();
    Interval = value_Interval.split(' ');
    if(Interval[0] == "" || Interval[0] == "m") {ui->LineEdit_Interval_2->setText("1 m");}
    else{ui->LineEdit_Interval_2->setText(Interval[0] + " m");}
}

void MainWindow::on_LineEdit_GridXm_2_textEdited(const QString &arg1)
{
    value_GridXm_edited = arg1;
    GridXm_edited = value_GridXm_edited.split(' ');
    ui->LineEdit_GridXm_2->setText(GridXm_edited[0]);
    order= 16;
    delement_order[0] = GridXm_edited[0].toDouble();
    delement_order[1] = order;
    makePlot(delement_order);
}

void MainWindow::on_LineEdit_GridXm_2_returnPressed()
{
    fpr_gridxm = GridXm_edited[0].toDouble();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_GridXm = ui->LineEdit_GridXm_2->displayText();
    GridXm = value_GridXm.split(' ');
    if(GridXm[0] == "" || GridXm[0] == "m") {ui->LineEdit_GridXm_2->setText("1 m");}
    else{ui->LineEdit_GridXm_2->setText(GridXm[0] + " m");}
}

void MainWindow::on_LineEdit_YCm_2_textEdited(const QString &arg1)
{
    value_YCm_edited = arg1;
    YCm_edited = value_YCm_edited.split(' ');
    ui->LineEdit_YCm_2->setText(YCm_edited[0]);
    order= 17;
    delement_order[0] = YCm_edited[0].toDouble();
    delement_order[1] = order;
    makePlot(delement_order);
}

void MainWindow::on_LineEdit_YCm_2_returnPressed()
{
    value_YCm = ui->LineEdit_YCm_2->displayText();
    YCm = value_YCm.split(' ');
    if(YCm[0] == "" || YCm[0] == "c" || YCm[0] == "cm") {ui->LineEdit_YCm_2->setText("1 cm");}
    else{ui->LineEdit_YCm_2->setText(YCm[0] + " cm");}
}

void MainWindow::on_LineEdit_TrajRange_2_textEdited(const QString &arg1)
{
    value_TrajRange_edited = arg1;
    TrajRange_edited = value_TrajRange_edited.split(' ');
    ui->LineEdit_TrajRange_2->setText(TrajRange_edited[0]);
    order= 18;
    delement_order[0] = TrajRange_edited[0].toDouble();
    delement_order[1] = order;
    fpr_traj_range = TrajRange_edited[0].toInt();

}

void MainWindow::on_LineEdit_TrajRange_2_returnPressed()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);

    value_TrajRange = ui->LineEdit_TrajRange_2->displayText();
    TrajRange = value_TrajRange.split(' ');
    if(TrajRange[0] == "" || TrajRange[0] == "m") {ui->LineEdit_TrajRange_2->setText("1 m");}
    else{ui->LineEdit_TrajRange_2->setText(TrajRange[0] + " m");}
}

void MainWindow::on_LineEdit_Range2_2_textEdited(const QString &arg1)
{
   value_range2_edited = arg1;
   range2_edited = value_range2_edited.split(' ');
   ui->LineEdit_Range2_2->setText(range2_edited[0]);
   fpr_range2 = range2_edited[0].toInt();
   order= 19;
   delement_order[0] = range2_edited[0].toDouble();
   delement_order[1] = order;
   ui->customPlot_2->clearItems();
   ui->customPlot_3->clearItems();
   makePlot(delement_order);
}

void MainWindow::on_LineEdit_Range2_2_returnPressed()
{
    value_range2 = ui->LineEdit_Range2_2->displayText();
    range2 = value_range2.split('m');
    if(range2[0] == "" || range2[0] == "m") {ui->LineEdit_Range2_2->setText("1 m");}
    else{ui->LineEdit_Range2_2->setText(range2[0] + " m");}
}

void MainWindow::on_LineEdit_Wall_2_textEdited(const QString &arg1)
{
    value_Wall_edited = arg1;
    Wall_edited = value_Wall_edited.split(' ');
    ui->LineEdit_Wall_2->setText(Wall_edited[0]);
    fpr_wall = Wall_edited[0].toInt();
    order= 20;
    delement_order[0] = Wall_edited[0].toDouble();
    delement_order[1] = order;
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
}

void MainWindow::on_LineEdit_Wall_2_returnPressed()
{
    value_Wall = ui->LineEdit_Wall_2->displayText();
    Wall = value_Wall.split(' ');
    if(Wall[0] == "" || Wall[0] == "m") {ui->LineEdit_Wall_2->setText("1 m");}
    else{ui->LineEdit_Wall_2->setText(Wall[0] + " m");}
}

void MainWindow::initTableWidget(string fpr_dragfunction,double fpr_muzzle_velocity,double fpr_balcoefficient,double fpr_heightofsight,double fpr_gunelevation1,double fpr_airtemperature,double fpr_airpressure,double fpr_humidity,double fpr_altitude,double fpr_headwindspeed,double fpr_crosswindspeed,int fpr_graphXend,double fpr_step,double fpr_gridxm,int fpr_traj_range,int fpr_range2,int fpr_wall)
{

    const int nCols = 8;
    ui->tableWidget_2->setColumnCount(nCols);
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);

    ui->tableWidget_2->verticalHeader()->hide();
    ui->tableWidget_2->setHorizontalHeaderItem(0, new QTableWidgetItem("Range (m)"));
    ui->tableWidget_2->setHorizontalHeaderItem(1, new QTableWidgetItem("Height (cm)"));
    ui->tableWidget_2->setHorizontalHeaderItem(2, new QTableWidgetItem("Defl (cm)"));
    ui->tableWidget_2->setHorizontalHeaderItem(3, new QTableWidgetItem("Vel (m/s)"));
    ui->tableWidget_2->setHorizontalHeaderItem(4, new QTableWidgetItem("Time (s)"));
    ui->tableWidget_2->setHorizontalHeaderItem(5, new QTableWidgetItem("Vx (m/sn)"));
    ui->tableWidget_2->setHorizontalHeaderItem(6, new QTableWidgetItem("Vy (m/sn)"));
    ui->tableWidget_2->setHorizontalHeaderItem(7, new QTableWidgetItem("Vz (m/sn)"));

    //TEST Amaçlıdır.
        //Drag function
        DragFunction dragFunc = DragFunction::CreateDragFunction(fpr_dragfunction);
        DragFunction drag2 = DragFunction::CreateDragFunction("G2");
        //BallisticProjector

        //BallisticProjector* bullet = new BallisticProjector(1, "Test", 2.00, false, 100.00, 10.00, 2800.0, 0.105, dragFunc);
        BallisticProjector* bullet = new BallisticProjector(1, "Test", 5.56, false, 100.00, fpr_heightofsight, (fpr_muzzle_velocity*3.28084), fpr_balcoefficient, dragFunc);
        //cout << bullet->getBallisticCoefficient() << endl;
        //cout << bullet->getDragFunction().getDragFunction() << endl;
    /*
     *
        for each (double number in bullet->getDragFunction().getTheMachSpeedArray())
        {
            cout << number << endl;
        }

        bullet->setDragFunction(drag2);
        cout << "-------" << endl;

        for each (double number in bullet->getDragFunction().getTheMachSpeedArray()) {
            cout << number << endl;
        }
    */
        //AirDensity ---double AirDensity::CalculateAirDensity(double H, double T, double A, double P)

        AirDensity airDensity(fpr_humidity, fpr_airtemperature, fpr_altitude, fpr_airpressure);
        Wind wind(fpr_crosswindspeed,fpr_headwindspeed);


        airDensity.CalculateAirDensity();
        wind.CalculateCrossWind(wind.getSpeed(), wind.getAngle());
        wind.CalculateHeadWind(wind.getSpeed(), wind.getAngle());


        Atmosphere* atm = new Atmosphere(airDensity, wind);

        /*QDebug << atm->getAirDensity().getAltitude() << endl;
        QDebug << atm->getAirDensity().getPressure() << endl;
        QDebug << atm->getAirDensity().getHumidity() << endl;
        QDebug << atm->getWind().getAngle() << endl;*/
        //BallisticTrajectory

        //Dikey pozitif sapma açısı.
        double incVerticalAngle = fpr_gunelevation1;
        //saat yönünde yatay sapma açısı
        double incHorizontalAngle = 0.00;
        //Kaç metrede bir nokta yaratılsın

        //*********************************************************************double step = 5.00;
        //Interval_edited = value_Interval_edited.split(" ");
        //Hangi uzaklığa kadar balistik hesabı yapılsın


        //	BallisticTrajectory::CalculateBulletPathWay(bullet, atm, incVerticalAngle, incHorizontalAngle, step, range);


        int size = BallisticTrajectory::CalculateBulletPathWay(bullet, atm, incVerticalAngle, incHorizontalAngle, fpr_step, fpr_traj_range).size();


        for (int i = 0; i < size; i++) {
          try {

                ResultList.push_back(BallisticTrajectory::CalculateBulletPathWay(bullet, atm, fpr_gunelevation1, incHorizontalAngle, fpr_step, fpr_traj_range).at(i));
            }
            catch (exception ex) {
                ex.what();
            }
        }

        const int nRows = ResultList.size();

        for( int i = 0; i < nRows; i++ )
        {
           ui->tableWidget_2->insertRow(i);
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getDistance())));
              item->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_2->setItem( i, 0, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getHeight())));
              item->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_2->setItem( i, 1, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getDeflection())));
              item->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_2->setItem( i, 2, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getTotalVelocity())));
              item->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_2->setItem( i, 3, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getTime())));
              item->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_2->setItem( i, 4, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getTheVelocityX())));
              item->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_2->setItem( i, 5, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getTheVelocityY())));
              item->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_2->setItem( i, 6, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getTheVelocityZ())));
              item->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_2->setItem( i, 7, item );
           }

        }


        ui->lineEditDeneme->setText(QString::number(ResultList.size()));


        /*
        BulletCondition bulletCondition;

         foreach( bulletCondition , ResultList)
             {
                 qDebug() << "   Velocity: " << bulletCondition.getTotalVelocity() << "	Flight Time: " << bulletCondition.getTime() << "   Flight Distance: " << bulletCondition.getDistance() << "   Flight Deflection: "<< bulletCondition.getDeflection() << "   Height: " << bulletCondition.getHeight() << "   Velocity X: "<< bulletCondition.getTheVelocityX() << "   Velocity Y: "<< bulletCondition.getTheVelocityY() <<"   Velocity Z: "<< bulletCondition.getTheVelocityZ() <<endl;
             }
        */
}

void MainWindow::makePlot(double delement_order[2])
{

    int    order          = int(delement_order[1]);
    double element_nvalue = delement_order[0];

    // generate some data:
   QVector<double> x(2000), y(2000),lazerx(2000),lazery(2000),target_height(2000),target_deflection(2000); // initialize with entries 0..100

   if((fpr_muzzle_velocity == 1052.0) && (fpr_balcoefficient == 0.221))
   {
       x = { 0.000,0.050,0.150,0.200,0.250,0.300,0.350,0.400,0.450,0.500,0.550,0.600,0.650,0.700,0.725,0.750,0.775,0.800,0.825,0.850
       ,0.875,0.900,0.925,0.950,0.975,1.000,1.025,1.050,1.075,1.100,1.125,1.150,1.200,1.250,1.300,1.350,1.400,1.450,1.500,1.550,1.600
       ,1.650,1.700,1.750,1.800,1.850,1.900,1.950,2.000,2.050,2.100,2.150,2.200,2.250,2.300,2.350,2.400,2.450,2.500,2.600,2.700,2.800
       ,2.900,3.000,3.100,3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,4.000,4.200,4.400,4.600,4.800,5.000};

       y = {0.2629,0.2558,0.2487,0.2413,0.2344,0.2278,0.2214,0.2155,0.2104,0.2061,0.2032,0.202,0.2034,0.2165,0.223,0.2313,0.2417,0.2546
       ,0.2706,0.2901,0.3136,0.3415,0.3734,0.4084,0.4448,0.4805,0.5136,0.5427,0.5677,0.5883,0.6053,0.6191,0.6393,0.6518,0.6589,0.6621
       ,0.6625,0.6607,0.6573,0.6528,0.6474,0.6413,0.6347,0.628,0.621,0.6141,0.6072,0.6003,0.5934,0.5867,0.5804,0.5743,0.5685,0.563,0.5577
       ,0.5527,0.5481,0.5438,0.5397,0.5325,0.5264,0.5211,0.5168,0.5133,0.5105,0.5084,0.5067,0.5054,0.504,0.503,0.5022,0.5016,0.501,0.5006
       ,0.4998,0.4995,0.4992,0.499,0.4988};

       //create graph and assign data to it:
       ui->customPlot_2->addGraph();
       ui->customPlot_2->graph(0)->setData(x, y);
       // give the axes some labels:
       ui->customPlot_2->xAxis->setLabel("x");
       ui->customPlot_2->yAxis->setLabel("y");
       // set axes ranges, so we see all data:
       ui->customPlot_2->xAxis->setRange(0, 5);
       ui->customPlot_2->yAxis->setRange(0, 1);
       ui->customPlot_2->replot();

       ui->customPlot_3->addGraph();
       ui->customPlot_3->graph(0)->setData(x, y);
       // give the axes some labels:
       ui->customPlot_3->xAxis->setLabel("x");
       ui->customPlot_3->yAxis->setLabel("y");
       // set axes ranges, so we see all data:
       ui->customPlot_3->xAxis->setRange(0, 5);
       ui->customPlot_3->yAxis->setRange(0, 1);
       ui->customPlot_3->replot();
   }
   else
   {
       /*for (int i=0; i<101; ++i)
       {
         x[i] = i/50.0 - 1; // x goes from -1 to 1
         y[i] = x[i]*x[i]; // let's plot a quadratic function
       }
       */

       for (int i=0; i < ResultList.size(); i++)
       {
         x[i] = ResultList.at(i).getDistance();
         y[i] = ResultList.at(i).getHeight(); // let's plot a quadratic function
       }

       /*QCPItemLine *line = new QCPItemLine(ui->customPlot);
       line->point1->setCoords(2, 0);  // location of point 1 in plot coordinate
       line->point2->setCoords(2, 1);  // location of point 2 in plot coordinate*/





       // create graph and assign data to it:
       ui->customPlot_2->addGraph();
       ui->customPlot_2->graph(0)->setData(x, y);
       // give the axes some labels:
       ui->customPlot_2->xAxis->setLabel("x");
       ui->customPlot_2->yAxis->setLabel("y");
       // set axes ranges, so we see all data:
       ui->customPlot_2->xAxis->setRange(fpr_gridxm, fpr_graphXend);
       QPainter painter(this);
       QPen pen;  // creates a default pen

       pen.setStyle(Qt::DotLine);
       pen.setWidth(0.5);
       pen.setBrush(Qt::gray);
       pen.setCapStyle(Qt::RoundCap);
       pen.setJoinStyle(Qt::RoundJoin);

       painter.setPen(pen);
       ui->customPlot_2->xAxis->setSubTickPen(pen);
       ui->customPlot_2->xAxis->setSubTickLength(267);
       //ui->customPlot_2->yAxis->setRange(-81000, 81000);
       ui->customPlot_2->yAxis->setRange(-150000, 150000);


       /* wall */
       QCPItemStraightLine *infLine = new QCPItemStraightLine(ui->customPlot_2);
       infLine->setPen(QPen(Qt::darkRed));
       infLine->point1->setCoords(fpr_wall, 0);  // location of point 1 in plot coordinate
       infLine->point2->setCoords(fpr_wall, 3);  // location of point 2 in plot coordinate


       /* zero line */
       QCPItemStraightLine *infLine2 = new QCPItemStraightLine(ui->customPlot_2);
       infLine2->setPen(QPen(Qt::darkGreen));
       infLine2->point1->setCoords(0, 0);  // location of point 1 in plot coordinate


       /* range2 */
       QCPItemStraightLine *infLine3 = new QCPItemStraightLine(ui->customPlot_2);
       infLine3->setPen(QPen(Qt::darkMagenta));
       infLine3->point1->setCoords(fpr_range2, 0);  // location of point 1 in plot coordinate
       infLine3->point2->setCoords(fpr_range2, 3);  // location of point 2 in plot coordinate


       // create graph and assign data to it:
       ui->customPlot_3->addGraph();
       ui->customPlot_3->graph(0)->setData(x, y);
       // give the axes some labels:
       ui->customPlot_3->xAxis->setLabel("x");
       ui->customPlot_3->yAxis->setLabel("y");
       // set axes ranges, so we see all data:
       ui->customPlot_3->xAxis->setRange(fpr_gridxm, fpr_graphXend);
       QPainter painter2(this);
       QPen pen2;  // creates a default pen

       pen2.setStyle(Qt::DotLine);
       pen2.setWidth(0.5);
       pen2.setBrush(Qt::gray);
       pen2.setCapStyle(Qt::RoundCap);
       pen2.setJoinStyle(Qt::RoundJoin);

       painter2.setPen(pen2);
       ui->customPlot_3->xAxis->setSubTickPen(pen2);
       ui->customPlot_3->xAxis->setSubTickLength(267);
       //ui->customPlot_2->yAxis->setRange(-81000, 81000);
       ui->customPlot_3->yAxis->setRange(-150000, 150000);



       /* wall */
       QCPItemStraightLine *infLine_second_1 = new QCPItemStraightLine(ui->customPlot_3);
       infLine_second_1->setPen(QPen(Qt::darkRed));
       infLine_second_1->point1->setCoords(fpr_wall, 0);  // location of point 1 in plot coordinate
       infLine_second_1->point2->setCoords(fpr_wall, 3);  // location of point 2 in plot coordinate


       /* zero line */
       QCPItemStraightLine *infLine_second_2 = new QCPItemStraightLine(ui->customPlot_3);
       infLine_second_2->setPen(QPen(Qt::darkGreen));
       infLine_second_2->point1->setCoords(0, 0);  // location of point 1 in plot coordinate


       /* range2 */
       QCPItemStraightLine *infLinesecond_3 = new QCPItemStraightLine(ui->customPlot_3);
       infLinesecond_3->setPen(QPen(Qt::darkMagenta));
       infLinesecond_3->point1->setCoords(fpr_range2, 0);  // location of point 1 in plot coordinate
       infLinesecond_3->point2->setCoords(fpr_range2, 3);  // location of point 2 in plot coordinate



       const int nRows = ResultList.size();
       const int nCols = 8;

        QCPItemStraightLine *infLineLzr = new QCPItemStraightLine(ui->customPlot_2);
        QCPItemStraightLine *infLineLzr_second = new QCPItemStraightLine(ui->customPlot_3);
       for( int i = 0; i < nRows; i++ )
       {
          for( int j = 0; j < nCols; j++ ) {
           lazerx[i] = ResultList.at(i).getDistance();
           lazery[i] = ResultList.at(i).getHeight() + ResultList.at(i).getDeflection();
           target_height[i] = ResultList.at(i).getHeight();
           target_deflection[i] = ResultList.at(i).getDeflection();
           /* zero line */
           infLineLzr->setPen(QPen(Qt::red));
           infLineLzr->point1->setCoords(round(lazerx[i]), round(lazery[i])*1.5);  // location of point 1 in plot coordinate
           /* zero line */
           infLineLzr_second->setPen(QPen(Qt::red));
           infLineLzr_second->point1->setCoords(round(lazerx[i]), round(lazery[i])*1.5);  // location of point 1 in plot coordinate
          }
          ui->lineEditDeneme_2->setText(QString::number(target_height[(round(fpr_range2/fpr_step))]/10));
          ui->lineEditDeneme_3->setText(QString::number(target_deflection[(round(fpr_range2/fpr_step))]*10));
          ui->txtlabel_hght_defl->setText("Drop (cm) : " +QString::number(target_height[(round(fpr_range2/fpr_step))]/10) + "  Deflection (cm) : " +QString::number(target_deflection[(round(fpr_range2/fpr_step))]*10));
       }

        ui->customPlot_2->replot();
        ui->customPlot_3->replot();

        /*
        // create empty curve objects:
        QCPCurve *fermatSpiral1 = new QCPCurve(ui->customPlot_4->xAxis, ui->customPlot_4->yAxis);


        // generate the curve data points:
        const int pointCount = 500;
        QVector<QCPCurveData> dataSpiral1(pointCount);
        for (int i=0; i<pointCount; ++i)
        {
          double phi = i/(double)(pointCount-1)*8*M_PI;
          double theta = i/(double)(pointCount-1)*2*M_PI;
          dataSpiral1[i] = QCPCurveData(i, qSqrt(phi)*qCos(phi), qSqrt(phi)*qSin(phi));
        }
        // pass the data to the curves; we know t (i in loop above) is ascending, so set alreadySorted=true (saves an extra internal sort):
        fermatSpiral1->data()->set(dataSpiral1, true);
        // color the curves:

        // set some basic customPlot config:
        ui->customPlot_4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->customPlot_4->axisRect()->setupFullAxesBox();
        ui->customPlot_4->rescaleAxes();
        */

        scene = new QGraphicsScene(0,0,0,0);
        ui->graphicsView->setScene(scene);
        QPen redPen(Qt::red);
        QPen bluePen(Qt::blue);
        /*
        ellipse = scene->addEllipse(-50,10,100,100,redPen);
        ellipse = scene->addEllipse(-100,-40,200,200,redPen);
        ellipse = scene->addEllipse(-150,-90,300,300,redPen);
        */
        /*
        ellipse = scene->addEllipse(-11,49.5,22,22,redPen);
        ellipse = scene->addEllipse(-22,38.5,44,44,redPen);
        ellipse = scene->addEllipse(-44,16.5,88,88,redPen);
        ellipse = scene->addEllipse(-66,-5.5,132,132,redPen);
        ellipse = scene->addEllipse(-88,-27.5,176,176,redPen);
        ellipse = scene->addEllipse(-110,-49.5,220,220,redPen);
        ellipse = scene->addEllipse(-132,-71.5,264,264,redPen);
        ellipse = scene->addEllipse(-154,-93.5,308,308,redPen);
        ellipse = scene->addEllipse(-176,-115.5,352,352,redPen);
        ellipse = scene->addEllipse(-198,-137.5,396,396,redPen);
        ellipse = scene->addEllipse(-220,-159.5,440,440,redPen);
        */
        QBrush brush_magenta(Qt::magenta);
        QBrush brush_red(Qt::red);


        ellipse = scene->addEllipse(-20,40,40,40,redPen);
        ellipse = scene->addEllipse(-40,20,80,80,redPen);
        ellipse = scene->addEllipse(-60,0,120,120,redPen);
        ellipse = scene->addEllipse(-80,-20,160,160,redPen);
        ellipse = scene->addEllipse(-100,-40,200,200,redPen);
        ellipse = scene->addEllipse(-120,-60,240,240,redPen);
        ellipse = scene->addEllipse(-140,-80,280,280,redPen);
        ellipse = scene->addEllipse(-160,-100,320,320,redPen);
        ellipse = scene->addEllipse(-180,-120,360,360,redPen);
        ellipse = scene->addEllipse(-200,-140,400,400,redPen);
        ellipse = scene->addEllipse(-220,-160,440,440,redPen);


        //ellipse = scene->addEllipse(-50,30,100,100,redPen);
        //ellipse = scene->addEllipse(-60,30,60,60,redPen);


        /*ellipse = scene->addEllipse(-20,35,40,40,redPen);
        ellipse = scene->addEllipse(-40,15,80,80,redPen);
        ellipse = scene->addEllipse(-60,5,120,120,redPen);
        ellipse = scene->addEllipse(-80,-15,160,160,redPen);
        ellipse = scene->addEllipse(-110,-35,220,220,redPen);
        ellipse = scene->addEllipse(-130,-55,260,260,redPen);
        ellipse = scene->addEllipse(-150,-75,300,300,redPen);
        ellipse = scene->addEllipse(-170,-95,340,340,redPen);
        ellipse = scene->addEllipse(-190,-115,380,380,redPen);
        ellipse = scene->addEllipse(-220,-135,440,440,redPen);*/

        myline = scene->addLine(-240,60,240,60);
        myline = scene->addLine(0,285,0,-165);

        target_number = ui->lineEditDeneme_2->displayText();
        tar_number = round(target_number.toDouble());
        QString target_deflection = ui->lineEditDeneme_3->displayText();
        double target_def_number  = target_deflection.toDouble();

        if(tar_number > 220 || tar_number < -220)
        {
        scaled_val = tar_number /fpr_scalingat45deg;
        }
        else
        {
         scaled_val = tar_number;
        }

        ellipse = scene->addEllipse(6,54,-12,12,bluePen,brush_red);
        ellipse = scene->addEllipse((target_def_number+6),((scaled_val*-1)+54),-12,12,bluePen,brush_magenta);

        QString str_tar_number;
        double str_tar;
        int k=18,s=2;

        if(fpr_gunelevation1 >0 || tar_number< -4)
        {
        scene->clear();
        scene = new QGraphicsScene(0,0,0,0);
        ui->graphicsView->setScene(scene);
        QPen redPen(Qt::red);
        QPen bluePen(Qt::blue);

        myline = scene->addLine(-240,60,240,60);
        myline = scene->addLine(0,285,0,-165);

        ellipse = scene->addEllipse(-20,40,40,40,redPen);
        ellipse = scene->addEllipse(-40,20,80,80,redPen);
        ellipse = scene->addEllipse(-60,0,120,120,redPen);
        ellipse = scene->addEllipse(-80,-20,160,160,redPen);
        ellipse = scene->addEllipse(-100,-40,200,200,redPen);
        ellipse = scene->addEllipse(-120,-60,240,240,redPen);
        ellipse = scene->addEllipse(-140,-80,280,280,redPen);
        ellipse = scene->addEllipse(-160,-100,320,320,redPen);
        ellipse = scene->addEllipse(-180,-120,360,360,redPen);
        ellipse = scene->addEllipse(-200,-140,400,400,redPen);
        ellipse = scene->addEllipse(-220,-160,440,440,redPen);

        ellipse = scene->addEllipse(6,54,-12,12,bluePen,brush_red);

        ellipse = scene->addEllipse((target_def_number+6),((scaled_val*-1)+54),-12,12,bluePen,brush_magenta);

        text = scene->addText("20");text->setPos(18, 56);text = scene->addText("40");text->setPos(38, 56);text = scene->addText("60");text->setPos(58, 56);text = scene->addText("80");text->setPos(78, 56);text = scene->addText("100");text->setPos(98, 56);text = scene->addText("120");text->setPos(118, 56);text = scene->addText("140");text->setPos(138, 56);text = scene->addText("160");text->setPos(158, 56);text = scene->addText("180");text->setPos(178, 56);text = scene->addText("200");text->setPos(198, 56);text = scene->addText("220");text->setPos(218, 56);
        text = scene->addText("20");text->setPos(-34, 56);text = scene->addText("40");text->setPos(-56, 56);text = scene->addText("60");text->setPos(-76, 56);text = scene->addText("80");text->setPos(-96, 56);text = scene->addText("100");text->setPos(-122, 56);text = scene->addText("120");text->setPos(-142, 56);text = scene->addText("140");text->setPos(-162, 56);text = scene->addText("160");text->setPos(-182, 56);text = scene->addText("180");text->setPos(-202, 56);text = scene->addText("200");text->setPos(-222, 56);text = scene->addText("220");text->setPos(-242, 56);
        text = scene->addText("20");text->setPos(0, 26);text = scene->addText("40");text->setPos(0, 6);text = scene->addText("60");text->setPos(0, -14);text = scene->addText("80");text->setPos(0, -34);text = scene->addText("100");text->setPos(0, -54);text = scene->addText("120");text->setPos(0, -74);text = scene->addText("140");text->setPos(0, -94);text = scene->addText("160");text->setPos(0, -114);text = scene->addText("180");text->setPos(0, -134);text = scene->addText("200");text->setPos(0, -154);text = scene->addText("220");text->setPos(0, -174);
        text = scene->addText("20");text->setPos(0, 74);text = scene->addText("40");text->setPos(0, 94);text = scene->addText("60");text->setPos(0, 114);text = scene->addText("80");text->setPos(0, 134);text = scene->addText("100");text->setPos(0, 154);text = scene->addText("120");text->setPos(0, 174);text = scene->addText("140");text->setPos(0, 194);text = scene->addText("160");text->setPos(0, 214);text = scene->addText("180");text->setPos(0, 234);text = scene->addText("200");text->setPos(0, 254);text = scene->addText("220");text->setPos(0, 274);
        }
        if(tar_number< 0 && tar_number >-10){
            scene->clear();
            scene = new QGraphicsScene(0,0,0,0);
            ui->graphicsView->setScene(scene);
            QPen redPen(Qt::red);
            QPen bluePen(Qt::blue);

            myline = scene->addLine(-240,60,240,60);
            myline = scene->addLine(0,285,0,-165);

            ellipse = scene->addEllipse(-20,40,40,40,redPen);
            ellipse = scene->addEllipse(-40,20,80,80,redPen);
            ellipse = scene->addEllipse(-60,0,120,120,redPen);
            ellipse = scene->addEllipse(-80,-20,160,160,redPen);
            ellipse = scene->addEllipse(-100,-40,200,200,redPen);
            ellipse = scene->addEllipse(-120,-60,240,240,redPen);
            ellipse = scene->addEllipse(-140,-80,280,280,redPen);
            ellipse = scene->addEllipse(-160,-100,320,320,redPen);
            ellipse = scene->addEllipse(-180,-120,360,360,redPen);
            ellipse = scene->addEllipse(-200,-140,400,400,redPen);
            ellipse = scene->addEllipse(-220,-160,440,440,redPen);

            ellipse = scene->addEllipse(6,54,-10,10,bluePen,brush_red);
            ellipse = scene->addEllipse((target_def_number+8),((scaled_val*-1)+60),-17,17,bluePen,brush_magenta);


            s=2;
            for(int i = 0 ; i< 11; i++)
            {
                str_tar_number = QString::number(s * 2);
                s += 2;
                text = scene->addText(str_tar_number);
                text->setPos(k, 56);
                k+=20;
            }
            k=-36;
            s=2;
            for(int i = 0 ; i< 11; i++)
            {
                str_tar_number = QString::number(s * 2);
                s += 2;
                text = scene->addText(str_tar_number);
                text->setPos(k, 56);
                k-=20;
            }

            k=26;
            s = 2;

            for(int i = 0 ; i< 11; i++)
            {
                str_tar_number = QString::number(s * 2);
                s += 2;
                text = scene->addText(str_tar_number);
                text->setPos(0, k);
                k-=20;
            }

            k=74;
            s = 2;

            for(int i = 0 ; i< 11; i++)
            {
                str_tar_number = QString::number(s * 2);
                s += 2;
                text = scene->addText(str_tar_number);
                text->setPos(0, k);
                k+=20;
            }
            }
        }

   /*
     // generate some data:
     QVector<double> x(101), y(101); // initialize with entries 0..100
     if(bc_text == "0.1")

         {
             for (int i=0; i<101; ++i)
             {
               x[i] = i/50.0 - 1; // x goes from -1 to 1
               y[i] = x[i]*x[i]; // let's plot a quadratic function
             }
         }
         else
         {
        x = { 0.000,0.050,0.150,0.200,0.250,0.300,0.350,0.400,0.450,0.500,0.550,0.600,0.650,0.700,0.725,0.750,0.775,0.800,0.825,0.850
       ,0.875,0.900,0.925,0.950,0.975,1.000,1.025,1.050,1.075,1.100,1.125,1.150,1.200,1.250,1.300,1.350,1.400,1.450,1.500,1.550,1.600
       ,1.650,1.700,1.750,1.800,1.850,1.900,1.950,2.000,2.050,2.100,2.150,2.200,2.250,2.300,2.350,2.400,2.450,2.500,2.600,2.700,2.800
       ,2.900,3.000,3.100,3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,4.000,4.200,4.400,4.600,4.800,5.000};

       y = {0.2629,0.2558,0.2487,0.2413,0.2344,0.2278,0.2214,0.2155,0.2104,0.2061,0.2032,0.202,0.2034,0.2165,0.223,0.2313,0.2417,0.2546
       ,0.2706,0.2901,0.3136,0.3415,0.3734,0.4084,0.4448,0.4805,0.5136,0.5427,0.5677,0.5883,0.6053,0.6191,0.6393,0.6518,0.6589,0.6621
       ,0.6625,0.6607,0.6573,0.6528,0.6474,0.6413,0.6347,0.628,0.621,0.6141,0.6072,0.6003,0.5934,0.5867,0.5804,0.5743,0.5685,0.563,0.5577
       ,0.5527,0.5481,0.5438,0.5397,0.5325,0.5264,0.5211,0.5168,0.5133,0.5105,0.5084,0.5067,0.5054,0.504,0.503,0.5022,0.5016,0.501,0.5006
       ,0.4998,0.4995,0.4992,0.499,0.4988};
         }

     //create graph and assign data to it:
     ui->customPlot->addGraph();
     ui->customPlot->graph(0)->setData(x, y);
     // give the axes some labels:
     ui->customPlot->xAxis->setLabel("x");
     ui->customPlot->yAxis->setLabel("y");
     // set axes ranges, so we see all data:
     ui->customPlot->xAxis->setRange(0, 5);
     ui->customPlot->yAxis->setRange(0, 1);
     ui->customPlot->replot();
     */
   }


void MainWindow::on_Cmbx_mindegmil_2_currentIndexChanged(int index)
{

    if(current_index == 0)
    {
        if(index == 1)
        {
            QString dtext_GunElevation1 =  ui->LineEdit_GunElevation1_2->displayText();
            QString dtext_GunElevation2 =  ui->LineEdit_GunElevation2_2->displayText();
            conv_vall_GunElevation1 = dtext_GunElevation1.toDouble();
            conv_vall_GunElevation2 = dtext_GunElevation2.toDouble();
            conv_vall_GunElevation1 = conv_vall_GunElevation1 / 60;
            conv_vall_GunElevation2 = conv_vall_GunElevation2 / 60;
            ui->LineEdit_GunElevation1_2->setText(QString::number(conv_vall_GunElevation1,'f',2));
            ui->LineEdit_GunElevation2_2->setText(QString::number(conv_vall_GunElevation2,'f',2));
            current_index = 1;
        }
        if(index == 2)
        {
            QString dtext_GunElevation1 =  ui->LineEdit_GunElevation1_2->displayText();
            QString dtext_GunElevation2 =  ui->LineEdit_GunElevation2_2->displayText();
            conv_vall_GunElevation1 = dtext_GunElevation1.toDouble();
            conv_vall_GunElevation2 = dtext_GunElevation2.toDouble();
            conv_vall_GunElevation1 = conv_vall_GunElevation1 / (3.375);
            conv_vall_GunElevation2 = conv_vall_GunElevation2 / (3.375);
            ui->LineEdit_GunElevation1_2->setText(QString::number(conv_vall_GunElevation1,'f',2));
            ui->LineEdit_GunElevation2_2->setText(QString::number(conv_vall_GunElevation2,'f',2));
            current_index = 2;
        }

    }
    else if(current_index == 1)
    {
        if(index == 0)
        {
            QString dtext_GunElevation1 =  ui->LineEdit_GunElevation1_2->displayText();
            QString dtext_GunElevation2 =  ui->LineEdit_GunElevation2_2->displayText();
            conv_vall_GunElevation1 = dtext_GunElevation1.toDouble();
            conv_vall_GunElevation2 = dtext_GunElevation2.toDouble();
            conv_vall_GunElevation1 = conv_vall_GunElevation1 * 60;
            conv_vall_GunElevation2 = conv_vall_GunElevation2 * 60;
            ui->LineEdit_GunElevation1_2->setText(QString::number(conv_vall_GunElevation1,'f',2));
            ui->LineEdit_GunElevation2_2->setText(QString::number(conv_vall_GunElevation2,'f',2));
            current_index = 0;
        }
        if(index == 2)
        {
            QString dtext_GunElevation1 =  ui->LineEdit_GunElevation1_2->displayText();
            QString dtext_GunElevation2 =  ui->LineEdit_GunElevation2_2->displayText();
            conv_vall_GunElevation1 = dtext_GunElevation1.toDouble();
            conv_vall_GunElevation2 = dtext_GunElevation2.toDouble();
            conv_vall_GunElevation1 = round(conv_vall_GunElevation1 * 17.77766666666666);
            conv_vall_GunElevation2 = round(conv_vall_GunElevation2 * 17.77766666666666);
            ui->LineEdit_GunElevation1_2->setText(QString::number(conv_vall_GunElevation1,'f',2));
            ui->LineEdit_GunElevation2_2->setText(QString::number(conv_vall_GunElevation2,'f',2));
            current_index = 2;
        }

    }
    else if (current_index == 2)
    {
        if(index == 0)
        {
            QString dtext_GunElevation1 =  ui->LineEdit_GunElevation1_2->displayText();
            QString dtext_GunElevation2 =  ui->LineEdit_GunElevation2_2->displayText();
            conv_vall_GunElevation1 = dtext_GunElevation1.toDouble();
            conv_vall_GunElevation2 = dtext_GunElevation2.toDouble();
            conv_vall_GunElevation1 = round(conv_vall_GunElevation1 * 3.375);
            conv_vall_GunElevation2 = round(conv_vall_GunElevation2 * 3.375);
            ui->LineEdit_GunElevation1_2->setText(QString::number(conv_vall_GunElevation1,'f',2));
            ui->LineEdit_GunElevation2_2->setText(QString::number(conv_vall_GunElevation2,'f',2));
            current_index = 0;
        }
        if(index == 1)
        {
            QString dtext_GunElevation1 =  ui->LineEdit_GunElevation1_2->displayText();
            QString dtext_GunElevation2 =  ui->LineEdit_GunElevation2_2->displayText();
            conv_vall_GunElevation1 = dtext_GunElevation1.toDouble();
            conv_vall_GunElevation2 = dtext_GunElevation2.toDouble();
            conv_vall_GunElevation1 = round(conv_vall_GunElevation1 / 17.77766666666666);
            conv_vall_GunElevation2 = round(conv_vall_GunElevation2 / 17.77766666666666);
            ui->LineEdit_GunElevation1_2->setText(QString::number(conv_vall_GunElevation1,'f',2));
            ui->LineEdit_GunElevation2_2->setText(QString::number(conv_vall_GunElevation2,'f',2));
            current_index = 1;
        }
    }

}

void MainWindow::on_comboBox_SelectGun_currentIndexChanged(int index)
{
    if(current_index_for_gun == 0)
    {
        if(index == 0)
        {
            fpr_dragfunction=kilinc2000.gun_dragfunction;fpr_muzzle_velocity=kilinc2000.gun_muzzle_velocity;fpr_balcoefficient=kilinc2000.gun_balcoefficient;fpr_heightofsight=kilinc2000.gun_heightofsight;fpr_gunelevation1=kilinc2000.gun_gunelevation1;fpr_airtemperature=kilinc2000.gun_airtemperature;fpr_airpressure=kilinc2000.gun_airpressure;fpr_humidity=kilinc2000.gun_humidity;fpr_altitude=kilinc2000.gun_altitude;fpr_headwindspeed=kilinc2000.gun_headwindspeed;fpr_crosswindspeed=kilinc2000.gun_crosswindspeed;fpr_graphXend=kilinc2000.gun_grapXend;fpr_step=kilinc2000.gun_step;fpr_traj_range=kilinc2000.gun_traj_range;fpr_range2=kilinc2000.gun_range2;fpr_wall=kilinc2000.gun_wall;fpr_scalingat45deg=kilinc2000.gun_scalingat45deg/220;
        }
        if(index == 1)
        {
            fpr_dragfunction=glock19.gun_dragfunction;fpr_muzzle_velocity=glock19.gun_muzzle_velocity;fpr_balcoefficient=glock19.gun_balcoefficient;fpr_heightofsight=glock19.gun_heightofsight;fpr_gunelevation1=glock19.gun_gunelevation1;fpr_airtemperature=glock19.gun_airtemperature;fpr_airpressure=glock19.gun_airpressure;fpr_humidity=glock19.gun_humidity;fpr_altitude=glock19.gun_altitude;fpr_headwindspeed=glock19.gun_headwindspeed;fpr_crosswindspeed=glock19.gun_crosswindspeed;fpr_graphXend=glock19.gun_grapXend;fpr_step=glock19.gun_step;fpr_traj_range=glock19.gun_traj_range;fpr_range2=glock19.gun_range2;fpr_wall=glock19.gun_wall,fpr_scalingat45deg=glock19.gun_scalingat45deg/220;
        }

        if(index == 2)
        {
            fpr_dragfunction=sigsauer.gun_dragfunction;fpr_muzzle_velocity=sigsauer.gun_muzzle_velocity;fpr_balcoefficient=sigsauer.gun_balcoefficient;fpr_heightofsight=sigsauer.gun_heightofsight;fpr_gunelevation1=sigsauer.gun_gunelevation1;fpr_airtemperature=sigsauer.gun_airtemperature;fpr_airpressure=sigsauer.gun_airpressure;fpr_humidity=sigsauer.gun_humidity;fpr_altitude=sigsauer.gun_altitude;fpr_headwindspeed=sigsauer.gun_headwindspeed;fpr_crosswindspeed=sigsauer.gun_crosswindspeed;fpr_graphXend=sigsauer.gun_grapXend;fpr_step=sigsauer.gun_step;fpr_traj_range=sigsauer.gun_traj_range;fpr_range2=sigsauer.gun_range2;fpr_wall=sigsauer.gun_wall,fpr_scalingat45deg=sigsauer.gun_scalingat45deg/220;
        }
        if(index == 3)
        {
            fpr_dragfunction=mp5.gun_dragfunction;fpr_muzzle_velocity=mp5.gun_muzzle_velocity;fpr_balcoefficient=mp5.gun_balcoefficient;fpr_heightofsight=mp5.gun_heightofsight;fpr_gunelevation1=mp5.gun_gunelevation1;fpr_airtemperature=mp5.gun_airtemperature;fpr_airpressure=mp5.gun_airpressure;fpr_humidity=mp5.gun_humidity;fpr_altitude=mp5.gun_altitude;fpr_headwindspeed=mp5.gun_headwindspeed;fpr_crosswindspeed=mp5.gun_crosswindspeed;fpr_graphXend=mp5.gun_grapXend;fpr_step=mp5.gun_step;fpr_traj_range=mp5.gun_traj_range;fpr_range2=mp5.gun_range2;fpr_wall=mp5.gun_wall,fpr_scalingat45deg=mp5.gun_scalingat45deg/220;
        }
        if(index == 4)
        {
            fpr_dragfunction=mpt76.gun_dragfunction;fpr_muzzle_velocity=mpt76.gun_muzzle_velocity;fpr_balcoefficient=mpt76.gun_balcoefficient;fpr_heightofsight=mpt76.gun_heightofsight;fpr_gunelevation1=mpt76.gun_gunelevation1;fpr_airtemperature=mpt76.gun_airtemperature;fpr_airpressure=mpt76.gun_airpressure;fpr_humidity=mpt76.gun_humidity;fpr_altitude=mpt76.gun_altitude;fpr_headwindspeed=mpt76.gun_headwindspeed;fpr_crosswindspeed=mpt76.gun_crosswindspeed;fpr_graphXend=mpt76.gun_grapXend;fpr_step=mpt76.gun_step;fpr_traj_range=mpt76.gun_traj_range;fpr_range2=mpt76.gun_range2;fpr_wall=mpt76.gun_wall,fpr_scalingat45deg=mpt76.gun_scalingat45deg/220;
        }
        if(index == 5)
        {
            fpr_dragfunction=fn_minimi.gun_dragfunction;fpr_muzzle_velocity=fn_minimi.gun_muzzle_velocity;fpr_balcoefficient=fn_minimi.gun_balcoefficient;fpr_heightofsight=fn_minimi.gun_heightofsight;fpr_gunelevation1=fn_minimi.gun_gunelevation1;fpr_airtemperature=fn_minimi.gun_airtemperature;fpr_airpressure=fn_minimi.gun_airpressure;fpr_humidity=fn_minimi.gun_humidity;fpr_altitude=fn_minimi.gun_altitude;fpr_headwindspeed=fn_minimi.gun_headwindspeed;fpr_crosswindspeed=fn_minimi.gun_crosswindspeed;fpr_graphXend=fn_minimi.gun_grapXend;fpr_step=fn_minimi.gun_step;fpr_traj_range=fn_minimi.gun_traj_range;fpr_range2=fn_minimi.gun_range2;fpr_wall=fn_minimi.gun_wall,fpr_scalingat45deg=fn_minimi.gun_scalingat45deg/220;
        }
        if(index == 6)
        {
            fpr_dragfunction=m2browning.gun_dragfunction;fpr_muzzle_velocity=m2browning.gun_muzzle_velocity;fpr_balcoefficient=m2browning.gun_balcoefficient;fpr_heightofsight=m2browning.gun_heightofsight;fpr_gunelevation1=m2browning.gun_gunelevation1;fpr_airtemperature=m2browning.gun_airtemperature;fpr_airpressure=m2browning.gun_airpressure;fpr_humidity=m2browning.gun_humidity;fpr_altitude=m2browning.gun_altitude;fpr_headwindspeed=m2browning.gun_headwindspeed;fpr_crosswindspeed=m2browning.gun_crosswindspeed;fpr_graphXend=m2browning.gun_grapXend;fpr_step=m2browning.gun_step;fpr_traj_range=m2browning.gun_traj_range;fpr_range2=m2browning.gun_range2;fpr_wall=m2browning.gun_wall,fpr_scalingat45deg=m2browning.gun_scalingat45deg/220;
        }
        if(index == 7)
        {
            fpr_dragfunction=bora12.gun_dragfunction;fpr_muzzle_velocity=bora12.gun_muzzle_velocity;fpr_balcoefficient=bora12.gun_balcoefficient;fpr_heightofsight=bora12.gun_heightofsight;fpr_gunelevation1=bora12.gun_gunelevation1;fpr_airtemperature=bora12.gun_airtemperature;fpr_airpressure=bora12.gun_airpressure;fpr_humidity=bora12.gun_humidity;fpr_altitude=bora12.gun_altitude;fpr_headwindspeed=bora12.gun_headwindspeed;fpr_crosswindspeed=bora12.gun_crosswindspeed;fpr_graphXend=bora12.gun_grapXend;fpr_step=bora12.gun_step;fpr_traj_range=bora12.gun_traj_range;fpr_range2=bora12.gun_range2;fpr_wall=bora12.gun_wall,fpr_scalingat45deg=bora12.gun_scalingat45deg/220;
        }
        if(index == 8)
        {
            fpr_dragfunction=barretm82a1.gun_dragfunction;fpr_muzzle_velocity=barretm82a1.gun_muzzle_velocity;fpr_balcoefficient=barretm82a1.gun_balcoefficient;fpr_heightofsight=barretm82a1.gun_heightofsight;fpr_gunelevation1=barretm82a1.gun_gunelevation1;fpr_airtemperature=barretm82a1.gun_airtemperature;fpr_airpressure=barretm82a1.gun_airpressure;fpr_humidity=barretm82a1.gun_humidity;fpr_altitude=barretm82a1.gun_altitude;fpr_headwindspeed=barretm82a1.gun_headwindspeed;fpr_crosswindspeed=barretm82a1.gun_crosswindspeed;fpr_graphXend=barretm82a1.gun_grapXend;fpr_step=barretm82a1.gun_step;fpr_traj_range=barretm82a1.gun_traj_range;fpr_range2=barretm82a1.gun_range2;fpr_wall=barretm82a1.gun_wall,fpr_scalingat45deg=barretm82a1.gun_scalingat45deg/220;
        }
        if(index == 9)
        {
            fpr_dragfunction=mk19bomb.gun_dragfunction;fpr_muzzle_velocity=mk19bomb.gun_muzzle_velocity;fpr_balcoefficient=mk19bomb.gun_balcoefficient;fpr_heightofsight=mk19bomb.gun_heightofsight;fpr_gunelevation1=mk19bomb.gun_gunelevation1;fpr_airtemperature=mk19bomb.gun_airtemperature;fpr_airpressure=mk19bomb.gun_airpressure;fpr_humidity=mk19bomb.gun_humidity;fpr_altitude=mk19bomb.gun_altitude;fpr_headwindspeed=mk19bomb.gun_headwindspeed;fpr_crosswindspeed=mk19bomb.gun_crosswindspeed;fpr_graphXend=mk19bomb.gun_grapXend;fpr_step=mk19bomb.gun_step;fpr_traj_range=mk19bomb.gun_traj_range;fpr_range2=mk19bomb.gun_range2;fpr_wall=mk19bomb.gun_wall,fpr_scalingat45deg=mk19bomb.gun_scalingat45deg/220;
        }
        if(index == 10)
        {
            fpr_dragfunction=impalaplus12.gun_dragfunction;fpr_muzzle_velocity=impalaplus12.gun_muzzle_velocity;fpr_balcoefficient=impalaplus12.gun_balcoefficient;fpr_heightofsight=impalaplus12.gun_heightofsight;fpr_gunelevation1=impalaplus12.gun_gunelevation1;fpr_airtemperature=impalaplus12.gun_airtemperature;fpr_airpressure=impalaplus12.gun_airpressure;fpr_humidity=impalaplus12.gun_humidity;fpr_altitude=impalaplus12.gun_altitude;fpr_headwindspeed=impalaplus12.gun_headwindspeed;fpr_crosswindspeed=impalaplus12.gun_crosswindspeed;fpr_graphXend=impalaplus12.gun_grapXend;fpr_step=impalaplus12.gun_step;fpr_traj_range=impalaplus12.gun_traj_range;fpr_range2=impalaplus12.gun_range2;fpr_wall=impalaplus12.gun_wall,fpr_scalingat45deg=impalaplus12.gun_scalingat45deg/220;
        }
        if(index == 11)
        {
            fpr_dragfunction=ut1havan.gun_dragfunction;fpr_muzzle_velocity=ut1havan.gun_muzzle_velocity;fpr_balcoefficient=ut1havan.gun_balcoefficient;fpr_heightofsight=ut1havan.gun_heightofsight;fpr_gunelevation1=ut1havan.gun_gunelevation1;fpr_airtemperature=ut1havan.gun_airtemperature;fpr_airpressure=ut1havan.gun_airpressure;fpr_humidity=ut1havan.gun_humidity;fpr_altitude=ut1havan.gun_altitude;fpr_headwindspeed=ut1havan.gun_headwindspeed;fpr_crosswindspeed=ut1havan.gun_crosswindspeed;fpr_graphXend=ut1havan.gun_grapXend;fpr_step=ut1havan.gun_step;fpr_traj_range=ut1havan.gun_traj_range;fpr_range2=ut1havan.gun_range2;fpr_wall=ut1havan.gun_wall,fpr_scalingat45deg=ut1havan.gun_scalingat45deg/220;
        }
        if(index == 12)
        {
            fpr_dragfunction=mpt55.gun_dragfunction;fpr_muzzle_velocity=mpt55.gun_muzzle_velocity;fpr_balcoefficient=mpt55.gun_balcoefficient;fpr_heightofsight=mpt55.gun_heightofsight;fpr_gunelevation1=mpt55.gun_gunelevation1;fpr_airtemperature=mpt55.gun_airtemperature;fpr_airpressure=mpt55.gun_airpressure;fpr_humidity=mpt55.gun_humidity;fpr_altitude=mpt55.gun_altitude;fpr_headwindspeed=mpt55.gun_headwindspeed;fpr_crosswindspeed=mpt55.gun_crosswindspeed;fpr_graphXend=mpt55.gun_grapXend;fpr_step=mpt55.gun_step;fpr_traj_range=mpt55.gun_traj_range;fpr_range2=mpt55.gun_range2;fpr_wall=mpt55.gun_wall,fpr_scalingat45deg=mpt55.gun_scalingat45deg/220;
        }
        if(index == 13)
        {
            fpr_dragfunction=sar109t.gun_dragfunction;fpr_muzzle_velocity=sar109t.gun_muzzle_velocity;fpr_balcoefficient=sar109t.gun_balcoefficient;fpr_heightofsight=sar109t.gun_heightofsight;fpr_gunelevation1=sar109t.gun_gunelevation1;fpr_airtemperature=sar109t.gun_airtemperature;fpr_airpressure=sar109t.gun_airpressure;fpr_humidity=sar109t.gun_humidity;fpr_altitude=sar109t.gun_altitude;fpr_headwindspeed=sar109t.gun_headwindspeed;fpr_crosswindspeed=sar109t.gun_crosswindspeed;fpr_graphXend=sar109t.gun_grapXend;fpr_step=sar109t.gun_step;fpr_traj_range=sar109t.gun_traj_range;fpr_range2=sar109t.gun_range2;fpr_wall=sar109t.gun_wall,fpr_scalingat45deg=sar109t.gun_scalingat45deg/220;
        }
        if(index == 14)
        {
            fpr_dragfunction=knt76.gun_dragfunction;fpr_muzzle_velocity=knt76.gun_muzzle_velocity;fpr_balcoefficient=knt76.gun_balcoefficient;fpr_heightofsight=knt76.gun_heightofsight;fpr_gunelevation1=knt76.gun_gunelevation1;fpr_airtemperature=knt76.gun_airtemperature;fpr_airpressure=knt76.gun_airpressure;fpr_humidity=knt76.gun_humidity;fpr_altitude=knt76.gun_altitude;fpr_headwindspeed=knt76.gun_headwindspeed;fpr_crosswindspeed=knt76.gun_crosswindspeed;fpr_graphXend=knt76.gun_grapXend;fpr_step=knt76.gun_step;fpr_traj_range=knt76.gun_traj_range;fpr_range2=knt76.gun_range2;fpr_wall=knt76.gun_wall,fpr_scalingat45deg=knt76.gun_scalingat45deg/220;
        }
        if(index == 15)
        {
            fpr_dragfunction=rpg7.gun_dragfunction;fpr_muzzle_velocity=rpg7.gun_muzzle_velocity;fpr_balcoefficient=rpg7.gun_balcoefficient;fpr_heightofsight=rpg7.gun_heightofsight;fpr_gunelevation1=rpg7.gun_gunelevation1;fpr_airtemperature=rpg7.gun_airtemperature;fpr_airpressure=rpg7.gun_airpressure;fpr_humidity=rpg7.gun_humidity;fpr_altitude=rpg7.gun_altitude;fpr_headwindspeed=rpg7.gun_headwindspeed;fpr_crosswindspeed=rpg7.gun_crosswindspeed;fpr_graphXend=rpg7.gun_grapXend;fpr_step=rpg7.gun_step;fpr_traj_range=rpg7.gun_traj_range;fpr_range2=rpg7.gun_range2;fpr_wall=rpg7.gun_wall,fpr_scalingat45deg=rpg7.gun_scalingat45deg/220;
        }
        if(index == 16)
        {
            fpr_dragfunction=law.gun_dragfunction;fpr_muzzle_velocity=law.gun_muzzle_velocity;fpr_balcoefficient=law.gun_balcoefficient;fpr_heightofsight=law.gun_heightofsight;fpr_gunelevation1=law.gun_gunelevation1;fpr_airtemperature=law.gun_airtemperature;fpr_airpressure=law.gun_airpressure;fpr_humidity=law.gun_humidity;fpr_altitude=law.gun_altitude;fpr_headwindspeed=law.gun_headwindspeed;fpr_crosswindspeed=law.gun_crosswindspeed;fpr_graphXend=law.gun_grapXend;fpr_step=law.gun_step;fpr_traj_range=law.gun_traj_range;fpr_range2=law.gun_range2;fpr_wall=law.gun_wall,fpr_scalingat45deg=law.gun_scalingat45deg/220;
        }

        ResultList.clear();
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setRowCount(0);
        dragfunc_cmbx_index = ui->Cmbx_DragFunction_2->findText(QString::fromStdString(fpr_dragfunction));
        ui->Cmbx_DragFunction_2->setCurrentIndex(dragfunc_cmbx_index);
        fpr_dragfunction = ui->Cmbx_DragFunction_2->currentText().toStdString();
        initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
        ui->customPlot_2->clearItems();
        ui->customPlot_3->clearItems();
        makePlot(delement_order);
        ui->LineEdit_MuzzleVelocity_2->setText(QString::number(fpr_muzzle_velocity) + " m/sec");
        ui->LineEdit_BalisticsCoefficient_2->setText(QString::number(fpr_balcoefficient,'f',3));
        ui->LineEdit_HeightofSight_2->setText(QString::number(fpr_heightofsight,'f',2) + " cm");
        ui->LineEdit_GunElevation1_2->setText(QString::number(fpr_gunelevation1,'f',2));
        ui->LineEdit_GunElevation2_2->setText(QString::number(fpr_gunelevation1,'f',2));
        ui->LineEdit_AirTemperature_2->setText(QString::number(fpr_airtemperature,'f',1) + " °C");
        ui->LineEdit_AirPressure_2->setText(QString::number(fpr_airpressure) + " mmHg");
        ui->LineEdit_Humidity_2->setText(QString::number(fpr_humidity) + " %");
        ui->LineEdit_Altitude_2->setText(QString::number(fpr_altitude) + " m");
        ui->LineEdit_HeadWindSpeed_2->setText(QString::number(fpr_headwindspeed) + " km/h");
        ui->LineEdit_CrossWindSpeed_2->setText(QString::number(fpr_crosswindspeed) + " km/h");
        ui->LineEdit_GraphXEnd_2->setText(QString::number(fpr_graphXend) + " m");
        ui->LineEdit_Interval_2->setText(QString::number(fpr_step) + " m");
        ui->LineEdit_TrajRange_2->setText(QString::number(fpr_traj_range) + " m");
        ui->LineEdit_Range2_2->setText(QString::number(fpr_range2) + " m");
        ui->LineEdit_Wall_2->setText(QString::number(fpr_wall) + " m");
        ui->LineEdit_AirTemperature_3->setText(QString::number(fpr_airtemperature,'f',1) + " °C");
        ui->LineEdit_AirPressure_3->setText(QString::number(fpr_airpressure) + " mmHg");
        ui->LineEdit_Humidity_3->setText(QString::number(fpr_humidity) + " %");
        ui->LineEdit_Altitude_3->setText(QString::number(fpr_altitude) + " m");
        ui->LineEdit_HeadWindSpeed_3->setText(QString::number(fpr_headwindspeed) + " km/h");
        ui->LineEdit_CrossWindSpeed_3->setText(QString::number(fpr_crosswindspeed) + " km/h");
    }
}

void MainWindow::on_Cmbx_DragFunction_2_currentTextChanged(const QString &arg1)
{
    ResultList.clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    dragfunc_cmbx_index = ui->Cmbx_DragFunction_2->findText(arg1);
    ui->Cmbx_DragFunction_2->setCurrentIndex(dragfunc_cmbx_index);
    fpr_dragfunction = ui->Cmbx_DragFunction_2->currentText().toStdString();
    ui->Cmbx_DragFunction_2->setCurrentText(QString::fromStdString(fpr_dragfunction));
    initTableWidget(fpr_dragfunction,fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_gridxm,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot_2->clearItems();
    ui->customPlot_3->clearItems();
    makePlot(delement_order);
}
