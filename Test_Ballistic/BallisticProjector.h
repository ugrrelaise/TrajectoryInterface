#ifndef BALLISTICPROJECTOR_H
#define BALLISTICPROJECTOR_H
#include <string>
#include "DragFunction.h"
#include "Gun.h"
#include "Util.h"

#include "Lib_Ballistic_global.h"


class BallisticProjector
	{
	public:
		///<summary>Balistik ozellikleri tanımlayan ve degerlerini saklayan nesne.</summary>
		///<param name = "IncProjectorCategoryID">Projektör kategori id degeri</param>
		///<param name = "IncProjectorCategoryName">Projektör kategori isimi</param>
		///<param name = "IncProjectileCalibre">Mermi kalibre degeri</param>
		///<param name = "IncIsZeroing">Sıfırlanma durumu</param>
		///<param name = "IncRange">Mesafe degeri</param>
		///<param name = "IncHeightOfSight">Gorus uzaklik degeri</param>
		///<param name = "IncMuzzleVelocity">Namludan cikis hiz degeri</param>
		///<param name = "IncBallisticCoefficient">Balistik katsayi degeri</param>
		///<param name = "incDragFunction">Suruklenme fonskiyonu nesnesi</param>
		BallisticProjector(int IncProjectorCategoryID, std::string IncProjectorCategoryName, double IncProjectileCalibre, bool IncIsZeroing, double IncRange, double IncHeightOfSight, double IncMuzzleVelocity, double IncBallisticCoefficient, DragFunction incDragFunction);
		~BallisticProjector();
		Gun *ClassGunMCD;
		/// <summary>
		/// Get or Set the speed of bullet in feets per second cinsinden when it leaves the muzzle
		/// </summary>
		double getTheMuzzleVelocity();
		double getBallisticCoefficient();
		DragFunction getDragFunction();
		void setTheMuzzleVelocity(double theMuzzleVelocity);
		void setBallisticCoefficient(double theBallisticCoefficient);
		void setDragFunction(DragFunction incDragFunction);
	private:

		double MuzzleVelocity;
	    double BallisticCoefficient;
	    int ProjectorCategoryID;
	    std::string ProjectorCategoryName;
	    double ProjectileCalibre;
	    DragFunction dragFunction;
	    bool IsZeroing;
	    double Range;
		//Bitmap  ProjectorTargetImage;   Bitmap kütüphanesi eksik
	};

#endif
