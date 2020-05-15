#pragma once

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <cassert>

#include "nav_constants.h"

using namespace std::literals::string_view_literals;

namespace CoordinatesNS {

	template <typename T>
	class Coordinates;
	template <typename T>
	struct D_t;
	template <typename T>
	struct DM_t;
	template <typename T>
	struct DMS_t;

	enum class CoordinatesType {
		NONE, // No rules!
		LATITUDE, // 90 > x > -90
		LONGITUDE, // 180 > x > -180
		GENERAL // 360 > x > -360
	};

	template <class T>
	class Coordinates
	{
	// Private must be first to make phi and lambda work...
	private:
		T latM {};
		T lonM {};

	public:
		Coordinates<T>(T const lat_, T const lon_) : latM { lat_ }, lonM { lon_ } { latM.type = CoordinatesType::LATITUDE; lonM.type = CoordinatesType::LONGITUDE; latM.validate(); lonM.validate(); }
		template <class TT>
		Coordinates<T>(TT const pos) : latM { pos.lat() }, lonM { pos.lon() } { latM.validate(); lonM.validate(); }
		Coordinates<T>() = default;
		~Coordinates<T>() = default;
		Coordinates<T>(Coordinates<T> const &) = default;
		Coordinates<T>(Coordinates<T>&&) = default;
		Coordinates<T>& operator=(Coordinates<T> const &) = default;
		Coordinates<T>& operator=(Coordinates<T>&&) = default;

		template <typename TT>
		Coordinates<T>& operator=(const Coordinates<TT>& rhs)
		{
			lat(rhs.lat());
			lon(rhs.lon());
			lat.validate();
			lon.validate();
		}

		T lat() const { return latM; }
		void lat(const T lat_) { latM = lat_; }

		T lon() const { return lonM; }
		void lon(const T lon_) { lonM = lon_; }

		decltype(latM.deg) phi() const {
			D_t<decltype(latM.deg)> const dlatM { latM };
			return degress2radians(dlatM.deg);
		}

		decltype(lonM.deg) lambda() const {
			D_t<decltype(lonM.deg)> const dlonM { lonM };
			return degress2radians(dlonM.deg); 
		}

		template <typename TT>
		operator Coordinates<TT>() const {
			Coordinates<TT> const ret { lon(), lat() };

			return ret;
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
		CoordinatesType type {CoordinatesType::NONE};

		D_t<T>() = default;
		D_t<T>(T deg_, CoordinatesType type_ = CoordinatesType::NONE) : deg { deg_ }, type { type_}
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

		operator DM_t<T>() const;
		operator DMS_t<T>() const;
		D_t<T>& operator=(const DM_t<T>& rhs);
		D_t<T>& operator=(const DMS_t<T> & rhs);

		void validate() const;
	};

	template <typename T>
	struct DM_t {
		T deg {};
		T min {};
		CoordinatesType type { CoordinatesType::NONE };

		DM_t<T>() = default;
		DM_t<T>(T deg_, T min_, CoordinatesType type_ = CoordinatesType::NONE) : deg {deg_}, min{min_}, type{type_}
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

		operator D_t<T>() const;
		operator DMS_t<T>() const;
		DM_t<T>& operator=(const D_t<T>&rhs);
		DM_t<T>& operator=(const DMS_t<T>&rhs);

		void validate() const;
	};

	template <typename T>
	struct DMS_t {
		T deg {};
		T min {};
		T sec {};
		CoordinatesType type { CoordinatesType::NONE };

		DMS_t<T>() = default;
		DMS_t<T>(T deg_, T min_, T sec_, CoordinatesType type_ = CoordinatesType::NONE) : deg { deg_ }, min { min_ }, sec { sec_ }, type { type_ }
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

		operator D_t<T>() const;
		operator DM_t<T>() const;

		DMS_t<T>& operator=(const D_t<T>& rhs);
		DMS_t<T>& operator=(const DM_t<T>& rhs);

		void validate() const;
	};

	template <typename T>
	D_t<T> operator+(D_t<T> lhs, const D_t<T>& rhs)
	{
		return lhs.deg + rhs.deg;
	}

	template <typename T>
	D_t<T>& D_t<T>::operator=(const DM_t<T>& rhs)
	{
		T const stmp { rhs.deg };
		T const valtmp { std::fabs(rhs.deg) + (rhs.min / NavigationConstantsNS::deg_min<T>) };
		this->deg = std::copysign(valtmp, stmp);

		this->type = rhs.type;
		this->validate();

		return *this;
	}

