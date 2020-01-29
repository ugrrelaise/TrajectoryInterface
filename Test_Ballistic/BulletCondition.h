#ifndef BULLETCONDITION_H
#define BULLETCONDITION_H

#include "Lib_Ballistic_global.h"


	class BulletCondition
	{
	public:
		///<summary>Mermi durumunu tanimlayan nesne.</summary>
		///<param name = "incDistance">Uzaklik degeri</param>
		///<param name = "incHeight">Yukseklik degeri</param>
		///<param name = "incDeflection">Sapma degeri</param>
		///<param name = "incTotalVelocity">Toplam surat degeri</param>
		///<param name = "incTime">Sure degeri</param>
		///<param name = "incVelocityX">X yonundeki surat degeri</param>
		///<param name = "incVelocityY">Y younundeki surat degeri</param>
		///<param name = "incVelocityZ">z younundeki surat degeri</param>
		BulletCondition(double incDistance, double incHeight, double incDeflection, double incTotalVelocity, double incTime, double incVelocityX, double incVelocityY, double incVelocityZ);
		~BulletCondition();
		double getDistance();
		double getHeight();
		double getDeflection();
		double getTotalVelocity();
		double getTime();
		double getTheVelocityX();
		double getTheVelocityY();
		double getTheVelocityZ();
	private:
		 double Distance;
		 double Height;
		 double Deflection;
		 double TotalVelocity;
		 double Time;
		 double VelocityX;
		 double VelocityY;
		 double VelocityZ;
	};

#endif
