#include "BallisticProjector.h"

#include "Lib_Ballistic_global.h"
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
BallisticProjector::BallisticProjector(int IncProjectorCategoryID, std::string IncProjectorCategoryName, double IncProjectileCalibre, bool IncIsZeroing, double IncRange, double IncHeightOfSight, double IncMuzzleVelocity, double IncBallisticCoefficient, DragFunction incDragFunction)
{
	
	ClassGunMCD = new Gun(IncHeightOfSight);
	Range = IncRange;
	ProjectorCategoryName = IncProjectorCategoryName;
	ProjectorCategoryID = IncProjectorCategoryID;
	ProjectileCalibre = IncProjectileCalibre;
	IsZeroing = IncIsZeroing;
	MuzzleVelocity = IncMuzzleVelocity;
	BallisticCoefficient = IncBallisticCoefficient;
	dragFunction = incDragFunction;
}

BallisticProjector::~BallisticProjector()
{
}

double BallisticProjector::getTheMuzzleVelocity()
{
	return MuzzleVelocity;
}

double BallisticProjector::getBallisticCoefficient()
{
	return BallisticCoefficient;
}

DragFunction BallisticProjector::getDragFunction()
{
	return dragFunction;
}

void BallisticProjector::setTheMuzzleVelocity(double incMuzzleVelocity)
{
	MuzzleVelocity = incMuzzleVelocity;
}

void BallisticProjector::setBallisticCoefficient(double incBallisticCoefficient)
{
	BallisticCoefficient = incBallisticCoefficient;
}

void BallisticProjector::setDragFunction(DragFunction incDragFunction)
{
	dragFunction = incDragFunction;
}

