#pragma once

#include <cmath>
#include <initializer_list>
#include <iostream>

#include "nav_constants.h"

using namespace std::literals::string_literals;

namespace CoordinatesNS {
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
		friend Nav_vec_t<TN> operator+ (Nav_vec_t<TN> lhs, const Nav_vec_t<TN>& rhs);
		template <typename TN>
		friend Nav_vec_t<TN> operator+ (Nav_vec_t<TN> lhs, const T& rhs);
		template <typename TN>
		friend Nav_vec_t<TN> operator* (Nav_vec_t<TN> lhs, const T& rhs);

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
	Nav_vec_t<T> operator+(Nav_vec_t<T> lhs, const Nav_vec_t<T>& rhs)
	{
		Cart_vec_t<T> const cv1 { lhs };
		Cart_vec_t<T> const cv2 { rhs };

		Cart_vec_t<T> const ans { cv1 + cv2 };

		lhs = ans;

		return lhs;
	}

	template <typename T>
	T radians(T deg) {
		//static const T pi_to_rads { (std::acos(static_cast<T>(-1))) / static_cast<T>(180) };
		constexpr T pi_to_rads { my_pi<T> / static_cast<T>(180) };

		T rad { deg * pi_to_rads };

		return rad;
	}

	template <typename T>
	T degrees(T rad) {
		//static const T pi_to_degs { static_cast<T>(180) / std::acos(static_cast<T>(-1)) };
		constexpr T pi_to_degs { static_cast<T>(180) / my_pi<T> };

		T deg { rad * pi_to_degs };

		return deg;
	}

	template <typename T>
	Nav_vec_t<T>& Nav_vec_t<T>::operator= (const Cart_vec_t<T>& rhs)
	{
		T const X { std::abs(rhs.X) };
		T const Y { std::abs(rhs.Y) };
		constexpr T M0 { static_cast<T>(0) };
		constexpr T M90 { static_cast<T>(90) };
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
	Nav_vec_t<T> operator+ (Nav_vec_t<T> lhs, const T& rhs)
	{
		lhs.distance += rhs;

		return lhs;
	}

	template <typename T>
	Nav_vec_t<T> operator* (Nav_vec_t<T> lhs, const T& rhs)
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
		constexpr T M0 { static_cast<T>(0) };
		constexpr T M90 { static_cast<T>(90) };
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

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const Nav_vec_t<TN>& nv_) {
		return out << nv_.distance << " "s << nv_.direction << "d"s;
	}

	template <typename TN>
	std::ostream& operator<<(std::ostream& out, const Cart_vec_t<TN>& cv_) {
		return out << cv_.X << "X "s << cv_.Y << "Y"s;
	}
}