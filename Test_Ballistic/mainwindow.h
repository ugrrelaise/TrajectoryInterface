#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMouseEvent>
#include <QVector>
#include <BulletCondition.h>
#include "select_bullets.h"
#include <qcustomplot.h>
#include "lib_ballistic.h"
#include "Lib_Ballistic_global.h"
#include "Gun.h"
#include "Kilinc2000.h"
#include "Glock19.h"
#include "SigSauer.h"
#include "MP5.h"
#include "MPT76.h"
#include "FN_Minimi.h"
#include "M2Browning.h"
#include "Bora12.h"
#include "BarrettM82A1.h"
#include "MK19Bomb.h"
#include "ImpalaPlus12.h"
#include "UT1Havan.h"
#include "MPT55.h"
#include "Sar109T.h"
#include "KNT76.h"
#include "RPG7.h"
#include "Law.h"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;
               class Select_Bullets;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //void mousePressEvent(QMouseEvent *ev);

    QString value_muzzlevelocity_edited="914.0",value_muzzlevelocity,value_BalisticsCoefficient_edited="0.338",value_BalisticsCoefficient,value_HeightofSight_edited="10.00",value_HeightofSight,value_GunElevation1_edited="1.00",value_GunElevation1="0.0",value_GunElevation2="45.00",value_AirTemperature_edited="15",value_AirTemperature,value_AirPressure_edited="760",value_AirPressure,value_Humidity_edited="60",value_Humidity,value_Altitude_edited="200",value_Altitude,value_HeadWindSpeed_edited="10",value_HeadWindSpeed,value_CrossWindSpeed_edited="10",value_CrossWindSpeed,value_Range_edited="0",value_Range,value_TargetHeight_edited="0",value_TargetHeight,value_GraphXEnd_edited="3000",value_GraphXEnd,value_Interval_edited="1",value_Interval, value_GridXm_edited="20",value_GridXm,value_YCm_edited="20.0",value_YCm,value_TrajRange_edited="1500.0",value_TrajRange,value_range2_edited="100",value_range2,value_Wall_edited="2000",value_Wall;
    QStringList muzzlevelocity_edited,muzzle_velocity,ballisticcoefficient_edited,ballisticcoefficient,HeightofSight_edited,HeightofSight,GunElevation1_edited,Gun_Elevation1,AirTemperature_edited,AirTemperature,AirPressure_edited,AirPressure,Humidity_edited,Humidityy,Altitude_edited,Altitudee,HeadWindSpeed_edited,HeadWindSpeed,CrossWindSpeed_edited,CrossWindSpeed,Range_edited,Range,TargetHeight_edited,TargetHeight,GraphXEnd_edited,GraphXEnd,Interval_edited,Interval,GridXm_edited,GridXm,YCm_edited,YCm,TrajRange_edited,TrajRange,range2_edited,range2,Wall_edited,Wall;
    double delement_order[2],conv_vall_GunElevation1 = 1.0,conv_vall_GunElevation2;
    int order;

    // fpr_muzzle_velocity = 491 * ,
    Kilinc2000 kilinc2000;Glock19 glock19;SigSauer sigsauer;MP5 mp5;MPT76 mpt76;FN_Minimi fn_minimi;M2Browning m2browning;Bora12 bora12;BarretM82A1 barretm82a1;MK19Bomb mk19bomb;ImpalaPlus12 impalaplus12;UT1Havan ut1havan;MPT55 mpt55;Sar109T sar109t;KNT76 knt76;RPG7 rpg7;Law law;

    string fpr_dragfunction=kilinc2000.gun_dragfunction;
    double fpr_muzzle_velocity=kilinc2000.gun_muzzle_velocity,fpr_balcoefficient=kilinc2000.gun_balcoefficient,fpr_heightofsight=kilinc2000.gun_heightofsight,fpr_gunelevation1=kilinc2000.gun_gunelevation1,fpr_airtemperature=kilinc2000.gun_airtemperature,fpr_airpressure=kilinc2000.gun_airpressure,fpr_humidity=kilinc2000.gun_humidity,fpr_altitude=kilinc2000.gun_altitude,fpr_headwindspeed=kilinc2000.gun_headwindspeed,fpr_crosswindspeed=kilinc2000.gun_crosswindspeed,fpr_step=kilinc2000.gun_step,fpr_gridxm = kilinc2000.gun_gridxm,fpr_scalingat45deg = kilinc2000.gun_scalingat45deg/220;
    int current_index = 1,current_index_for_gun = 0,fpr_traj_range=kilinc2000.gun_traj_range,fpr_graphXend=kilinc2000.gun_grapXend,fpr_range2=kilinc2000.gun_range2,fpr_wall=kilinc2000.gun_wall;

    QString target_number;
    double tar_number,scaled_val;
    std::vector<BulletCondition> ResultList;
    int changed = 0,dragfunc_cmbx_index;

    Lib_Ballistic libbb;

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsLineItem *myline;
    QGraphicsTextItem *text;

