#pragma once

#include <cmath>
#include <initializer_list>
#include <iostream>

using namespace std::literals::string_literals;

namespace CoordinatesNS {

	namespace NavigationConstantsNS {
		template <typename T>
		constexpr T my_pi { static_cast<T>(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244) };

		template <typename T>
		constexpr T half_circ_deg { static_cast<T>(180) };

		template <typename T>
		constexpr T deg_min { static_cast<T>(60) };

		template <typename T>
		constexpr T min_sec { static_cast<T>(60) };

		template <typename T>
		constexpr T deg_sec { deg_min<T> * min_sec<T> };

		template <typename T>
		constexpr T to_degs { half_circ_deg<T> / my_pi<T> };

		template <typename T>
		constexpr T to_rads { my_pi<T> / half_circ_deg<T> };

	}

	//To convert latitude or longitude to radians use
	// Degrees on globe are degress..
	//	1deg = (Pi / 180) radians
	//

	template <typename T>
	T radians(T deg) {
		T rad { deg * NavigationConstantsNS::to_rads<T> };

		return rad;
	}

	template <typename T>
	T degrees(T rad) {
		T deg { rad * NavigationConstantsNS::to_degs<T> };

		return deg;
	}
}