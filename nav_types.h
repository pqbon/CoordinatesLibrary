#pragma once


#include <cmath>
#include <initializer_list>
#include <iostream>

#include "nav_coordinates.h"
#include "nav_vectors.h"

using namespace std::literals::string_literals;

namespace CoordinatesNS::Float {
	using Degrees [[maybe_unused]] = D_t<float_t>;
	using DegreesMinutes [[maybe_unused]] = DM_t<float_t>;
	using DegreesMinutesSeconds [[maybe_unused]] = DMS_t<float_t>;
	using NavigationVector [[maybe_unused]] = Nav_vec_t<float_t>;
	using CartesianVector [[maybe_unused]] = Cart_vec_t<float_t>;

	using CoordinatesDegrees [[maybe_unused]] = Coordinates<Degrees>;
	using CoordinatesDegreesMinutes [[maybe_unused]] = Coordinates<DegreesMinutes>;
	using CoordinatesDegreesMinutesSeconds [[maybe_unused]] = Coordinates<DegreesMinutesSeconds>;

	Degrees operator""_D(long double degs_);

	Degrees operator""_ND(long double degs_);
	Degrees operator""_SD(long double degs_);
	Degrees operator""_ED(long double degs_);
	Degrees operator""_WD(long double degs_);

	Degrees operator""_D(long double degs_)
	{
		Degrees ret(static_cast<float>(degs_));
		return ret;
	}

	Degrees operator""_ND(long double degs_)
	{
		Degrees ret(static_cast<float>(degs_));
		return ret;
	}

	Degrees operator""_SD(long double degs_)
	{
		Degrees ret(static_cast<float>(-degs_));
		return ret;
	}

	Degrees operator""_ED(long double degs_)
	{
		Degrees ret(static_cast<float>(degs_));
		return ret;
	}

	Degrees operator""_WD(long double degs_)
	{
		Degrees ret(static_cast<float>(-degs_));
		return ret;
	}
}

namespace CoordinatesNS::Double {
	using Degrees [[maybe_unused]] = D_t<double>;
	using DegreesMinutes [[maybe_unused]] = DM_t<double>;
	using DegreesMinutesSeconds [[maybe_unused]] = DMS_t<double>;
	using NavigationVector [[maybe_unused]] = Nav_vec_t<double>;
	using CartesianVector [[maybe_unused]] = Cart_vec_t<double>;

	using CoordinatesDegrees [[maybe_unused]] = Coordinates<Degrees>;
	using CoordinatesDegreesMinutes [[maybe_unused]] = Coordinates<DegreesMinutes>;
	using CoordinatesDegreesMinutesSeconds [[maybe_unused]] = Coordinates<DegreesMinutesSeconds>;

	Degrees operator""_D(long double degs_);

	Degrees operator""_ND(long double degs_);
	Degrees operator""_SD(long double degs_);
	Degrees operator""_ED(long double degs_);
	Degrees operator""_WD(long double degs_);

	Degrees operator""_D(long double degs_)
	{
		Degrees ret(static_cast<double>(degs_));
		return ret;
	}

	Degrees operator""_ND(long double degs_)
	{
		Degrees ret(static_cast<double>(degs_));
		return ret;
	}

	Degrees operator""_SD(long double degs_)
	{
		Degrees ret(static_cast<double>(-degs_));
		return ret;
	}

	Degrees operator""_ED(long double degs_)
	{
		Degrees ret(static_cast<double>(degs_));
		return ret;
	}

	Degrees operator""_WD(long double degs_)
	{
		Degrees ret(static_cast<double>(-degs_));
		return ret;
	}

}