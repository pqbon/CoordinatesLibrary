#pragma once


#include <cmath>
#include <initializer_list>
#include <iostream>

#include "nav_coordinates.h"
#include "nav_vectors.h"

using namespace std::literals::string_literals;

namespace CoordinatesNS::Float {
	using D_tF = D_t<float_t>;
	using DM_tF = DM_t<float_t>;
	using DMS_tF = DMS_t<float_t>;
	using Nav_vec_tF = Nav_vec_t<float_t>;
	using Cart_vec_tF = Cart_vec_t<float_t>;

	using CoordinatesDF = Coordinates<D_tF>;
	using CoordinatesDMF = Coordinates<DM_tF>;
	using CoordinatesDMSF = Coordinates<DMS_tF>;

	D_tF operator""_D(long double degs_);

	D_tF operator""_ND(long double degs_);
	D_tF operator""_SD(long double degs_);
	D_tF operator""_ED(long double degs_);
	D_tF operator""_WD(long double degs_);

	D_tF operator""_D(long double degs_)
	{
		D_tF ret(static_cast<float>(degs_));
		return ret;
	}

	D_tF operator""_ND(long double degs_)
	{
		D_tF ret(static_cast<float>(degs_));
		return ret;
	}

	D_tF operator""_SD(long double degs_)
	{
		D_tF ret(static_cast<float>(-degs_));
		return ret;
	}

	D_tF operator""_ED(long double degs_)
	{
		D_tF ret(static_cast<float>(degs_));
		return ret;
	}

	D_tF operator""_WD(long double degs_)
	{
		D_tF ret(static_cast<float>(-degs_));
		return ret;
	}
}

namespace CoordinatesNS::Double {
	using D_tD = D_t<double>;
	using DM_tD = DM_t<double>;
	using DMS_tD = DMS_t<double>;
	using Nav_vec_tD = Nav_vec_t<double>;
	using Cart_vec_tD = Cart_vec_t<double>;

	using CoordinatesDD = Coordinates<D_tD>;
	using CoordinatesDMD = Coordinates<DM_tD>;
	using CoordinatesDMSD = Coordinates<DMS_tD>;

	D_tD operator""_D(long double degs_);

	D_tD operator""_ND(long double degs_);
	D_tD operator""_SD(long double degs_);
	D_tD operator""_ED(long double degs_);
	D_tD operator""_WD(long double degs_);

	D_tD operator""_D(long double degs_)
	{
		D_tD ret(static_cast<double>(degs_));
		return ret;
	}

	D_tD operator""_ND(long double degs_)
	{
		D_tD ret(static_cast<double>(degs_));
		return ret;
	}

	D_tD operator""_SD(long double degs_)
	{
		D_tD ret(static_cast<double>(-degs_));
		return ret;
	}

	D_tD operator""_ED(long double degs_)
	{
		D_tD ret(static_cast<double>(degs_));
		return ret;
	}

	D_tD operator""_WD(long double degs_)
	{
		D_tD ret(static_cast<double>(-degs_));
		return ret;
	}
}