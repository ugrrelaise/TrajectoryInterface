#ifndef DRAGFUNCTION_H
#define DRAGFUNCTION_H

#include <string>
#include <vector>

#include "Lib_Ballistic_global.h"


	class DragFunction
	{
	public:
		///<summary>Kalibre turlerine gore suruklenme fonksiyonu hesaplayacak olan ust siniftir.</summary>
		///<param name="incDragFunction">Suruklenme fonksiyon tanimlamasi.</param>
		DragFunction(std::string incDragFunction);
		DragFunction();
		~DragFunction();
		std::vector<double> getTheMachSpeedArray();
		std::vector<double> getTheDragArray();
		std::string getDragFunction();
		void setDragFunction(std::string incDragFunction);
		///<summary>Girilen kalibre turune gore uygun nesne dondurecek olan methoddur.</summary>
		///<param name="incDragFunction">Suruklenme fonksiyon tanimlamasi.(bkz:"G1",G2","G5","G6","G7","G8","GI","GL","GS","RA4")</param>
		static DragFunction  CreateDragFunction(std::string incDragFunction);
	protected:
		std::vector<double> MachSpeedArray;
		std::vector<double> DragArray;
	private:
		std::string dragFunction;
		
	};
	///<summary>
	///   SECILI KALIBRE TURLERINE MACH SAYISI VE SURUKLENME SAYILARINI TANIMLARLAR.
	///</summary>
	/// <summary>
	/// A.K.A Ingalls, is by far the most popular drag function
	/// </summary>
	class G1 : public DragFunction
	{
	public:
		G1(std::string IncDragFunc);	
	};
	/// <summary>
	/// Aberdeen J projectile
	/// </summary>
	class G2 : public DragFunction
	{
	public:
		G2(std::string IncDragFunc);
	};
	/// <summary>
	/// short 7.5 degree boat-tail, 6.19 calibers long tangent ogive bullets drag function
	/// </summary>
	class G5 : public DragFunction
	{
	public:
		G5(std::string IncDragFunc);
	};
	/// <summary>
	/// Flatbase, 6 calibers long secant ogive bullets drag function
	/// </summary>
	class G6 : public DragFunction
	{
	public:
		G6(std::string IncDragFunc);
	};
	/// <summary>
	/// long 7.5 degree boat-tail, 10 calibers tangent ogive, preferred by some manufacturers for very-low-drag bullets
	/// </summary>
	class G7 : public DragFunction
	{
	public:
		G7(std::string IncDragFunc);
	};
	/// <summary>
	/// Flatbase, 10 calibers long secant ogive
	/// </summary>
	class G8 : public DragFunction
	{
	public:
		G8(std::string IncDragFunc);
	};
	/// <summary>
	/// Converted from the original Ingalls tables
	/// </summary>
	class GI : public DragFunction
	{
	public:
		GI(std::string IncDragFunc);
	};
	/// <summary>
	/// Blunt lead nose bullets drag function
	/// </summary>
	class GL : public DragFunction
	{
	public:
		GL(std::string IncDragFunc);
	};
	/// <summary>
	/// For round ball - Based on measured 9/16" spherical projectiles
	/// </summary>
	class GS : public DragFunction
	{
	public:
		GS(std::string IncDragFunc);
	};
	/// <summary>
	/// For 22" Long Rifle, identical to G1 below 1400 fps
	/// </summary>
	class RA4 : public DragFunction
	{
	public:
		RA4(std::string IncDragFunc);
	};

#endif
