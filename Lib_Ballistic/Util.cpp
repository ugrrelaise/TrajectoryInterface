#include "Util.h"

#include "Lib_Ballistic_global.h"

Util::~Util()
{
}

Util::Util()
{
}
///<summary>1:100.000 ölceginde sayi yuvarlar</summary>
///<param name="roundValue">Yuvarlama yapiacak sayi</param>
double Util::roundD(double roundValue)
{
	return (double)roundValue >= 0.0000f ? floorf(roundValue + 0.00005f) : ceilf(roundValue - 0.00005f);
}
