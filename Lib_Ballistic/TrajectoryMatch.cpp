#include "TrajectoryMatch.h"
#include "Lib_Ballistic_global.h"
///<summary>Trajectory dogrulugunu ve hata payini hesaplayan nesne.</summary>
TrajectoryMatch::~TrajectoryMatch()
{
}
///<summary>2 mermi yolu birimi arasindaki hatayi (sapma) yi hesaplar.</summary>
///<param name="InProjector">BalisticProjector türünde nesne girdisi</param>
///<oaramn name="Range">Uzaklık degeri</param>
double TrajectoryMatch::CalculateIntersectionAngle(BallisticProjector *InProjector, float Range)
{
	Atmosphere *atm = new Atmosphere();
	std::vector<BulletCondition> BulletPathWay = BallisticTrajectory::CalculateBulletPathWay(InProjector,atm, 0, 0, Range, Range + 1);

	double Hata = BulletPathWay.at(1).getHeight(); // HATA santimetre cinsinden.
    //double ÖncekiHata = Hata;
	double CurrentDegree = 0.001;
	double degreeIncrement = 0.001;

	while (!((-0.2 < Hata) && (Hata < 0.2))) {
		BulletPathWay = BallisticTrajectory::CalculateBulletPathWay(InProjector, atm, CurrentDegree, 0, Range, Range + 1);
		Hata = BulletPathWay.at(1).getHeight(); //Hata santimetre cinsinden
		CurrentDegree = CurrentDegree + degreeIncrement;
	}
	return CurrentDegree;
}