public slots:

    void makePlot(double delement_order[2]);
    void initTableWidget(string fpr_dragfunction,double fpr_muzzle_velocity,double fpr_balcoefficient,double fpr_heightofsight,double gunelevation1,double fpr_airtemperature,double fpr_airpressure,double fpr_humidity,double fpr_altitude,double fpr_headwindspeed, double fpr_crosswindspeed,int fpr_graphXend,double fpr_step,double fpr_gridxm,int fpr_traj_range,int fpr_range2,int fpr_wall);


//private slots:

    //void on_pushButton_Select_2_clicked();
    //void Mouse_Pressed();
   // void on_LineEdit_Wall_textEdited(const QString &arg1);

    void on_LineEdit_Range2_2_textEdited(const QString &arg1);

    void on_LineEdit_Range2_2_returnPressed();

    void on_LineEdit_MuzzleVelocity_2_textEdited(const QString &arg1);

    void on_LineEdit_MuzzleVelocity_2_returnPressed();

    void on_LineEdit_BalisticsCoefficient_2_textEdited(const QString &arg1);

    void on_LineEdit_BalisticsCoefficient_2_returnPressed();

    void on_LineEdit_HeightofSight_2_textEdited(const QString &arg1);

    void on_LineEdit_HeightofSight_2_returnPressed();

    void on_LineEdit_GunElevation1_2_textEdited(const QString &arg1);

    void on_LineEdit_GunElevation1_2_returnPressed();

    void on_LineEdit_GunElevation2_2_textEdited(const QString &arg1);

    void on_LineEdit_GunElevation2_2_returnPressed();

    void on_Cmbx_mindegmil_2_currentTextChanged(const QString &arg1);

    void on_LineEdit_AirTemperature_2_textEdited(const QString &arg1);

    void on_LineEdit_AirTemperature_2_returnPressed();

    void on_LineEdit_AirPressure_2_textEdited(const QString &arg1);

    void on_LineEdit_AirPressure_2_returnPressed();

    void on_LineEdit_Humidity_2_textEdited(const QString &arg1);

    void on_LineEdit_Humidity_2_returnPressed();

    void on_LineEdit_Altitude_2_textEdited(const QString &arg1);

    void on_LineEdit_Altitude_2_returnPressed();

    void on_LineEdit_HeadWindSpeed_2_textEdited(const QString &arg1);

    void on_LineEdit_HeadWindSpeed_2_returnPressed();

    void on_LineEdit_CrossWindSpeed_2_textEdited(const QString &arg1);

    void on_LineEdit_CrossWindSpeed_2_returnPressed();

    void on_LineEdit_Range_2_textEdited(const QString &arg1);

    void on_LineEdit_Range_2_returnPressed();

    void on_LineEdit_TargetHeight_2_textEdited(const QString &arg1);

    void on_LineEdit_TargetHeight_2_returnPressed();

    void on_LineEdit_GraphXEnd_2_textEdited(const QString &arg1);

    void on_LineEdit_GraphXEnd_2_returnPressed();

    void on_LineEdit_Interval_2_textEdited(const QString &arg1);

    void on_LineEdit_Interval_2_returnPressed();

    void on_LineEdit_GridXm_2_textEdited(const QString &arg1);

    void on_LineEdit_GridXm_2_returnPressed();

    void on_LineEdit_YCm_2_textEdited(const QString &arg1);

    void on_LineEdit_YCm_2_returnPressed();

    void on_LineEdit_TrajRange_2_textEdited(const QString &arg1);

    void on_LineEdit_TrajRange_2_returnPressed();

    void on_LineEdit_Wall_2_textEdited(const QString &arg1);

    void on_LineEdit_Wall_2_returnPressed();

    void on_LineEdit_AirTemperature_3_textEdited(const QString &arg1);

    void on_LineEdit_AirTemperature_3_returnPressed();

    void on_LineEdit_AirPressure_3_textEdited(const QString &arg1);

    void on_LineEdit_AirPressure_3_returnPressed();

    void on_LineEdit_Humidity_3_textEdited(const QString &arg1);

    void on_LineEdit_Humidity_3_returnPressed();

    void on_LineEdit_Altitude_3_textEdited(const QString &arg1);

    void on_LineEdit_Altitude_3_returnPressed();

    void on_LineEdit_HeadWindSpeed_3_textEdited(const QString &arg1);

    void on_LineEdit_HeadWindSpeed_3_returnPressed();

    void on_LineEdit_CrossWindSpeed_3_textEdited(const QString &arg1);

    void on_LineEdit_CrossWindSpeed_3_returnPressed();


    void on_Cmbx_mindegmil_2_currentIndexChanged(int index);

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_returnPressed();

    void on_pushButton_Select_2_clicked();

    void on_comboBox_SelectGun_currentIndexChanged(int index);

    void on_Cmbx_DragFunction_2_currentTextChanged(const QString &arg1);


private:
    Ui::MainWindow *ui;
    //Select_Bullets *opendialog;
    QCustomPlot *wGraphic;
    QCPCurve *verticalLine;
    QCPItemTracer *tracer;
protected:

    //virtual void mousePressEvent(QMouseEvent *);
    //virtual void focusInEvent(QFocusEvent *e);

    //virtual void mouseDoubleClickEvent(QMouseEvent *);


};
#endif // MAINWINDOW_H