	template <typename T>
	D_t<T>& D_t<T>::operator=(const DMS_t<T>& rhs)
	{
		T const stmp { rhs.deg };
		T const valtmp { std::fabs(rhs.deg) + (rhs.min / NavigationConstantsNS::deg_min<T>) + (rhs.sec / NavigationConstantsNS::deg_sec<T>) };
		this->deg = std::copysign(valtmp, stmp);

		this->type = rhs.type;
		this->validate();

		return *this;
	}

	template <typename T>
	DM_t<T> operator+(DM_t<T> lhs, const DM_t<T>& rhs) {
		D_t<T> const lhsD { lhs };
		D_t<T> const rhsD { rhs };

		DM_t<T> const tmpD { lhsD + rhsD };

		return tmpD;
	}

	template <typename T>
	DM_t<T>& DM_t<T>::operator=(const D_t<T>& rhs)
	{
		T const stmp { rhs.deg};
		T const tdeg { std::fabs(rhs.deg) };
		this->deg = std::copysign(std::floor(tdeg), stmp);
		this->min = std::fmod(tdeg, static_cast<T>(1)) * NavigationConstantsNS::deg_min<T>;

		this->type = rhs.type;
		this->validate();

		return *this;
	}

	template <typename T>
	DM_t<T>& DM_t<T>::operator=(const DMS_t<T>& rhs)
	{
		this->deg = rhs.deg;
		this->min = rhs.min + (rhs.sec / NavigationConstantsNS::min_sec<T>);

		this->type = rhs.type;
		this->validate();

		return *this;
	}

	template <typename T>
	DMS_t<T> operator+(DMS_t<T> lhs, const DMS_t<T>& rhs) {
		D_t<T> const lhsD { lhs };
		D_t<T> const rhsD { rhs };

		DMS_t<T> const tmpD { lhsD + rhsD };

		return tmpD;
	}

	template <typename T>
	DMS_t<T>& DMS_t<T>::operator=(const D_t<T>& rhs)
	{
		T const stmp { rhs.deg};
		T const tdeg { std::fabs(rhs.deg) };
		this->deg = std::copysign(std::floor(tdeg), stmp);
		T const min { std::fmod(tdeg, static_cast<T>(1)) * NavigationConstantsNS::deg_min<T> };
		this->min = std::floor(min);
		this->sec = std::fmod(min, static_cast<T>(1)) * NavigationConstantsNS::min_sec<T>;

		this->type = rhs.type;
		this->validate();

		return *this;
	}

	template <typename T>
	DMS_t<T>& DMS_t<T>::operator=(const DM_t<T>& rhs)
	{
		this->deg = rhs.deg;
		T const min { rhs.min };
		this->min = std::floor(min);
		this->sec = std::fmod(min, static_cast<T>(1)) * NavigationConstantsNS::min_sec<T>;

		this->type = rhs.type;
		this->validate();

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
		static const std::string north_desg { "N"sv };
		static const std::string south_desg { "S"sv };
		static const std::string east_desg { "E"sv };
		static const std::string west_desg { "W"sv };

		bool const north { !std::signbit(coord.latM.deg) };
		bool const east { !std::signbit(coord.lonM.deg) };

		const std::string ns_string { (north) ? north_desg : south_desg };
		const std::string ew_string { (east) ? east_desg : west_desg };

		return out << coord.latM << ns_string  << " "sv << coord.lonM << ew_string;
	}

	template <typename T>
	D_t<T>::operator DM_t<T>() const {
		DM_t<T> ret {};

		T const stmp { deg };
		T const ldeg { std::fabs(deg) };
		ret.deg = std::copysign(std::floor(ldeg), stmp);
		T const min { std::fmod(ldeg, static_cast<T>(1)) * NavigationConstantsNS::deg_min<T> };
		ret.min = min;

		ret.type = type;
		ret.validate();

		return ret;
	}

	template <typename T>
	D_t<T>::operator DMS_t<T>() const {
		DMS_t<T> ret {};

		T const stmp { deg };
		T const ldeg { std::fabs(deg) };
		ret.deg = std::copysign(std::floor(ldeg), stmp);
		T const min { std::fmod(ldeg, static_cast<T>(1)) * NavigationConstantsNS::deg_min<T> };
		ret.min = std::floor(min);
		ret.sec = std::fmod(min, static_cast<T>(1)) * NavigationConstantsNS::min_sec<T>;

		ret.type = type;
		ret.validate();

		return ret;
	}

