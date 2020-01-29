#include "BallisticTrajectory.h"
#include "FlightSpeed.h"
#include "Lib_Ballistic_global.h"

BallisticTrajectory::~BallisticTrajectory()
{
}
const double BallisticTrajectory::PIR = -0.000208551;
const double BallisticTrajectory::TK1 = -0.000006858;
const double BallisticTrajectory::TK2 = -0.00000000002776;
const double BallisticTrajectory::RH1 = -0.00002926;
const double BallisticTrajectory::RH2 = -0.0000000001;
const double BallisticTrajectory::SpeedOfSoundConstant = 331.3; //Metre bölü saniye cinsinden
const double BallisticTrajectory::Gravity = 32.17405;//Gravity as feets per second
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
std::vector<BulletCondition> BallisticTrajectory::CalculateBulletPathWay(BallisticProjector *Bullet, Atmosphere *Enviroment, double IncVerticalAngle, double IncHorizantalAngle, double Step, double Range)
{
	std::vector<BulletCondition> ResultList;
	
	double FahrenheitTemprature = Conversions::CelsiusToFahrenheit(Enviroment->getAirDensity().getTemperature());

	FlightSpeed FlightSpeed(Bullet->getTheMuzzleVelocity(), IncVerticalAngle, IncHorizantalAngle);
	
	//TheHeight of sight başta 
	double HeightOfSight = -Conversions::CmToFeet(Bullet->ClassGunMCD->getHeightOfSight());

	double InitialVelocityOfBullet = sqrt(pow((FlightSpeed.getXComponent() - Enviroment->getWind().getHeadWindSpeedinfeetpers()), 2) +
		pow((FlightSpeed.getYComponent()), 2) +
		pow((FlightSpeed.getZComponent() - Enviroment->getWind().getCrossWindSpeedinfeetpers()), 2));

	double SightCorelatedTemprature = Conversions::KelvinToFahrenheit(Conversions::FahrenheitToKelvin(FahrenheitTemprature) * exp((TK1 + TK2 * HeightOfSight) * HeightOfSight));

	double TemperatureCorrectedSpeedOfSound = Conversions::MeterPerSecondToFeetPerSecond(SpeedOfSoundConstant + 0.606 * Conversions::FahrenheitToCelsius(SightCorelatedTemprature)); //Metre/second cinsinden hesaplayıp sonra yeniden feet per seconda çevriliyor)

	double MachSpeedOfBullet = InitialVelocityOfBullet / TemperatureCorrectedSpeedOfSound;

	double DragMultiplierFromSpeedOfBullet = DragInterpolation(Bullet->getDragFunction(), MachSpeedOfBullet);

	double DragMultiplierFromAirDensityOverBalisticCoefficient = (PIR * Enviroment->getAirDensity().CalculateAirDensity()) / Bullet->getBallisticCoefficient();

	double TrueDragMultiplier = (DragMultiplierFromSpeedOfBullet * DragMultiplierFromAirDensityOverBalisticCoefficient * InitialVelocityOfBullet
		* exp((RH1 + RH2 * HeightOfSight) * HeightOfSight)) / FlightSpeed.getXComponent();

	// feet cinsinden step ile çarpıldıklarında hız değişimini veren değişkenler
	double XSpeedStepMultiplier = TrueDragMultiplier * (FlightSpeed.getXComponent() - Enviroment->getWind().getHeadWindSpeedinfeetpers());
	double YSpeedStepMultiplier = (TrueDragMultiplier * FlightSpeed.getYComponent()) - (Gravity / FlightSpeed.getXComponent());
	double ZSpeedStepMultiplier = TrueDragMultiplier * (FlightSpeed.getZComponent() - Enviroment->getWind().getCrossWindSpeedinfeetpers());

	double CurrentRange = 0; //Uçuşun başlangıcı Feet cinsinden
	double FeetStep = Conversions::CmToFeet(Step * 100);
	double PreviousXSpeed = FlightSpeed.getXComponent();
	double PreviousYSpeed = FlightSpeed.getYComponent();
	double PreviousZSpeed = FlightSpeed.getZComponent();

	double PreviousXSpeedStepMultiplier = XSpeedStepMultiplier;
	double PreviousYSpeedStepMultiplier = YSpeedStepMultiplier;
	double PreviousZSpeedStepMultiplier = ZSpeedStepMultiplier;

	//İlk elemanın yaratılması
	BulletCondition BulletData (Conversions::FeetToCm(0) * 0.01, Conversions::FeetToCm(HeightOfSight),
	Conversions::FeetToCm(0), Conversions::FeetPerSecondToMeterPerSecond(InitialVelocityOfBullet), 0, Conversions::FeetPerSecondToMeterPerSecond(PreviousXSpeed),
	Conversions::FeetPerSecondToMeterPerSecond(PreviousYSpeed), Conversions::FeetPerSecondToMeterPerSecond(PreviousZSpeed));

	ResultList.push_back(BulletData);

	double EulerXSpeed = 0;
	double EulerYSpeed = 0;
	double EulerZSpeed = 0;

	double EulerVelocityOfBullet = 0;

	double EulerXSpeedStepMultiplier = 0;
	double EulerYSpeedStepMultiplier = 0;
	double EulerZSpeedStepMultiplier = 0;

	double PredictedXSpeed = 0;
	double PredictedYSpeed = 0;
	double PredictedZSpeed = 0;

	double PredictedVelocityOfBullet = 0;

	double HeunSuccees = 0;
	//Feet cinsinden
	double Height = HeightOfSight; //Bu noktadan sonra merminin yüksekliği sadece namlu yüksekliği olarak değil gerçek yüksekliği olarak görülecek
	double Deflection = 0;
	double Time = 0;
	double Velocity = 0;
	int sayfor = 0;
	int saywhile = 0;
	
	for (CurrentRange = 0 + FeetStep; CurrentRange < Conversions::CmToFeet(Range * 100); CurrentRange = CurrentRange + FeetStep)
	{

		sayfor++;
		//Eulerın predictor formülünün uygulanması
		//Bu değişkenler Euler predicted değişkenler
		EulerXSpeed = PreviousXSpeed + (PreviousXSpeedStepMultiplier * FeetStep);
		EulerYSpeed = PreviousYSpeed + (PreviousYSpeedStepMultiplier * FeetStep);
		EulerZSpeed = PreviousZSpeed + (PreviousZSpeedStepMultiplier * FeetStep);

		EulerVelocityOfBullet = sqrt(pow((EulerXSpeed - Enviroment->getWind().getHeadWindSpeedinfeetpers()), 2) +
			pow((EulerYSpeed), 2) +
			pow((EulerZSpeed - Enviroment->getWind().getCrossWindSpeedinfeetpers()), 2));

		//Heun correction uygulanması bunun bir sonraki adımının hesaplanması ve ikisinin ortalamasının doğru olarak kabul edilmesini içeriyor
		HeunSuccees = 1; //İlk girişin sağlanması için
		double PreviousHeunSuccees = 0; //Sonsuz döngüye girmesini engellemesi için

		while (Util::roundD(HeunSuccees) > 0.00001)     // Hata var precision ayarlanmalı. round(HeunSuccess,5) olmalı
		{
			saywhile++;

			SightCorelatedTemprature = Conversions::KelvinToFahrenheit(Conversions::FahrenheitToKelvin(FahrenheitTemprature) * exp((TK1 + TK2 * Height) * Height));

			TemperatureCorrectedSpeedOfSound = Conversions::MeterPerSecondToFeetPerSecond(SpeedOfSoundConstant + 0.606 * Conversions::FahrenheitToCelsius(SightCorelatedTemprature)); //Metre/second cinsinden hesaplayıp sonra yeniden feet per seconda çevriliyor

			MachSpeedOfBullet = EulerVelocityOfBullet / TemperatureCorrectedSpeedOfSound;

			DragMultiplierFromSpeedOfBullet = DragInterpolation(Bullet->getDragFunction(), MachSpeedOfBullet);

			TrueDragMultiplier = (DragMultiplierFromSpeedOfBullet * DragMultiplierFromAirDensityOverBalisticCoefficient * EulerVelocityOfBullet
				* exp((RH1 + RH2 * Height) * Height)) / EulerXSpeed;

			EulerXSpeedStepMultiplier = TrueDragMultiplier * (EulerXSpeed - Enviroment->getWind().getHeadWindSpeedinfeetpers());
			EulerYSpeedStepMultiplier = (TrueDragMultiplier * EulerYSpeed) - (Gravity / EulerXSpeed);
			EulerZSpeedStepMultiplier = TrueDragMultiplier * (EulerZSpeed - Enviroment->getWind().getCrossWindSpeedinfeetpers());

			//Tahmin ile bir önceki hesaplananın ağırlıklı ortalamasının alınması
			PredictedXSpeed = PreviousXSpeed + 0.5 * (EulerXSpeedStepMultiplier + PreviousXSpeedStepMultiplier) * FeetStep;
			PredictedYSpeed = PreviousYSpeed + 0.5 * (EulerYSpeedStepMultiplier + PreviousYSpeedStepMultiplier) * FeetStep;
			PredictedZSpeed = PreviousZSpeed + 0.5 * (EulerZSpeedStepMultiplier + PreviousZSpeedStepMultiplier) * FeetStep;

			PredictedVelocityOfBullet = sqrt(pow((PredictedXSpeed - Enviroment->getWind().getHeadWindSpeed()), 2) +
				pow((PredictedYSpeed), 2) +
				pow((PredictedZSpeed - Enviroment->getWind().getCrossWindSpeed()), 2));
			HeunSuccees = abs((PredictedVelocityOfBullet - EulerVelocityOfBullet) / PredictedVelocityOfBullet);

			if (PreviousHeunSuccees == HeunSuccees)
			{
				HeunSuccees = 0;
			}
			else
			{
				PreviousHeunSuccees = HeunSuccees;
			}
		}

		Height = Height + ((PredictedYSpeed + PreviousYSpeed) / (PredictedXSpeed + PreviousXSpeed)) * FeetStep; //Feets Cinsinden
		Deflection = Deflection + ((PredictedZSpeed + PreviousZSpeed) / (PredictedXSpeed + PreviousXSpeed)) * FeetStep; //Feets cinsinden
		Time = Time + (2 * FeetStep) / (PredictedXSpeed + PreviousXSpeed);
		Velocity = sqrt(pow(PredictedXSpeed, 2) + pow(PredictedYSpeed, 2) + pow(PredictedZSpeed, 2));

		BulletCondition BulletData (Conversions::FeetToCm(CurrentRange) * 0.01, Conversions::FeetToCm(Height),
			Conversions::FeetToCm(Deflection), Conversions::FeetPerSecondToMeterPerSecond(Velocity), Time, Conversions::FeetPerSecondToMeterPerSecond(PredictedXSpeed),
			Conversions::FeetPerSecondToMeterPerSecond(PredictedYSpeed), Conversions::FeetPerSecondToMeterPerSecond(PredictedZSpeed));

		ResultList.push_back(BulletData);
		PreviousXSpeed = PredictedXSpeed;
		PreviousYSpeed = PredictedYSpeed;
		PreviousZSpeed = PredictedZSpeed;
		PreviousXSpeedStepMultiplier = EulerXSpeedStepMultiplier;
		PreviousYSpeedStepMultiplier = EulerYSpeedStepMultiplier;
		PreviousZSpeedStepMultiplier = EulerZSpeedStepMultiplier;

	}
	
	return ResultList;
}

double BallisticTrajectory::DragInterpolation(DragFunction DragFunction, double MachSpeed)
{
	int x = 0;
	
	while ((MachSpeed > DragFunction.getTheMachSpeedArray().at(x)) && (x < DragFunction.getTheMachSpeedArray().size())) {
		x = x + 1;
	}
	double CorrectionMultiplier = (DragFunction.getTheDragArray().at(x+1) - DragFunction.getTheDragArray().at(x)) / (DragFunction.getTheMachSpeedArray().at(x+1) - DragFunction.getTheMachSpeedArray().at(x));
	double CorrectedMachSpeed = DragFunction.getTheDragArray().at(x) + CorrectionMultiplier * (MachSpeed - DragFunction.getTheMachSpeedArray().at(x));
	return CorrectedMachSpeed;
}
