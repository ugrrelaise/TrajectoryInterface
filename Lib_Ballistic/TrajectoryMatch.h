#ifndef TRAJECTORYMATCH_H
#define TRAJECTORYMATCH_H
#include "BallisticProjector.h"
#include "BulletCondition.h"
#include "BallisticTrajectory.h"
#include "Atmosphere.h"
#include <vector>

#include "Lib_Ballistic_global.h"


	///<summary>Trajectory dogrulugunu ve hata payini hesaplayan nesne.</summary>
    class LIB_BALLISTIC_EXPORT TrajectoryMatch
	{
	public:
		~TrajectoryMatch();
		///<summary>2 mermi yolu birimi arasindaki hatayi (sapma) yi hesaplar.</summary>
		///<param name="InProjector">BalisticProjector türünde nesne girdisi</param>
		///<oaramn name="Range">Uzaklık degeri</param>
		static double CalculateIntersectionAngle(BallisticProjector *InProjector, float Range);
	};

#endif