	template <typename T>
	DM_t<T>::operator D_t<T>() const {
		D_t<T> ret {};
		auto const stmp { deg };
		auto const valtmp { std::abs(deg) + (min / NavigationConstantsNS::deg_min<T>) };
		ret.deg = std::copysign(valtmp, stmp);

		ret.type = type;
		ret.validate();

		return ret;
	}

	template <typename T>
	DM_t<T>::operator DMS_t<T>() const {
		DMS_t<T> ret {};
		ret.deg = deg;
		T const lmin { std::floor(min) };
		ret.min = lmin;
		ret.sec = ((min - lmin) * NavigationConstantsNS::min_sec<T>);

		ret.type = type;
		ret.validate();

		return ret;
	}

	template <typename T>
	DMS_t<T>::operator D_t<T>() const {
		D_t<T> ret {};
		auto const stmp { deg };
		auto const valtmp { std::abs(deg) + (min / NavigationConstantsNS::deg_min<T>) + (sec / NavigationConstantsNS::deg_sec<T>) };
		ret.deg = std::copysign(valtmp, stmp);

		ret.type = type;
		ret.validate();

		return ret;
	}

	template <typename T>
	DMS_t<T>::operator DM_t<T>() const {
		DM_t<T> ret {};
		ret.deg = deg;
		ret.min = min + (sec / NavigationConstantsNS::min_sec<T>);

		ret.type = type;
		ret.validate();

		return ret;
	}

	template <typename T>
	void D_t<T>::validate() const {
		switch (type) {
		case CoordinatesType::NONE: // No rules!
		{
			// No validation...
		}
		break;
		case CoordinatesType::LATITUDE: // 90 > x > -90
		{
			assert((deg < static_cast<T>(90)) && (deg > static_cast<T>(-90)));
		}
		break;
		case CoordinatesType::LONGITUDE: // 180 > x > -180
		{
			assert((deg < static_cast<T>(180)) && (deg > static_cast<T>(-180)));
		}
		break;
		case CoordinatesType::GENERAL: // 360 > x > -360
		{
			assert((deg < static_cast<T>(360)) && (deg > static_cast<T>(-360)));
		}
		break;
		}
	};

	template <typename T>
	void DM_t<T>::validate() const {
		switch (type) {
		case CoordinatesType::NONE: // No rules!
		{
			// No validation...
		}
		break;
		case CoordinatesType::LATITUDE: // 90 > x > -90
		{
			assert((deg < static_cast<T>(90)) && (deg > static_cast<T>(-90)));
		}
		break;
		case CoordinatesType::LONGITUDE: // 180 > x > -180
		{
			assert((deg < static_cast<T>(180)) && (deg > static_cast<T>(-180)));
		}
		break;
		case CoordinatesType::GENERAL: // 360 > x > -360
		{
			assert((deg < static_cast<T>(360)) && (deg > static_cast<T>(-360)));
		}
		break;
		}
		assert((min < static_cast<T>(60)) && min >= static_cast<T>(0));
	};

	template <typename T>
	void DMS_t<T>::validate() const {
		switch (type) {
		case CoordinatesType::NONE: // No rules!
		{
			// No validation...
		}
		break;
		case CoordinatesType::LATITUDE: // 90 > x > -90
		{
			assert((deg < static_cast<T>(90)) && (deg > static_cast<T>(-90)));
		}
		break;
		case CoordinatesType::LONGITUDE: // 180 > x > -180
		{
			assert((deg < static_cast<T>(180)) && (deg > static_cast<T>(-180)));
		}
		break;
		case CoordinatesType::GENERAL: // 360 > x > -360
		{
			assert((deg < static_cast<T>(360)) && (deg > static_cast<T>(-360)));
		}
		break;
		}
		assert((min < static_cast<T>(60)) && min >= static_cast<T>(0));
		assert((sec < static_cast<T>(60)) && sec >= static_cast<T>(0));
	};

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const D_t<TN>& coord) {
		return out << std::abs(coord.deg);
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const DM_t<TN>& coord) {
		return out << std::abs(coord.deg) << " "sv << coord.min << "'"sv;
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const DMS_t<TN>& coord) {
		return out << std::abs(coord.deg) << " "sv << coord.min << "' "sv << coord.sec << "\""sv;
	}

} //CoordinatesNS