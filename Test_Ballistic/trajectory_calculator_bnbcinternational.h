#ifndef TRAJECTORY_CALCULATOR_BNBCINTERNATIONAL_H
#define TRAJECTORY_CALCULATOR_BNBCINTERNATIONAL_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QVector>
#include <BulletCondition.h>
#include "select_bullets.h"
#include <qcustomplot.h>

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class Trajectory_Calculator_BnbcInternational;
               class Select_Bullets;}
QT_END_NAMESPACE

class Trajectory_Calculator_BnbcInternational : public QMainWindow
{
    Q_OBJECT

public:
    Trajectory_Calculator_BnbcInternational(QWidget *parent = nullptr);
    ~Trajectory_Calculator_BnbcInternational();

    //void mousePressEvent(QMouseEvent *ev);

    QString value_muzzlevelocity_edited="914.0",value_muzzlevelocity,value_BalisticsCoefficient_edited="0.338",value_BalisticsCoefficient,value_HeightofSight_edited="10.00",value_HeightofSight,value_GunElevation1_edited="1.00",value_GunElevation1="0.0",value_GunElevation2="45.00",value_AirTemperature_edited="15",value_AirTemperature,value_AirPressure_edited="760",value_AirPressure,value_Humidity_edited="60",value_Humidity,value_Altitude_edited="200",value_Altitude,value_HeadWindSpeed_edited="10",value_HeadWindSpeed,value_CrossWindSpeed_edited="10",value_CrossWindSpeed,value_Range_edited="0",value_Range,value_TargetHeight_edited="0",value_TargetHeight,value_GraphXEnd_edited="3000",value_GraphXEnd,value_Interval_edited="1",value_Interval, value_GridXm_edited="20",value_GridXm,value_YCm_edited="20.0",value_YCm,value_TrajRange_edited="1500.0",value_TrajRange,value_range2_edited="100",value_range2,value_Wall_edited="2000",value_Wall;
    QStringList muzzlevelocity_edited,muzzle_velocity,ballisticcoefficient_edited,ballisticcoefficient,HeightofSight_edited,HeightofSight,GunElevation1_edited,Gun_Elevation1,AirTemperature_edited,AirTemperature,AirPressure_edited,AirPressure,Humidity_edited,Humidityy,Altitude_edited,Altitudee,HeadWindSpeed_edited,HeadWindSpeed,CrossWindSpeed_edited,CrossWindSpeed,Range_edited,Range,TargetHeight_edited,TargetHeight,GraphXEnd_edited,GraphXEnd,Interval_edited,Interval,GridXm_edited,GridXm,YCm_edited,YCm,TrajRange_edited,TrajRange,range2_edited,range2,Wall_edited,Wall;
    double delement_order[2],conv_vall_GunElevation1 = 1.0,conv_vall_GunElevation2;
    int order;
    int current_index = 0,fpr_traj_range=1000,fpr_graphXend=1500,fpr_range2=100,fpr_wall=1000;
    // fpr_muzzle_velocity = 491 * ,
    double fpr_muzzle_velocity=914.0,fpr_balcoefficient=0.338,fpr_heightofsight=0.0,fpr_gunelevation1=0.0,fpr_airtemperature=20,fpr_airpressure=760,fpr_humidity=85,fpr_altitude=0,fpr_headwindspeed=0,fpr_crosswindspeed=0,fpr_step=100.0;


    std::vector<BulletCondition> ResultList;
    int changed = 0;


public slots:

    void makePlot(double delement_order[2]);
    void initTableWidget(double fpr_muzzle_velocity,double fpr_balcoefficient,double fpr_heightofsight,double gunelevation1,double fpr_airtemperature,double fpr_airpressure,double fpr_humidity,double fpr_altitude,double fpr_headwindspeed, double fpr_crosswindspeed,int fpr_graphXend,double fpr_step,int fpr_traj_range,int fpr_range2,int fpr_wall);


//private slots:

    void on_pushButton_Select_clicked();
    //void Mouse_Pressed();
   // void on_LineEdit_Wall_textEdited(const QString &arg1);

    void on_LineEdit_Range2_textEdited(const QString &arg1);

    void on_LineEdit_Range2_returnPressed();

    void on_LineEdit_MuzzleVelocity_textEdited(const QString &arg1);

    void on_LineEdit_MuzzleVelocity_returnPressed();

    void on_LineEdit_BalisticsCoefficient_textEdited(const QString &arg1);

    void on_LineEdit_BalisticsCoefficient_returnPressed();

    void on_LineEdit_HeightofSight_textEdited(const QString &arg1);

    void on_LineEdit_HeightofSight_returnPressed();

    void on_LineEdit_GunElevation1_textEdited(const QString &arg1);

    void on_LineEdit_GunElevation1_returnPressed();

    void on_LineEdit_GunElevation2_textEdited(const QString &arg1);

    void on_LineEdit_GunElevation2_returnPressed();

    void on_Cmbx_mindegmil_currentTextChanged(const QString &arg1);

    void on_LineEdit_AirTemperature_textEdited(const QString &arg1);

    void on_LineEdit_AirTemperature_returnPressed();

    void on_LineEdit_AirPressure_textEdited(const QString &arg1);

    void on_LineEdit_AirPressure_returnPressed();

    void on_LineEdit_Humidity_textEdited(const QString &arg1);

    void on_LineEdit_Humidity_returnPressed();

    void on_LineEdit_Altitude_textEdited(const QString &arg1);

    void on_LineEdit_Altitude_returnPressed();

    void on_LineEdit_HeadWindSpeed_textEdited(const QString &arg1);

    void on_LineEdit_HeadWindSpeed_returnPressed();

    void on_LineEdit_CrossWindSpeed_textEdited(const QString &arg1);

    void on_LineEdit_CrossWindSpeed_returnPressed();

    void on_LineEdit_Range_textEdited(const QString &arg1);

    void on_LineEdit_Range_returnPressed();

    void on_LineEdit_TargetHeight_textEdited(const QString &arg1);

    void on_LineEdit_TargetHeight_returnPressed();

    void on_LineEdit_GraphXEnd_textEdited(const QString &arg1);

    void on_LineEdit_GraphXEnd_returnPressed();

    void on_LineEdit_Interval_textEdited(const QString &arg1);

    void on_LineEdit_Interval_returnPressed();

    void on_LineEdit_GridXm_textEdited(const QString &arg1);

    void on_LineEdit_GridXm_returnPressed();

    void on_LineEdit_YCm_textEdited(const QString &arg1);

    void on_LineEdit_YCm_returnPressed();

    void on_LineEdit_TrajRange_textEdited(const QString &arg1);

    void on_LineEdit_TrajRange_returnPressed();

    void on_LineEdit_Wall_textEdited(const QString &arg1);

    void on_LineEdit_Wall_returnPressed();

    void on_Cmbx_mindegmil_currentIndexChanged(int index);


private:
    Ui::Trajectory_Calculator_BnbcInternational *ui;
    //Select_Bullets *opendialog;
    QCustomPlot *wGraphic;
    QCPCurve *verticalLine;
    QCPItemTracer *tracer;
protected:

    //virtual void mousePressEvent(QMouseEvent *);
    //virtual void focusInEvent(QFocusEvent *e);

    //virtual void mouseDoubleClickEvent(QMouseEvent *);

};
#endif // TRAJECTORY_CALCULATOR_BNBCINTERNATIOui->customPlot
