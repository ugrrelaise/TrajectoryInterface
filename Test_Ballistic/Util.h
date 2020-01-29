#ifndef UTIL_H
#define UTIL_H
#include <math.h>

#include "Lib_Ballistic_global.h"


	class Util {
	public:
		~Util();
		Util();
		///<summary>1:100.000 olceginde sayi yuvarlar</summary>
		///<param name="roundValue">Yuvarlama yapiacak sayi</param>
		static double roundD(double roundValue);
	};
#endif