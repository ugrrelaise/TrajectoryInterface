#ifndef ENUMDRAGFUNCTION_H
#define ENUMDRAGFUNCTION_H

#include "Lib_Ballistic_global.h"


	enum EnumDragFunction
	{
		/// <summary>
		/// A.K.A Ingalls, is by far the most popular drag function
		/// </summary>
		G1,
		/// <summary>
		/// Aberdeen J projectile
		/// </summary>
		G2,
		/// <summary>
		/// short 7.5 degree boat-tail, 6.19 calibers long tangent ogive bullets drag function
		/// </summary>
		G5,
		/// <summary>
		/// Flatbase, 6 calibers long secant ogive bullets drag function
		/// </summary>
		G6,
		/// <summary>
		/// long 7.5 degree boat-tail, 10 calibers tangent ogive, preferred by some manufacturers for very-low-drag bullets
		/// </summary>
		G7,
		/// <summary>
		/// Flatbase, 10 calibers long secant ogive
		/// </summary>
		G8,
		/// <summary>
		/// Blunt lead nose bullets drag function
		/// </summary>
		GL,
		/// <summary>
		/// Converted from the original Ingalls tables
		/// </summary>
		GI,
		/// <summary>
		/// For round ball - Based on measured 9/16" spherical projectiles
		/// </summary>
		GS,
		/// <summary>
		/// For 22" Long Rifle, identical to G1 below 1400 fps
		/// </summary>
		RA4,

	};

#endif
