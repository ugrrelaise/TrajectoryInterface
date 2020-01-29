#ifndef BALLISTICTRAJECTORY_H
#define BALLISTICTRAJECTORY_H

#include "BulletCondition.h"
#include "BallisticProjector.h"
#include "Atmosphere.h"
#include <vector>
#include <math.h>

#include "Lib_Ballistic_global.h"

    class LIB_BALLISTIC_EXPORT BallisticTrajectory
	{
	public:		
		~BallisticTrajectory();
		/// <summary>
		///    Merminin atış süresince alacagı yolu hesaplar.
		/// </summary>
		/// <param name="Bullet">Balistikprojektor nesnesi</param>
		/// <param name="Enviroment">Atmosfer nesnesi</param>
		/// <param name="IncVerticalAngle">Derece cinsinden atışın yerle yaptığı açı</param>
		/// <param name="IncHorizantalAngle">Derece cinsinden silahın yatayla yaptığı açı</param>
		/// <param name="Step">Metre cinsinden sonuç arrayinin kaç metrede bir doldurulucağı</param>
		/// <param name="Range">Metre cinsinden bu arrayın kaç metreye kadar doldurulucağı</param>
		/// <returns>Returns NULL only if there is no dongle present.</returns>
		static std::vector<BulletCondition> CalculateBulletPathWay(BallisticProjector *Bullet,Atmosphere *Enviroment, double IncVerticalAngle, double IncHorizantalAngle, double Step, double Range);
	private:
		static double DragInterpolation(DragFunction DragFunction, double MachSpeed);
		//Bilinmeyen sabitleri
		static const double PIR;
		static const double TK1;
		static const double TK2;
		static const double RH1;
		static const double RH2;
		//const double SpeedOfSoundConstant = 49.0223;
		static const double SpeedOfSoundConstant;
		static const double Gravity;
	};
#endif

