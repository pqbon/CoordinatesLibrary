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
		constexpr T rad_to_mile { static_cast<T>(28.086282722513) };

		template <typename T>
		constexpr T mile_to_rad { static_cast<T>(0.035604569315199) };

		template <typename T>
		constexpr T km_to_m { static_cast<T>(1000) };

		template <typename T>
		constexpr T m_to_km { static_cast<T>(1) / static_cast<T>(1000) };

		template <typename T>
		constexpr T km_to_nm { static_cast<T>(1.852) };

		template <typename T>
		constexpr T nm_to_km { static_cast<T>(0.53995680345572) };

		template <typename T>
		constexpr T m_to_nm { static_cast<T>(1852) };

		template <typename T>
		constexpr T nm_to_m { static_cast<T>(0.00053995680345572) };

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

		template <typename T>
		constexpr T nm_deg { static_cast<T>(60) };

		template <typename T>
		constexpr T nm_to_rad { my_pi<T> / (half_circ_deg<T> * nm_deg<T>)};

		template <typename T>
		constexpr T rad_to_nm { (half_circ_deg<T> * nm_deg<T>) / my_pi<T> };

	}

	//To convert latitude or longitude to radians use
	// Degrees on globe are degress..
	//	1deg = (Pi / 180) radians
	//
	//distance_radians = (pi / (180 * 60)) * distance_nm
	//distance_nm = ((180 * 60) / pi) * distance_radians
	//

	template <typename T>
	T radians2nm(T const rad) {
		T const nm { rad * NavigationConstantsNS::rad_to_nm<T>};

		return nm;
	}

	template <typename T>
	T nm2radians(T const nm) {
		T const rad { nm * NavigationConstantsNS::nm_to_rad<T>};

		return rad;
	}

	template <typename T>
	T radians2miles(T const rad) {
		T const miles { rad * NavigationConstantsNS::rad_to_mile<T>};

		return miles;
	}

	template <typename T>
	T miles2radians(T const miles) {
		T const rad { miles * NavigationConstantsNS::mile_to_rad<T> };

		return rad;
	}

	template <typename T>
	T m2km(T const m) {
		T const km { m * NavigationConstantsNS::m_to_km<T>};

		return km;
	}

	template <typename T>
	T km2m(T const km) {
		T const m { km * NavigationConstantsNS::km_to_m<T>};

		return m;
	}

	template <typename T>
	T km2nm(T const km) {
		T const nm { km * NavigationConstantsNS::km_to_nm<T>};

		return nm;
	}

	template <typename T>
	T nm2km(T const nm) {
		T const km { nm * NavigationConstantsNS::nm_to_km<T>};

		return km;
	}

	template <typename T>
	T m2nm(T const m) {
		T const nm { m * NavigationConstantsNS::m_to_nm<T>};

		return nm;
	}

	template <typename T>
	T nm2m(T const nm) {
		T const m { nm * NavigationConstantsNS::nm_to_m<T> };

		return m;
	}

	template <typename T>
	T degress2radians(T const deg) {
		T const rad { deg * NavigationConstantsNS::to_rads<T> };

		return rad;
	}

	template <typename T>
	T radians2degrees(T const rad) {
		T const deg { rad * NavigationConstantsNS::to_degs<T> };

		return deg;
	}

	template <typename T>
	T mod(T x, T y) {
		//mod(y,x) = y - x*floor(y/x)
		T const ans { y - x * std::floor(y / x) };
		return ans;
	}
}