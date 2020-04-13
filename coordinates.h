#pragma once

#include <cmath>
#include <initializer_list>
#include <iostream>

namespace CoordinatesNS {

	constexpr int deg_min { 60 };
	constexpr int min_sec { 60 };
	constexpr int deg_sec { 60 * 60 };

	template <typename T>
	class Coordinates;
	template <typename T>
	struct D_t;
	template <typename T>
	struct DM_t;
	template <typename T>
	struct DMS_t;
	template <typename T>
	struct Nav_vec_t;
	template <typename T>
	struct Cart_vec_t;

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const Coordinates<TN>& coord);

	template <class T>
	class Coordinates
	{
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

		template <typename T0, typename T1>
		friend void convert(T0 &t0, const T1 &t1);

		template <typename TN>
		friend std::ostream& operator<<(std::ostream& out, const Coordinates<TN>& coord);

	private:
		T latM {};

		T lonM {};
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

		friend D_t<T> operator+(const D_t<T>& lhs, const D_t<T>& rhs);
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

		friend DM_t<T> operator+(const DM_t<T>& lhs, const DM_t<T>& rhs);
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

		friend DMS_t<T> operator+(const DMS_t<T>& lhs, const DMS_t<T>& rhs);
		DMS_t<T>& operator=(const D_t<T>& rhs);
		DMS_t<T>& operator=(const DM_t<T>& rhs);
	};

	template <typename T>
	D_t<T>& operator+(const D_t<T>& lhs, const D_t<T>& rhs)
	{
		D_t<T> tmp {};

		tmp.deg = lhs.deg + rhs.deg;

		return tmp;
	}

	template <typename T>
	D_t<T>& D_t<T>::operator=(const DM_t<T>& rhs)
	{
		this->deg = rhs.deg + (rhs.min / static_cast<T>(deg_min));

		return *this;
	}

	template <typename T>
	D_t<T>& D_t<T>::operator=(const DMS_t<T>& rhs)
	{
		this->deg = rhs.deg + (rhs.min / static_cast<T>(deg_min)) + (rhs.sec / static_cast<T>(deg_sec));

		return *this;
	}

	template <typename T>
	DM_t<T>& operator+(const DM_t<T>& lhs, const DM_t<T>& rhs) {
		DM_t<T> tmpDM {};
		D_t<T> tmpD {};
		D_t<T> lhsD { lhs };
		D_t<T> rhsD { rhs };

		tmpD = lhsD + rhsD;

		tmpDM = tmpD;

		return tmpDM;
	}

	template <typename T>
	DM_t<T>& DM_t<T>::operator=(const D_t<T>& rhs)
	{
		this->deg = std::floor(rhs.deg) ;
		this->min = std::abs(rhs.deg - this->deg) * static_cast<T>(deg_min);

		return *this;
	}

	template <typename T>
	DM_t<T>& DM_t<T>::operator=(const DMS_t<T>& rhs)
	{
		this->deg = rhs.deg;
		this->min = rhs.min + (rhs.sec / static_cast<T>(min_sec));

		return *this;
	}

	template <typename T>
	DMS_t<T>& operator+(const DMS_t<T>& lhs, const DMS_t<T>& rhs) {
		DMS_t<T> tmpDMS {};
		D_t<T> tmpD {};
		D_t<T> lhsD { lhs };
		D_t<T> rhsD { rhs };

		tmpD = lhsD + rhsD;
		tmpDMS = tmpD;

		return tmpDMS;
	}

	template <typename T>
	DMS_t<T>& DMS_t<T>::operator=(const D_t<T>& rhs)
	{
		this->deg = std::floor(rhs.deg);
		T min = std::abs(rhs.deg - this->deg) * static_cast<T>(deg_min);
		this->min = std::floor(min);
		this->sec = ((min - std::floor(min)) * static_cast<T>(min_sec));

		return *this;
	}

	template <typename T>
	DMS_t<T>& DMS_t<T>::operator=(const DM_t<T>& rhs)
	{
		this->deg = rhs.deg;
		T min = rhs.min;
		this->min = std::floor(rhs.min);
		this->sec = ((min - rhs.min) * static_cast<T>(min_sec));

		return *this;
	}

	template <typename T>
	struct Nav_vec_t
	{
		Nav_vec_t<T>() = default;
		~Nav_vec_t<T>() = default;
		Nav_vec_t<T>(const Nav_vec_t<T>&) = default;
		Nav_vec_t<T>(Nav_vec_t<T>&&) = default;
		Nav_vec_t<T>& operator=(const Nav_vec_t<T>&) = default;
		Nav_vec_t<T>& operator=(Nav_vec_t<T>&&) = default;

		Nav_vec_t<T>& operator=(const Cart_vec_t<T>& rhs);

		friend Nav_vec_t<T> operator+ (const Nav_vec_t<T> &lhs, const Nav_vec_t<T> &rhs);
		friend Nav_vec_t<T> operator+ (const Nav_vec_t<T> &lhs, const T &rhs);
		friend Nav_vec_t<T> operator* (const Nav_vec_t<T> &lhs, const T &rhs);

		T distance {};
		T direction {};
	};

	template <typename T>
	struct Cart_vec_t
	{
		Cart_vec_t<T>() = default;
		~Cart_vec_t<T>() = default;
		Cart_vec_t<T>(const Cart_vec_t<T>&) = default;
		Cart_vec_t<T>(Cart_vec_t<T>&&) = default;
		Cart_vec_t<T>& operator=(const Cart_vec_t<T>&) = default;
		Cart_vec_t<T>& operator=(Cart_vec_t<T>&&) = default;

		Cart_vec_t<T>& operator=(Nav_vec_t<T>& rhs);

		friend Cart_vec_t<T> operator+ (const Cart_vec_t<T>& lhs, const Cart_vec_t<T>& rhs);

		T X;
		T Y;
	};

	template <typename T>
	Nav_vec_t<T> operator+ (const Nav_vec_t<T> &lhs, const Nav_vec_t<T> &rhs)
	{
		Nav_vec_t<T> tmp;
		Cart_vec_t<T> cv1 = lhs;
		Cart_vec_t<T> cv2 = rhs;

		auto ans = cv1 + cv2;

		tmp = ans;

		return tmp;
	}

	template <typename T>
	Nav_vec_t<T>& Nav_vec_t<T>::operator=(const Cart_vec_t<T>& rhs)
	{
		Nav_vec_t<T> tmp;
		T X = std::abs(rhs.X);
		T Y = std::abs(rhs.Y);
		constexpr T M0   { static_cast<T>(0)   };
		constexpr T M90  { static_cast<T>(90)  };
		constexpr T M180 { static_cast<T>(180) };
		constexpr T M270 { static_cast<T>(270) };
		constexpr T M360 { static_cast<T>(360) };

		//r = sqrt(x2 + y2)
		//theta = atan(y / x)

		tmp.distance = std::sqrt(std::pow(X, 2) + std::pow(Y, 2));
		T theta = std::atan(Y/X);

		if ((rhs.X > 0) && (rhs.Y > 0))
		{
			tmp.direction = M90 - theta;
		}
		else if ((rhs.X > 0) && (rhs.Y < 0))
		{
			tmp.direction = M90 + theta;
		}
		else if ((rhs.X < 0) && (rhs.Y < 0))
		{
			tmp.direction = M180 + theta;
		}
		else if ((rhs.X < 0) && (rhs.Y > 0))
		{
			tmp.direction = M270 + theta;
		}
		else if ((rhs.X > 0) && (rhs.Y == 0)) //West
		{
			tmp.direction = M90;
		}
		else if ((rhs.X < 0) && (rhs.Y == 0)) //East
		{
			tmp.direction = M270;
		}
		else if ((rhs.X == 0) && (rhs.Y > 0)) //North
		{
			tmp.direction = M0;
		}
		else if ((rhs.X == 0) && (rhs.Y < 0)) //South
		{
			tmp.direction = M180;
		}
		else
		{
			tmp.direction = M360;
		}

		return *tmp;
	}
		
	template <typename T>
	Nav_vec_t<T> operator+ (const Nav_vec_t<T> &lhs, const T &rhs)
	{
		Nav_vec_t<T> tmp {};

		tmp.distance = lhs.distance + rhs;
		tmp.direction = lhs.direction;

		return tmp;
	}
	
	template <typename T>
	Nav_vec_t<T> operator* (const Nav_vec_t<T> &lhs, const T &rhs)
	{
		Nav_vec_t<T> tmp {};

		tmp.distance = lhs.distance * rhs;
		tmp.direction = lhs.direction;

		return tmp;
	}

	template <typename T>
	Cart_vec_t<T>& Cart_vec_t<T>::operator=(Nav_vec_t<T>& rhs)
	{
		Cart_vec_t<T> tmp;
		T theta;
		T magX;
		T magY;
		constexpr T M0   { static_cast<T>(0)   };
		constexpr T M90  { static_cast<T>(90)  };
		constexpr T M180 { static_cast<T>(180) };
		constexpr T M270 { static_cast<T>(270) };
		constexpr T M360 { static_cast<T>(360) };


		//x = r × cos(theta)
        //y = r × sin(theta)

		if (rhs.direction < M90)
		{
			theta = M90 - rhs.direction;
			magX = rhs.distance;
			magY = rhs.distance;
		}
		else if (rhs.direction < M180)
		{
			theta = rhs.direction - M90;
			magX = rhs.distance;
			magY = -rhs.distance;
		}
		else if (rhs.direction < M270)
		{
			theta = M90 - (rhs.direction - M180);
			magX = -rhs.distance;
			magY = -rhs.distance;
		}
		else //theta < M360
		{
			theta = rhs.direction - M270;
			magX = -rhs.distance;
			magY = rhs.distance;
		}

		tmp.X = magX * std::cos(theta);
		tmp.Y = magY * std::sin(theta);

		return *tmp;
	}

	template <typename T>
	Cart_vec_t<T> operator+ (const Cart_vec_t<T>& lhs, const Cart_vec_t<T>& rhs)
	{
		Cart_vec_t<T> tmp;

		tmp.X = lhs.X + rhs.X;
		tmp.Y = lhs.Y + rhs.Y;

		return *tmp;
	}

	using D_tF = D_t<float_t>;
	using DM_tF = DM_t<float_t>;
	using DMS_tF = DMS_t<float_t>;
	using Nav_vec_tF = Nav_vec_t<float_t>;
	using Cart_vec_tF = Cart_vec_t<float_t>;

	using CoordinatesDF = Coordinates<D_tF>;
	using CoordinatesDMF = Coordinates<DM_tF>;
	using CoordinatesDMSF = Coordinates<DMS_tF>;

	constexpr D_tF operator""_D(long double degs_);

	constexpr D_tF operator""_ND(long double degs_);
	constexpr D_tF operator""_SD(long double degs_);
	constexpr D_tF operator""_ED(long double degs_);
	constexpr D_tF operator""_WD(long double degs_);

	constexpr D_tF operator""_D(long double degs_)
	{
		D_tF ret(static_cast<float>(degs_));
		return ret;
	}

	constexpr D_tF operator""_ND(long double degs_)
	{
		D_tF ret(static_cast<float>(degs_));
		return ret;
	}

	constexpr D_tF operator""_SD(long double degs_)
	{
		D_tF ret(static_cast<float>(-degs_));
		return ret;
	}

	constexpr D_tF operator""_ED(long double degs_)
	{
		D_tF ret(static_cast<float>(degs_));
		return ret;
	}

	constexpr D_tF operator""_WD(long double degs_)
	{
		D_tF ret(static_cast<float>(-degs_));
		return ret;
	}

	template <typename T0, typename T1>
	void convert(T0 &t0, const T1 &t1)
	{
		t0.lonM = t1.lonM;
		t0.latM = t1.latM;
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const Coordinates<TN> &coord) {
		return out << coord.lat << " " << coord.lon;
	}


} //CoordinatesNS