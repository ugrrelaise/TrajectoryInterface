#ifndef GUN_H
#define GUN_H

#include <string>
#include "Lib_Ballistic_global.h"

using namespace std;
class LIB_BALLISTIC_EXPORT Gun
    {
    public:
        ///<summary>Silah gorus yuksekligini kaydeden nesne.<summary>
        ///<param name="incHeightOfSight">Gorus yukseklıgi degeri.</param>
        Gun(double incHeightOfSight);
        ~Gun();
        double getHeightOfSight();
        void setHeightOfSight(double incHeightOfSight);

    string gun_dragfunction;
    double gun_muzzle_velocity,gun_balcoefficient,gun_heightofsight,gun_gunelevation1,gun_airtemperature,gun_airpressure,gun_humidity,gun_altitude,gun_headwindspeed,gun_crosswindspeed,gun_grapXend,gun_step,gun_gridxm,gun_traj_range,gun_range2,gun_wall,gun_scalingat45deg;
    Gun();
    private:
        double HeightOfSight;
        double mass;
    };

//Gun sınıfından kalıtım aldır ve parametreler otomatik bu silahlardan alınsın hesaplama yapılırken.

// 1------------------- class Kılınc2000
/*
class Glock {};		//Glock-19 Tabanca,

class P229{};		//9 mm Sig Sauer P229 Tabanca

class MP_5{};		//9 mm MP - 5 Makineli Tabanca

class FN {};	   //62 mm FN Minimi Makineli Tüfek

class Browning {};	//7 mm M2 Browning Makineli Tüfek

class Bora {};		//Bora - 12 7, 62 mm Keskin Nişancı Tüfeği

class Barrett {};	// Barrett M82 - A1 12, 7 mm Keskin Nişancı Tüfeği

class MK19 {};		// MK19 40 mm Otomatik Bombaatar

class Impala {};	 //Impala Plus 12 Gauge Av Tüfeği

class UT-1Havan{};

class MPT55{};

class SAR109T{};

class KNT76{};

class RPG-7{};

class LAW{};

*/

#endif

/*
//TEST Amaçlıdır.
    //Drag function
    DragFunction dragFunc = DragFunction::CreateDragFunction("G1");
    DragFunction drag2 = DragFunction::CreateDragFunction("G2");
    //BallisticProjector

    //BallisticProjector* bullet = new BallisticProjector(1, "Test", 2.00, false, 100.00, 10.00, 2800.0, 0.105, dragFunc);
    BallisticProjector* bullet = new BallisticProjector(1, "Test", 5.56, false, 100.00, fpr_heightofsight, (fpr_muzzle_velocity*3.28084), fpr_balcoefficient, dragFunc);
    //cout << bullet->getBallisticCoefficient() << endl;
    //cout << bullet->getDragFunction().getDragFunction() << endl;

    for each (double number in bullet->getDragFunction().getTheMachSpeedArray())
    {
        cout << number << endl;
    }

    bullet->setDragFunction(drag2);
    cout << "-------" << endl;

    for each (double number in bullet->getDragFunction().getTheMachSpeedArray()) {
        cout << number << endl;
    }

    //AirDensity ---double AirDensity::CalculateAirDensity(double H, double T, double A, double P)

    AirDensity airDensity(fpr_humidity, fpr_airtemperature, fpr_altitude, fpr_airpressure);
    Wind wind(fpr_crosswindspeed,fpr_headwindspeed);


    airDensity.CalculateAirDensity();
    wind.CalculateCrossWind(wind.getSpeed(), wind.getAngle());
    wind.CalculateHeadWind(wind.getSpeed(), wind.getAngle());

    Atmosphere* atm = new Atmosphere(airDensity, wind);

    QDebug << atm->getAirDensity().getAltitude() << endl;
    QDebug << atm->getAirDensity().getPressure() << endl;
    QDebug << atm->getAirDensity().getHumidity() << endl;
    QDebug << atm->getWind().getAngle() << endl;*/
    //BallisticTrajectory

    //Dikey pozitif sapma açısı.
    //double incVerticalAngle = fpr_gunelevation1;
    //saat yönünde yatay sapma açısı
    //double incHorizontalAngle = 0.00;
    //Kaç metrede bir nokta yaratılsın

    //*********************************************************************double step = 5.00;
    //Interval_edited = value_Interval_edited.split(" ");
    //Hangi uzaklığa kadar balistik hesabı yapılsın


    //	BallisticTrajectory::CalculateBulletPathWay(bullet, atm, incVerticalAngle, incHorizontalAngle, step, range);

/*
    int size = BallisticTrajectory::CalculateBulletPathWay(bullet, atm, incVerticalAngle, incHorizontalAngle, fpr_step, fpr_traj_range).size();


    for (int i = 0; i < size; i++) {
      try {

            ResultList.push_back(BallisticTrajectory::CalculateBulletPathWay(bullet, atm, fpr_gunelevation1, incHorizontalAngle, fpr_step, fpr_traj_range).at(i));
        }
        catch (exception ex) {
            ex.what();
        }
    }
*/
