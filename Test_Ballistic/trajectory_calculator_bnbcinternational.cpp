#include "trajectory_calculator_bnbcinternational.h"
#include "ui_trajectory_calculator_bnbcinternational.h"

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

using namespace std;

Trajectory_Calculator_BnbcInternational::Trajectory_Calculator_BnbcInternational(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Trajectory_Calculator_BnbcInternational)
{
    ui->setupUi(this);

    Trajectory_Calculator_BnbcInternational::makePlot(delement_order);
    Trajectory_Calculator_BnbcInternational::initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);





    value_TrajRange_edited = ui->LineEdit_TrajRange->displayText();
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

Trajectory_Calculator_BnbcInternational::~Trajectory_Calculator_BnbcInternational()
{
    delete ui;
}


void Trajectory_Calculator_BnbcInternational::on_pushButton_Select_clicked()
{
    Select_Bullets slct;
    slct.setModal(false);
    slct.show();
    slct.exec();

    if(slct.ok_clicked)
    {
    ui->LineEdit_MuzzleVelocity->setText(slct.fromsecond_valvelocity);
    ui->LineEdit_BalisticsCoefficient->setText(slct.fromsecond_valbc);
    on_LineEdit_MuzzleVelocity_textEdited(slct.fromsecond_valvelocity);
    on_LineEdit_MuzzleVelocity_returnPressed();
    on_LineEdit_BalisticsCoefficient_textEdited(slct.fromsecond_valbc);
    on_LineEdit_BalisticsCoefficient_returnPressed();
    }
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_MuzzleVelocity_textEdited(const QString &arg1)
{
    value_muzzlevelocity_edited = arg1;
    if((value_muzzlevelocity_edited == "")){}else{
    muzzlevelocity_edited = value_muzzlevelocity_edited.split(' ');
    ui->LineEdit_MuzzleVelocity->setText(muzzlevelocity_edited[0]);
    order= 1;
    delement_order[0] = muzzlevelocity_edited[0].toDouble();
    delement_order[1] = order;
    fpr_muzzle_velocity   = muzzlevelocity_edited[0].toDouble();
    }
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_MuzzleVelocity_returnPressed()
{
    ui->customPlot->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);

    value_muzzlevelocity  = ui->LineEdit_MuzzleVelocity->displayText();
    muzzle_velocity       = value_muzzlevelocity.split('m');
    if(muzzle_velocity[0] == "" || muzzle_velocity[0] == "m" || muzzle_velocity[0] == "m/" || muzzle_velocity[0] == "m/s" || muzzle_velocity[0] == "m/s" || muzzle_velocity[0] == "m/se" ||  muzzle_velocity[0] == "m/sec") {ui->LineEdit_MuzzleVelocity->setText("1 m/sec");}
    else{ui->LineEdit_MuzzleVelocity->setText(muzzle_velocity[0] + " m/sec");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_BalisticsCoefficient_textEdited(const QString &arg1)
{
    value_BalisticsCoefficient = arg1;
    if(value_BalisticsCoefficient == "" || value_BalisticsCoefficient == "0" || value_BalisticsCoefficient == "0." || value_BalisticsCoefficient == "0.0"){}else{
    ballisticcoefficient_edited = value_BalisticsCoefficient.split(' ');
    ui->LineEdit_BalisticsCoefficient->setText(ballisticcoefficient_edited[0]);
    order= 2;
    delement_order[0]  = ballisticcoefficient_edited[0].toDouble();
    delement_order[1]  = order;
    fpr_balcoefficient = ballisticcoefficient_edited[0].toDouble();
    }
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_BalisticsCoefficient_returnPressed()
{
    ui->customPlot->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);


    value_BalisticsCoefficient = ui->LineEdit_BalisticsCoefficient->displayText();
    if(value_BalisticsCoefficient == "") {ui->LineEdit_BalisticsCoefficient->setText("0.000");}
    else{ui->LineEdit_BalisticsCoefficient->setText(value_BalisticsCoefficient);}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_HeightofSight_textEdited(const QString &arg1)
{
    value_HeightofSight_edited = arg1;
    HeightofSight_edited = value_HeightofSight_edited.split(' ');
    ui->LineEdit_HeightofSight->setText(HeightofSight_edited[0]);
    order= 3;
    delement_order[0] = HeightofSight_edited[0].toDouble();
    delement_order[1] = order;
    fpr_heightofsight = HeightofSight_edited[0].toDouble();
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_HeightofSight_returnPressed()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->customPlot->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);

    value_HeightofSight = ui->LineEdit_HeightofSight->displayText();
    HeightofSight = value_HeightofSight.split(' ');
    if(HeightofSight[0] == "" || HeightofSight[0] == "c" || HeightofSight[0] == "cm") {ui->LineEdit_HeightofSight->setText("1.00 cm");}
    else{ui->LineEdit_HeightofSight->setText(HeightofSight[0] + " cm");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_GunElevation1_textEdited(const QString &arg1)
{
    value_GunElevation1_edited = arg1;
    GunElevation1_edited = value_GunElevation1_edited.split(' ');
    ui->LineEdit_GunElevation1->setText(GunElevation1_edited[0]);
    order= 4;
    delement_order[0] = GunElevation1_edited[0].toDouble();
    delement_order[1] = order;
    fpr_gunelevation1 = GunElevation1_edited[0].toDouble();  
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_GunElevation1_returnPressed()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->customPlot->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->customPlot->clearItems();
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);

    value_GunElevation1 = ui->LineEdit_GunElevation1->displayText();
    if(value_GunElevation1 == "") {ui->LineEdit_GunElevation1->setText("0.00");}
    else{ui->LineEdit_GunElevation1->setText(QString::number(fpr_gunelevation1, 'f', 2));}
    ui->LineEdit_GunElevation2->setText(QString::number(fpr_gunelevation1, 'f', 2));
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_GunElevation2_textEdited(const QString &arg1)
{
    value_GunElevation2 = arg1;
    order= 5;
    delement_order[0] = value_GunElevation2.toDouble();
    delement_order[1] = order;
    makePlot(delement_order);
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_GunElevation2_returnPressed()
{
    /* do somethings */
    value_GunElevation2 = ui->LineEdit_GunElevation2->displayText();
    if(value_GunElevation2 == "") {ui->LineEdit_GunElevation2->setText("0.000");}
    else{ui->LineEdit_GunElevation2->setText((value_GunElevation2));}
}

void Trajectory_Calculator_BnbcInternational::on_Cmbx_mindegmil_currentTextChanged(const QString &arg1)
{
    /* do somethings */
    QString a= arg1;
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_AirTemperature_textEdited(const QString &arg1)
{
    value_AirTemperature_edited = arg1;
    AirTemperature_edited = value_AirTemperature_edited.split(' ');
    ui->LineEdit_AirTemperature->setText(AirTemperature_edited[0]);
    order= 6;
    delement_order[0] = AirTemperature_edited[0].toDouble();
    delement_order[1] = order;
    fpr_airtemperature = AirTemperature_edited[0].toDouble();
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_AirTemperature_returnPressed()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->customPlot->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);

    value_AirTemperature = ui->LineEdit_AirTemperature->displayText();
    AirTemperature = value_AirTemperature.split(' ');
    if(AirTemperature[0] == "°" ||AirTemperature[0] == "C") {ui->LineEdit_AirTemperature->setText("1.00 °C");}
    else{ui->LineEdit_AirTemperature->setText(QString::number(fpr_airtemperature,'f',1)+" °C");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_AirPressure_textEdited(const QString &arg1)
{
    value_AirPressure_edited = arg1;
    if(value_AirPressure_edited == "") {} else {
    AirPressure_edited = value_AirPressure_edited.split(' ');
    ui->LineEdit_AirPressure->setText(AirPressure_edited[0]);
    order= 7;
    delement_order[0] = AirPressure_edited[0].toDouble();
    delement_order[1] = order;
    fpr_airpressure = AirPressure_edited[0].toDouble();
    }
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_AirPressure_returnPressed()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->customPlot->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);

    value_AirPressure = ui->LineEdit_AirPressure->displayText();
    AirPressure = value_AirPressure.split(' ');
    if(AirPressure[0] == "" || AirPressure[0] == "m" || AirPressure[0] == "mm" || AirPressure[0] == "mmH" || AirPressure[0] == "mmHg") {ui->LineEdit_AirPressure->setText("1.00 mmHg");}
    else{ui->LineEdit_AirPressure->setText(AirPressure[0] + " mmHg");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_Humidity_textEdited(const QString &arg1)
{
    value_Humidity_edited = arg1;
    Humidity_edited = value_Humidity_edited.split(' ');
    ui->LineEdit_Humidity->setText(Humidity_edited[0]);
    order= 8;
    delement_order[0] = Humidity_edited[0].toDouble();
    delement_order[1] = order;
    fpr_humidity = Humidity_edited[0].toDouble();

}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_Humidity_returnPressed()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->customPlot->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);

    value_Humidity = ui->LineEdit_Humidity->displayText();
    Humidityy = value_Humidity.split(' ');
    if(Humidityy[0] == "" || Humidityy[0] == "%") {ui->LineEdit_Humidity->setText("1 %");}
    else{ui->LineEdit_Humidity->setText(Humidityy[0] + " %");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_Altitude_textEdited(const QString &arg1)
{
    value_Altitude_edited = arg1;
    Altitude_edited = value_Altitude_edited.split(' ');
    ui->LineEdit_Altitude->setText(Altitude_edited[0]);
    order= 9;
    delement_order[0] = Altitude_edited[0].toDouble();
    delement_order[1] = order;
    fpr_altitude = Altitude_edited[0].toDouble();

}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_Altitude_returnPressed()
{
    /*** changement of air temperature and air pressure ***/
    if(ui->LineEdit_Altitude->displayText() == "" || ui->LineEdit_Altitude->displayText() == "1" || ui->LineEdit_Altitude->displayText() == "2" || ui->LineEdit_Altitude->displayText() == "3" )
    {
    fpr_airpressure = 750;
    fpr_airtemperature = 15;
    ui->LineEdit_AirPressure->setText(QString::number(fpr_airpressure));
    ui->LineEdit_AirTemperature->setText(QString::number(fpr_airtemperature));
    on_LineEdit_AirPressure_returnPressed();
    on_LineEdit_AirTemperature_returnPressed();
    }

    fpr_airpressure = fpr_airpressure - round((fpr_altitude / 11));
    fpr_airtemperature = fpr_airtemperature - ((fpr_altitude / 100) * 0.5);
    ui->LineEdit_AirPressure->setText(QString::number(fpr_airpressure));
    on_LineEdit_AirPressure_returnPressed();
    ui->LineEdit_AirTemperature->setText(QString::number(fpr_airtemperature, 'f', 1));
    on_LineEdit_AirTemperature_returnPressed();


    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);
    /*** end changement of air pressure ***/
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->customPlot->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);

    value_Altitude = ui->LineEdit_Altitude->displayText();
    Altitudee = value_Altitude.split(' ');
    if(Altitudee[0] == "" || Altitudee[0] == "m") {ui->LineEdit_Altitude->setText("1 m");}
    else{ui->LineEdit_Altitude->setText(Altitudee[0] + " m");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_HeadWindSpeed_textEdited(const QString &arg1)
{

    value_HeadWindSpeed_edited = arg1;
    if(value_HeadWindSpeed_edited == ""){} else{
    HeadWindSpeed_edited = value_HeadWindSpeed_edited.split(' ');
    ui->LineEdit_HeadWindSpeed->setText(HeadWindSpeed_edited[0]);
    order= 10;
    delement_order[0] = HeadWindSpeed_edited[0].toDouble();
    delement_order[1] = order;
    fpr_headwindspeed = HeadWindSpeed_edited[0].toDouble();
    }
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_HeadWindSpeed_returnPressed()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->customPlot->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);

    value_HeadWindSpeed = ui->LineEdit_HeadWindSpeed->displayText();
    HeadWindSpeed = value_HeadWindSpeed.split(' ');
    if(HeadWindSpeed[0] == "" || HeadWindSpeed[0] == "k" || HeadWindSpeed[0] == "km" || HeadWindSpeed[0] == "km/" || HeadWindSpeed[0] == "km/h") {ui->LineEdit_HeadWindSpeed->setText("1 km/h");}
    else{ui->LineEdit_HeadWindSpeed->setText(HeadWindSpeed[0] + " km/h");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_CrossWindSpeed_textEdited(const QString &arg1)
{
    value_CrossWindSpeed_edited = arg1;
    if(value_CrossWindSpeed_edited == ""){} else{
    CrossWindSpeed_edited = value_CrossWindSpeed_edited.split(' ');
    ui->LineEdit_CrossWindSpeed->setText(CrossWindSpeed_edited[0]);
    order= 11;
    delement_order[0] = CrossWindSpeed_edited[0].toDouble();
    delement_order[1] = order;
    }
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_CrossWindSpeed_returnPressed()
{
    fpr_crosswindspeed = CrossWindSpeed_edited[0].toDouble();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->customPlot->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);

    value_CrossWindSpeed = ui->LineEdit_CrossWindSpeed->displayText();
    CrossWindSpeed = value_CrossWindSpeed.split(' ');
    if(CrossWindSpeed[0] == "" || CrossWindSpeed[0] == "k" || CrossWindSpeed[0] == "km" || CrossWindSpeed[0] == "km/" || CrossWindSpeed[0] == "km/h") {ui->LineEdit_CrossWindSpeed->setText("1 km/h");}
    else{ui->LineEdit_CrossWindSpeed->setText(CrossWindSpeed[0] + " km/h");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_Range_textEdited(const QString &arg1)
{
    value_Range_edited = arg1;
    Range_edited = value_Range_edited.split(' ');
    ui->LineEdit_Range->setText(Range_edited[0]);
    order= 12;
    delement_order[0] = Range_edited[0].toDouble();
    delement_order[1] = order;
    makePlot(delement_order);
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_Range_returnPressed()
{
    value_Range = ui->LineEdit_Range->displayText();
    Range = value_Range.split(' ');
    if(Range[0] == "" || Range[0] == "c" || Range[0] == "cm") {ui->LineEdit_Range->setText("1 cm");}
    else{ui->LineEdit_Range->setText(Range[0] + " cm");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_TargetHeight_textEdited(const QString &arg1)
{
    value_TargetHeight_edited = arg1;
    TargetHeight_edited = value_TargetHeight_edited.split(' ');
    ui->LineEdit_TargetHeight->setText(TargetHeight_edited[0]);
    order= 13;
    delement_order[0] = TargetHeight_edited[0].toDouble();
    delement_order[1] = order;
    makePlot(delement_order);
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_TargetHeight_returnPressed()
{
    value_TargetHeight = ui->LineEdit_TargetHeight->displayText();
    TargetHeight = value_TargetHeight.split(' ');
    if(TargetHeight[0] == "" || TargetHeight[0] == "c" || TargetHeight[0] == "cm") {ui->LineEdit_TargetHeight->setText("1 cm");}
    else{ui->LineEdit_TargetHeight->setText(TargetHeight[0] + " cm");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_GraphXEnd_textEdited(const QString &arg1)
{
    value_GraphXEnd_edited = arg1;
    GraphXEnd_edited = value_GraphXEnd_edited.split(' ');
    ui->LineEdit_GraphXEnd->setText(GraphXEnd_edited[0]);
    fpr_graphXend = GraphXEnd_edited[0].toInt();
    order= 14;
    delement_order[0] = GraphXEnd_edited[0].toDouble();
    delement_order[1] = order;
    makePlot(delement_order);
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_GraphXEnd_returnPressed()
{
    value_GraphXEnd = ui->LineEdit_GraphXEnd->displayText();
    GraphXEnd = value_GraphXEnd.split(' ');
    if(GraphXEnd[0] == "" || GraphXEnd[0] == "m") {
        ui->LineEdit_GraphXEnd->setText(QString::number(fpr_traj_range) + " m");
        fpr_graphXend = fpr_traj_range;
    }
    else{ui->LineEdit_GraphXEnd->setText(GraphXEnd[0] + " m");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_Interval_textEdited(const QString &arg1)
{
    value_Interval_edited = arg1;
    Interval_edited = value_Interval_edited.split(' ');
    ui->LineEdit_Interval->setText(Interval_edited[0]);
    order= 15;
    delement_order[0] = Interval_edited[0].toDouble();
    delement_order[1] = order;


    /*
    value_TrajRange_edited = arg1;
    TrajRange_edited = value_TrajRange_edited.split(' ');
    ui->LineEdit_TrajRange->setText(TrajRange_edited[0]);
    order= 18;
    delement_order[0] = TrajRange_edited[0].toDouble();
    delement_order[1] = order;
    fpr_traj_range = TrajRange_edited[0].toDouble();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_step,fpr_traj_range);
    makePlot(delement_order);
    */
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_Interval_returnPressed()
{
    fpr_step = Interval_edited[0].toDouble();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->customPlot->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);

    value_Interval = ui->LineEdit_Interval->displayText();
    Interval = value_Interval.split(' ');
    if(Interval[0] == "" || Interval[0] == "m") {ui->LineEdit_Interval->setText("1 m");}
    else{ui->LineEdit_Interval->setText(Interval[0] + " m");}  
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_GridXm_textEdited(const QString &arg1)
{
    value_GridXm_edited = arg1;
    GridXm_edited = value_GridXm_edited.split(' ');
    ui->LineEdit_GridXm->setText(GridXm_edited[0]);
    order= 16;
    delement_order[0] = GridXm_edited[0].toDouble();
    delement_order[1] = order;
    makePlot(delement_order);
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_GridXm_returnPressed()
{
    value_GridXm = ui->LineEdit_GridXm->displayText();
    GridXm = value_GridXm.split(' ');
    if(GridXm[0] == "" || GridXm[0] == "m") {ui->LineEdit_GridXm->setText("1 m");}
    else{ui->LineEdit_GridXm->setText(GridXm[0] + " m");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_YCm_textEdited(const QString &arg1)
{
    value_YCm_edited = arg1;
    YCm_edited = value_YCm_edited.split(' ');
    ui->LineEdit_YCm->setText(YCm_edited[0]);
    order= 17;
    delement_order[0] = YCm_edited[0].toDouble();
    delement_order[1] = order;
    makePlot(delement_order);
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_YCm_returnPressed()
{
    value_YCm = ui->LineEdit_YCm->displayText();
    YCm = value_YCm.split(' ');
    if(YCm[0] == "" || YCm[0] == "c" || YCm[0] == "cm") {ui->LineEdit_YCm->setText("1 cm");}
    else{ui->LineEdit_YCm->setText(YCm[0] + " cm");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_TrajRange_textEdited(const QString &arg1)
{
    value_TrajRange_edited = arg1;
    TrajRange_edited = value_TrajRange_edited.split(' ');
    ui->LineEdit_TrajRange->setText(TrajRange_edited[0]);
    order= 18;
    delement_order[0] = TrajRange_edited[0].toDouble();
    delement_order[1] = order;
    fpr_traj_range = TrajRange_edited[0].toInt();

}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_TrajRange_returnPressed()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->customPlot->clearItems();
    makePlot(delement_order);
    ResultList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    initTableWidget(fpr_muzzle_velocity,fpr_balcoefficient,fpr_heightofsight,fpr_gunelevation1,fpr_airtemperature,fpr_airpressure,fpr_humidity,fpr_altitude,fpr_headwindspeed,fpr_crosswindspeed,fpr_graphXend,fpr_step,fpr_traj_range,fpr_range2,fpr_wall);
    ui->customPlot->clearItems();
    makePlot(delement_order);

    value_TrajRange = ui->LineEdit_TrajRange->displayText();
    TrajRange = value_TrajRange.split(' ');
    if(TrajRange[0] == "" || TrajRange[0] == "m") {ui->LineEdit_TrajRange->setText("1 m");}
    else{ui->LineEdit_TrajRange->setText(TrajRange[0] + " m");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_Range2_textEdited(const QString &arg1)
{
   value_range2_edited = arg1;
   range2_edited = value_range2_edited.split(' ');
   ui->LineEdit_Range2->setText(range2_edited[0]);
   fpr_range2 = range2_edited[0].toInt();
   order= 19;
   delement_order[0] = range2_edited[0].toDouble();
   delement_order[1] = order;
   ui->customPlot->clearItems();
   makePlot(delement_order);
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_Range2_returnPressed()
{
    value_range2 = ui->LineEdit_Range2->displayText();
    range2 = value_range2.split('m');
    if(range2[0] == "" || range2[0] == "m") {ui->LineEdit_Range2->setText("1 m");}
    else{ui->LineEdit_Range2->setText(range2[0] + " m");}
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_Wall_textEdited(const QString &arg1)
{
    value_Wall_edited = arg1;
    Wall_edited = value_Wall_edited.split(' ');
    ui->LineEdit_Wall->setText(Wall_edited[0]);
    fpr_wall = Wall_edited[0].toInt();
    order= 20;
    delement_order[0] = Wall_edited[0].toDouble();
    delement_order[1] = order;
    ui->customPlot->clearItems();
    makePlot(delement_order);
}

void Trajectory_Calculator_BnbcInternational::on_LineEdit_Wall_returnPressed()
{
    value_Wall = ui->LineEdit_Wall->displayText();
    Wall = value_Wall.split(' ');
    if(Wall[0] == "" || Wall[0] == "m") {ui->LineEdit_Wall->setText("1 m");}
    else{ui->LineEdit_Wall->setText(Wall[0] + " m");}
}

void Trajectory_Calculator_BnbcInternational::initTableWidget(double fpr_muzzle_velocity,double fpr_balcoefficient,double fpr_heightofsight,double fpr_gunelevation1,double fpr_airtemperature,double fpr_airpressure,double fpr_humidity,double fpr_altitude,double fpr_headwindspeed,double fpr_crosswindspeed,int fpr_graphXend,double fpr_step,int fpr_traj_range,int fpr_range2,int fpr_wall)
{

    const int nCols = 8;
    ui->tableWidget->setColumnCount(nCols);
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Range (m)"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Height (cm)"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Defl (cm)"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Vel (m/s)"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Time (s)"));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Vx (m/sn)"));
    ui->tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("Vy (m/sn)"));
    ui->tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("Vz (m/sn)"));

    //TEST Amaçlıdır.
        //Drag function
        DragFunction dragFunc = DragFunction::CreateDragFunction("G1");
        DragFunction drag2 = DragFunction::CreateDragFunction("G2");
        //BallisticProjector

        //BallisticProjector* bullet = new BallisticProjector(1, "Test", 2.00, false, 100.00, 10.00, 2800.0, 0.105, dragFunc);
        BallisticProjector* bullet = new BallisticProjector(1, "Test", 5.56, false, 100.00, fpr_heightofsight, (fpr_muzzle_velocity*3.28084), fpr_balcoefficient, dragFunc);
        //cout << bullet->getBallisticCoefficient() << endl;
        //cout << bullet->getDragFunction().getDragFunction() << endl;
    /*
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
           ui->tableWidget->insertRow(i);
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getDistance())));
              ui->tableWidget->setItem( i, 0, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getHeight())));
              ui->tableWidget->setItem( i, 1, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getDeflection())));
              ui->tableWidget->setItem( i, 2, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getTotalVelocity())));
              ui->tableWidget->setItem( i, 3, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getTime())));
              ui->tableWidget->setItem( i, 4, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getTheVelocityX())));
              ui->tableWidget->setItem( i, 5, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getTheVelocityY())));
              ui->tableWidget->setItem( i, 6, item );
           }
        }

        for( int i = 0; i < nRows; i++ )
        {
           for( int j = 0; j < nCols; j++ ) {
              QTableWidgetItem *item = new QTableWidgetItem( QString("%1").arg(QString::number(ResultList.at(i).getTheVelocityZ())));
              ui->tableWidget->setItem( i, 7, item );
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

void Trajectory_Calculator_BnbcInternational::makePlot(double delement_order[2])
{


    int    order          = int(delement_order[1]);
    double element_nvalue = delement_order[0];

    // generate some data:
   QVector<double> x(2000), y(2000),lazerx(2000),lazery(2000); // initialize with entries 0..100

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
       ui->customPlot->addGraph();
       ui->customPlot->graph(0)->setData(x, y);
       // give the axes some labels:
       ui->customPlot->xAxis->setLabel("x");
       ui->customPlot->yAxis->setLabel("y");
       // set axes ranges, so we see all data:
       ui->customPlot->xAxis->setRange(0, 5);
       ui->customPlot->yAxis->setRange(0, 1);
       ui->customPlot->replot();
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
       ui->customPlot->addGraph();
       ui->customPlot->graph(0)->setData(x, y);
       // give the axes some labels:
       ui->customPlot->xAxis->setLabel("x");
       ui->customPlot->yAxis->setLabel("y");
       // set axes ranges, so we see all data:
       ui->customPlot->xAxis->setRange(0, fpr_traj_range);
       ui->customPlot->xAxis->setRange(0, fpr_graphXend);
       ui->customPlot->yAxis->setRange(-155280, 155280);



       /* wall */
       QCPItemStraightLine *infLine = new QCPItemStraightLine(ui->customPlot);
       infLine->setPen(QPen(Qt::darkRed));
       infLine->point1->setCoords(fpr_wall, 0);  // location of point 1 in plot coordinate
       infLine->point2->setCoords(fpr_wall, 3);  // location of point 2 in plot coordinate


       /* zero line */
       QCPItemStraightLine *infLine2 = new QCPItemStraightLine(ui->customPlot);
       infLine2->setPen(QPen(Qt::darkGreen));
       infLine2->point1->setCoords(0, 0);  // location of point 1 in plot coordinate


       /* range2 */
       QCPItemStraightLine *infLine3 = new QCPItemStraightLine(ui->customPlot);
       infLine3->setPen(QPen(Qt::darkMagenta));
       infLine3->point1->setCoords(fpr_range2, 0);  // location of point 1 in plot coordinate
       infLine3->point2->setCoords(fpr_range2, 3);  // location of point 2 in plot coordinate




       const int nRows = ResultList.size();
       const int nCols = 8;

        QCPItemStraightLine *infLineLzr = new QCPItemStraightLine(ui->customPlot);
       for( int i = 0; i < nRows; i++ )
       {
          for( int j = 0; j < nCols; j++ ) {
           lazerx[i] = ResultList.at(i).getDistance();
           lazery[i] = ResultList.at(i).getHeight() + ResultList.at(i).getDeflection();
           /* zero line */
           infLineLzr->setPen(QPen(Qt::red));
           infLineLzr->point1->setCoords(round(lazerx[i]), round(lazery[i])*1.5);  // location of point 1 in plot coordinate
          }
          ui->lineEditDeneme_2->setText(QString::number(lazery[1]));
       }

        ui->customPlot->replot();

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

void Trajectory_Calculator_BnbcInternational::on_Cmbx_mindegmil_currentIndexChanged(int index)
{

    if(current_index == 0)
    {
        if(index == 1)
        {
            QString dtext_GunElevation1 =  ui->LineEdit_GunElevation1->displayText();
            QString dtext_GunElevation2 =  ui->LineEdit_GunElevation2->displayText();
            conv_vall_GunElevation1 = dtext_GunElevation1.toDouble();
            conv_vall_GunElevation2 = dtext_GunElevation2.toDouble();
            conv_vall_GunElevation1 = conv_vall_GunElevation1 / 60;
            conv_vall_GunElevation2 = conv_vall_GunElevation2 / 60;
            ui->LineEdit_GunElevation1->setText(QString::number(conv_vall_GunElevation1,'f',2));
            ui->LineEdit_GunElevation2->setText(QString::number(conv_vall_GunElevation2,'f',2));
            current_index = 1;
        }
        if(index == 2)
        {
            QString dtext_GunElevation1 =  ui->LineEdit_GunElevation1->displayText();
            QString dtext_GunElevation2 =  ui->LineEdit_GunElevation2->displayText();
            conv_vall_GunElevation1 = dtext_GunElevation1.toDouble();
            conv_vall_GunElevation2 = dtext_GunElevation2.toDouble();
            conv_vall_GunElevation1 = conv_vall_GunElevation1 / (3.375);
            conv_vall_GunElevation2 = conv_vall_GunElevation2 / (3.375);
            ui->LineEdit_GunElevation1->setText(QString::number(conv_vall_GunElevation1,'f',2));
            ui->LineEdit_GunElevation2->setText(QString::number(conv_vall_GunElevation2,'f',2));
            current_index = 2;
        }

    }
    else if(current_index == 1)
    {
        if(index == 0)
        {
            QString dtext_GunElevation1 =  ui->LineEdit_GunElevation1->displayText();
            QString dtext_GunElevation2 =  ui->LineEdit_GunElevation2->displayText();
            conv_vall_GunElevation1 = dtext_GunElevation1.toDouble();
            conv_vall_GunElevation2 = dtext_GunElevation2.toDouble();
            conv_vall_GunElevation1 = conv_vall_GunElevation1 * 60;
            conv_vall_GunElevation2 = conv_vall_GunElevation2 * 60;
            ui->LineEdit_GunElevation1->setText(QString::number(conv_vall_GunElevation1,'f',2));
            ui->LineEdit_GunElevation2->setText(QString::number(conv_vall_GunElevation2,'f',2));
            current_index = 0;
        }
        if(index == 2)
        {
            QString dtext_GunElevation1 =  ui->LineEdit_GunElevation1->displayText();
            QString dtext_GunElevation2 =  ui->LineEdit_GunElevation2->displayText();
            conv_vall_GunElevation1 = dtext_GunElevation1.toDouble();
            conv_vall_GunElevation2 = dtext_GunElevation2.toDouble();
            conv_vall_GunElevation1 = round(conv_vall_GunElevation1 * 17.77766666666666);
            conv_vall_GunElevation2 = round(conv_vall_GunElevation2 * 17.77766666666666);
            ui->LineEdit_GunElevation1->setText(QString::number(conv_vall_GunElevation1,'f',2));
            ui->LineEdit_GunElevation2->setText(QString::number(conv_vall_GunElevation2,'f',2));
            current_index = 2;
        }

    }
    else if (current_index == 2)
    {
        if(index == 0)
        {
            QString dtext_GunElevation1 =  ui->LineEdit_GunElevation1->displayText();
            QString dtext_GunElevation2 =  ui->LineEdit_GunElevation2->displayText();
            conv_vall_GunElevation1 = dtext_GunElevation1.toDouble();
            conv_vall_GunElevation2 = dtext_GunElevation2.toDouble();
            conv_vall_GunElevation1 = round(conv_vall_GunElevation1 * 3.375);
            conv_vall_GunElevation2 = round(conv_vall_GunElevation2 * 3.375);
            ui->LineEdit_GunElevation1->setText(QString::number(conv_vall_GunElevation1,'f',2));
            ui->LineEdit_GunElevation2->setText(QString::number(conv_vall_GunElevation2,'f',2));
            current_index = 0;
        }
        if(index == 1)
        {
            QString dtext_GunElevation1 =  ui->LineEdit_GunElevation1->displayText();
            QString dtext_GunElevation2 =  ui->LineEdit_GunElevation2->displayText();
            conv_vall_GunElevation1 = dtext_GunElevation1.toDouble();
            conv_vall_GunElevation2 = dtext_GunElevation2.toDouble();
            conv_vall_GunElevation1 = round(conv_vall_GunElevation1 / 17.77766666666666);
            conv_vall_GunElevation2 = round(conv_vall_GunElevation2 / 17.77766666666666);
            ui->LineEdit_GunElevation1->setText(QString::number(conv_vall_GunElevation1,'f',2));
            ui->LineEdit_GunElevation2->setText(QString::number(conv_vall_GunElevation2,'f',2));
            current_index = 1;
        }
    }

}
