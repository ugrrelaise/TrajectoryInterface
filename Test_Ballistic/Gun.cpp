#include "Gun.h"
///<summary>Silah gorus yuksekligini kaydeden nesne.<summary>
///<param name="incHeightOfSight">Gorus yukseklıgi degeri.</param>
Gun::Gun(double incHeightOfSight)
{
	HeightOfSight = incHeightOfSight;
}

Gun::~Gun()
{
}

double Gun::getHeightOfSight()
{
	return HeightOfSight;
}

void Gun::setHeightOfSight(double incHeightOfSight)
{
	HeightOfSight = incHeightOfSight;
}
