#pragma once

#include <cmath>
#include <initializer_list>
#include <iostream>

using namespace std::literals::string_literals;

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
		T const min { std::abs(rhs.deg - this->deg) * static_cast<T>(deg_min) };
		this->min = std::floor(min);
		this->sec = ((min - std::floor(min)) * static_cast<T>(min_sec));

		return *this;
	}

	template <typename T>
	DMS_t<T>& DMS_t<T>::operator=(const DM_t<T>& rhs)
	{
		this->deg = rhs.deg;
		T const min { rhs.min };
		this->min = std::floor(rhs.min);
		this->sec = ((min - rhs.min) * static_cast<T>(min_sec));

		return *this;
	}

	template <typename T>
	struct Nav_vec_t
	{
		Nav_vec_t<T>(T distance_, T direction_) : distance { distance_ }, direction { direction_ }
		{
		}

		Nav_vec_t<T>(const Cart_vec_t<T>& cvec)
		{
			*this = cvec;
		}
		Nav_vec_t<T>() = default;
		~Nav_vec_t<T>() = default;
		Nav_vec_t<T>(const Nav_vec_t<T>&) = default;
		Nav_vec_t<T>(Nav_vec_t<T>&&) = default;
		Nav_vec_t<T>& operator=(const Nav_vec_t<T>&) = default;
		Nav_vec_t<T>& operator=(Nav_vec_t<T>&&) = default;

		Nav_vec_t<T>& operator=(const Cart_vec_t<T>& rhs);

		template <typename TN>
		friend Nav_vec_t<TN> operator+ (Nav_vec_t<TN> lhs, const Nav_vec_t<TN> &rhs);
		template <typename TN>
		friend Nav_vec_t<TN> operator+ (Nav_vec_t<TN> lhs, const T &rhs);
		template <typename TN>
		friend Nav_vec_t<TN> operator* (Nav_vec_t<TN> lhs, const T &rhs);

		template <typename TN>
		friend std::ostream& operator<<(std::ostream& out, const Nav_vec_t<TN>& nv_);

		T distance {};
		T direction {};
	};

	template <typename T>
	struct Cart_vec_t
	{
		Cart_vec_t<T>(T x_, T y_) : X { x_ }, Y { y_ }
		{
		}

		Cart_vec_t<T>(const Nav_vec_t<T>& nvec)
		{
			*this = nvec;
		}

		Cart_vec_t<T>() = default;
		~Cart_vec_t<T>() = default;
		Cart_vec_t<T>(const Cart_vec_t<T>&) = default;
		Cart_vec_t<T>(Cart_vec_t<T>&&) = default;
		Cart_vec_t<T>& operator=(const Cart_vec_t<T>&) = default;
		Cart_vec_t<T>& operator=(Cart_vec_t<T>&&) = default;

		Cart_vec_t<T>& operator=(const Nav_vec_t<T>& rhs);

		template <typename TN>
		friend Cart_vec_t<TN> operator+ (Cart_vec_t<TN> lhs, const Cart_vec_t<TN>& rhs);

		template <typename TN>
		friend std::ostream& operator<<(std::ostream& out, const Nav_vec_t<TN>& cv_);

		T X;
		T Y;
	};

	template <typename T>
	Nav_vec_t<T> operator+(Nav_vec_t<T> lhs, const Nav_vec_t<T> &rhs)
	{
		Cart_vec_t<T> const cv1 { lhs };
		Cart_vec_t<T> const cv2 { rhs };

		Cart_vec_t<T> const ans { cv1 + cv2 };

		lhs = ans;

		return lhs;
	}

	template <typename T>
	constexpr T my_pi { static_cast<T>(3.141592653589793238462643383279502884197169399375105820974944592307816406286) };

	template <typename T>
	T radians(T deg) {
		//static const T pi_to_rads { (std::acos(static_cast<T>(-1))) / static_cast<T>(180) };
		constexpr T pi_to_rads { my_pi<T> / static_cast<T>(180)};

		T rad { deg * pi_to_rads };

		return rad;
	}

	template <typename T>
	T degrees(T rad) {
		//static const T pi_to_degs { static_cast<T>(180) / std::acos(static_cast<T>(-1)) };
		constexpr T pi_to_degs { static_cast<T>(180) / my_pi<T>};

		T deg { rad * pi_to_degs };

		return deg;
	}

	template <typename T>
	Nav_vec_t<T>& Nav_vec_t<T>::operator= (const Cart_vec_t<T>& rhs)
	{
		T const X { std::abs(rhs.X) };
		T const Y { std::abs(rhs.Y) };
		constexpr T M0   { static_cast<T>(0)   };
		constexpr T M90  { static_cast<T>(90)  };
		constexpr T M180 { static_cast<T>(180) };
		constexpr T M270 { static_cast<T>(270) };
		constexpr T M360 { static_cast<T>(360) };

		//r = sqrt(x2 + y2)
		//theta = atan(y / x)

		this->distance = std::hypot(rhs.X, rhs.Y);
		T theta { std::atan(Y / X) };

		if ((rhs.X > 0) && (rhs.Y > 0))
		{
			this->direction = M90 - degrees(theta);
		}
		else if ((rhs.X > 0) && (rhs.Y < 0))
		{
			this->direction = M90 + degrees(theta);
		}
		else if ((rhs.X < 0) && (rhs.Y < 0))
		{
			this->direction = M180 + degrees(theta);
		}
		else if ((rhs.X < 0) && (rhs.Y > 0))
		{
			this->direction = M270 + degrees(theta);
		}
		else if ((rhs.X > 0) && (rhs.Y == 0)) //West
		{
			this->direction = M90;
		}
		else if ((rhs.X < 0) && (rhs.Y == 0)) //East
		{
			this->direction = M270;
		}
		else if ((rhs.X == 0) && (rhs.Y > 0)) //North
		{
			this->direction = M0;
		}
		else if ((rhs.X == 0) && (rhs.Y < 0)) //South
		{
			this->direction = M180;
		}
		else
		{
			this->direction = M360;
		}

		return *this;
	}
		
	template <typename T>
	Nav_vec_t<T> operator+ (Nav_vec_t<T> lhs, const T &rhs)
	{
		lhs.distance += rhs;

		return lhs;
	}
	
	template <typename T>
	Nav_vec_t<T> operator* (Nav_vec_t<T> lhs, const T &rhs)
	{
		lhs.distance *= rhs;

		return lhs;
	}

	template <typename T>
	Cart_vec_t<T>& Cart_vec_t<T>::operator=(const Nav_vec_t<T>& rhs)
	{

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
			theta = radians(M90 - rhs.direction);
			magX = rhs.distance;
			magY = rhs.distance;
		}
		else if (rhs.direction < M180)
		{
			theta = radians(rhs.direction - M90);
			magX = rhs.distance;
			magY = -rhs.distance;
		}
		else if (rhs.direction < M270)
		{
			theta = radians(M90 - (rhs.direction - M180));
			magX = -rhs.distance;
			magY = -rhs.distance;
		}
		else //theta < M360
		{
			theta = radians(rhs.direction - M270);
			magX = -rhs.distance;
			magY = rhs.distance;
		}

		this->X = magX * std::cos(theta);
		this->Y = magY * std::sin(theta);

		return *this;
	}

	template <typename T>
	Cart_vec_t<T> operator+ (Cart_vec_t<T> lhs, const Cart_vec_t<T>& rhs)
	{
		lhs.X += rhs.X;
		lhs.Y += rhs.Y;

		return lhs;
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
		bool const north { !std::signbit(coord.latM.deg) };
		bool const east { !std::signbit(coord.lonM.deg) };
		static const std::string north_desg { "N"s };
		static const std::string south_desg { "S"s };
		static const std::string east_desg { "E"s };
		static const std::string west_desg { "W"s };

		const std::string ns_string { (north) ? north_desg : south_desg };
		const std::string ew_string { (east) ? east_desg : west_desg };

		return out << coord.latM << ns_string  << " "s << coord.lonM << ew_string;
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const Nav_vec_t<TN>& nv_) {
		return out << nv_.distance << " "s << nv_.direction << "d"s;
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const Cart_vec_t<TN>& cv_) {
		return out << cv_.X << "X "s << cv_.Y << "Y"s;
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const D_t<TN>& coord) {
		return out << std::abs(coord.deg) << "d"s;
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const DM_t<TN>& coord) {
		return out << std::abs(coord.deg) << "d "s << coord.min << "m"s;
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const DMS_t<TN>& coord) {
		return out << std::abs(coord.deg) << "d "s << coord.min << "m "s << coord.sec << "s"s;
	}

} //CoordinatesNS