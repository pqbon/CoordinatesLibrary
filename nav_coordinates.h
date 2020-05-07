#pragma once

#include <cmath>
#include <initializer_list>
#include <iostream>

#include "nav_constants.h"

using namespace std::literals::string_literals;

namespace CoordinatesNS {

	template <typename T>
	class Coordinates;
	template <typename T>
	struct D_t;
	template <typename T>
	struct DM_t;
	template <typename T>
	struct DMS_t;

	template <class T>
	class Coordinates
	{
	// Private must be first to make phi and lambda work...
	private:
		T latM {};

		T lonM {};

	public:
		Coordinates<T>(T lat_, T lon_) : latM { lat_ }, lonM { lon_ } {}
		Coordinates<T>() = default;
		~Coordinates<T>() = default;
		Coordinates<T>(Coordinates<T>&) = default;
		Coordinates<T>(Coordinates<T>&&) = default;
		Coordinates<T>& operator=(Coordinates<T>&) = default;
		Coordinates<T>& operator=(Coordinates<T>&&) = default;

		template <typename TT>
		Coordinates<T>& operator=(Coordinates<TT>& rhs)
		{
			latM = rhs.latM;
			lonM = rhs.lonM;
		}

		T lat() const { return latM; }
		void lat(const T lat_) { latM = lat_; }

		T lon() const { return lonM; }
		void lon(const T lon_) { lonM = lon_; }

		decltype(latM.deg) phi() const {
			D_t<decltype(latM.deg)> dlatM {};
			dlatM = latM;
			return dlatM.deg; 
		}

		decltype(lonM.deg) lambda() const {
			D_t<decltype(lonM.deg)> dlonM {};
			dlonM = lonM;
			return dlonM.deg; 
		}

		template <typename T0, typename T1>
		friend void convert(T0 &t0, const T1 &t1);

		template <typename TN>
		friend std::ostream& operator<<(std::ostream& out, const Coordinates<TN>& coord);
	};

	//// D = D + M/60 + S/3600
	////
	//// D = trunc (Ds)
	//// M = trunc (abs(Ds - D) * 60)
	//// S = 36500 * abs(Ds - D) - 60 x M
    ////
	//// D = trunc (Ds)
	//// M = abs(Ds - D) * 60
	////


	template <typename T>
	struct D_t {
		T deg {};

		D_t<T>() = default;
		D_t<T>(T deg_) : deg { deg_ }
		{
		}

		~D_t<T>() = default;
		D_t<T>(const D_t<T>&) = default;
		D_t<T>(D_t<T>&&) = default;
		D_t<T>& operator=(const D_t<T>&) = default;
		D_t<T>& operator=(D_t<T>&&) = default;

		template <typename TN>
		friend D_t<TN> operator+ (D_t<TN> lhs, const D_t<TN>& rhs);
		template <typename TN>
		friend std::ostream& operator<<(std::ostream& out, const D_t<TN>& coord);

		D_t<T>& operator=(const DM_t<T>& rhs);
		D_t<T>& operator=(const DMS_t<T> & rhs);
	};

	template <typename T>
	struct DM_t {
		T deg {};
		T min {};

		DM_t<T>() = default;
		DM_t<T>(T deg_, T min_) : deg {deg_}, min{min_}
		{
		}

		~DM_t<T>() = default;
		DM_t<T>(const DM_t<T>&) = default;
		DM_t<T>(DM_t<T>&&) = default;
		DM_t<T>& operator=(const DM_t<T>&) = default;
		DM_t<T>& operator=(DM_t<T>&&) = default;

		template <typename TN>
		friend DM_t<TN> operator+ (DM_t<TN> lhs, const DM_t<TN>& rhs);
		template <typename TN>
		friend std::ostream& operator<<(std::ostream& out, const DM_t<TN>& coord);

		DM_t<T>& operator=(const D_t<T>&rhs);
		DM_t<T>& operator=(const DMS_t<T>&rhs);
	};

	template <typename T>
	struct DMS_t {
		T deg {};
		T min {};
		T sec {};

		DMS_t<T>() = default;
		DMS_t<T>(T deg_, T min_, T sec_) : deg { deg_ }, min { min_ }, sec { sec_ }
		{
		}

		~DMS_t<T>() = default;
		DMS_t<T>(const DMS_t<T>&) = default;
		DMS_t<T>(DMS_t<T>&&) = default;
		DMS_t<T>& operator=(const DMS_t<T>&) = default;
		DMS_t<T>& operator=(DMS_t<T>&&) = default;

		template <typename TN>
		friend DMS_t<TN> operator+ (DMS_t<TN> lhs, const DMS_t<TN>& rhs);
		template <typename TN>
		friend std::ostream& operator<<(std::ostream& out, const DMS_t<TN>& coord);

		DMS_t<T>& operator=(const D_t<T>& rhs);
		DMS_t<T>& operator=(const DM_t<T>& rhs);
	};

	template <typename T>
	D_t<T> operator+(D_t<T> lhs, const D_t<T>& rhs)
	{
		lhs.deg += rhs.deg;

		return lhs;
	}

	template <typename T>
	D_t<T>& D_t<T>::operator=(const DM_t<T>& rhs)
	{
		this->deg = rhs.deg + (rhs.min / NavigationConstantsNS::deg_min<T>);

		return *this;
	}

	template <typename T>
	D_t<T>& D_t<T>::operator=(const DMS_t<T>& rhs)
	{
		this->deg = rhs.deg + (rhs.min / NavigationConstantsNS::deg_min<T>) + (rhs.sec / NavigationConstantsNS::deg_sec<T>);

		return *this;
	}

	template <typename T>
	DM_t<T> operator+(DM_t<T> lhs, const DM_t<T>& rhs) {
		D_t<T> const lhsD { lhs };
		D_t<T> const rhsD { rhs };

		D_t<T> tmpD { lhsD + rhsD };

		lhs = tmpD;

		return lhs;
	}

	template <typename T>
	DM_t<T>& DM_t<T>::operator=(const D_t<T>& rhs)
	{
		this->deg = std::floor(rhs.deg) ;
		this->min = std::abs(rhs.deg - this->deg) * NavigationConstantsNS::deg_min<T>;

		return *this;
	}

	template <typename T>
	DM_t<T>& DM_t<T>::operator=(const DMS_t<T>& rhs)
	{
		this->deg = rhs.deg;
		this->min = rhs.min + (rhs.sec / NavigationConstantsNS::min_sec<T>);

		return *this;
	}

	template <typename T>
	DMS_t<T> operator+(DMS_t<T> lhs, const DMS_t<T>& rhs) {
		D_t<T> const lhsD { lhs };
		D_t<T> const rhsD { rhs };

		D_t<T> const tmpD { lhsD + rhsD };
		lhs = tmpD;

		return lhs;
	}

	template <typename T>
	DMS_t<T>& DMS_t<T>::operator=(const D_t<T>& rhs)
	{
		this->deg = std::floor(rhs.deg);
		T const min { std::abs(rhs.deg - this->deg) * NavigationConstantsNS::deg_min<T> };
		this->min = std::floor(min);
		this->sec = ((min - std::floor(min)) * NavigationConstantsNS::min_sec<T>);

		return *this;
	}

	template <typename T>
	DMS_t<T>& DMS_t<T>::operator=(const DM_t<T>& rhs)
	{
		this->deg = rhs.deg;
		T const min { rhs.min };
		this->min = std::floor(rhs.min);
		this->sec = ((min - rhs.min) * NavigationConstantsNS::min_sec<T>);

		return *this;
	}

	template <typename T0, typename T1>
	void convert(T0 &t0, const T1 &t1)
	{
		t0.lonM = t1.lonM;
		t0.latM = t1.latM;
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const Coordinates<TN> &coord) {
		static const std::string north_desg { "N"s };
		static const std::string south_desg { "S"s };
		static const std::string east_desg { "E"s };
		static const std::string west_desg { "W"s };

		bool const north { !std::signbit(coord.latM.deg) };
		bool const east { !std::signbit(coord.lonM.deg) };

		const std::string ns_string { (north) ? north_desg : south_desg };
		const std::string ew_string { (east) ? east_desg : west_desg };

		return out << coord.latM << ns_string  << " "s << coord.lonM << ew_string;
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const D_t<TN>& coord) {
		return out << std::abs(coord.deg);
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const DM_t<TN>& coord) {
		return out << std::abs(coord.deg) << ":"s << coord.min;
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const DMS_t<TN>& coord) {
		return out << std::abs(coord.deg) << ":"s << coord.min << ":"s << coord.sec;
	}
} //CoordinatesNS