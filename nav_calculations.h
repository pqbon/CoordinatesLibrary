#pragma once

#include <cmath>
#include <cstdlib>
#include <cassert>

#include "nav_constants.h"
#include "nav_types.h"
#include "nav_coordinates.h"


namespace CoordinatesNS {
	template <typename T>
	auto grtcrcl_dist_small_nm(T p0, T p1) -> decltype(p0.phi()) {
		//d = 2 * asin(sqrt((sin[(lat1 - lat2) / 2]) ^ 2 +
		//	cos(lat1) * cos(lat2) * (sin[(lon1 - lon2) / 2]) ^ 2))
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlat1 { p1.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const rlon1 { p1.lambda() };

		decltype(p0.phi()) const rlatdiff { rlat0 - rlat1 };
		decltype(p0.phi()) const rlondiff { rlon0 - rlon1 };
		decltype(p0.phi()) const sin_latdiff { std::sin(rlatdiff / 2) };
		decltype(p0.phi()) const sin_londiff { std::sin(rlondiff / 2) };
		decltype(p0.phi()) const cos_lat0 { std::cos(rlat0) };
		decltype(p0.phi()) const cos_lat1 { std::cos(rlat1) };
		decltype(p0.phi()) const dist_rad { 2 * std::asin(std::sqrt(std::pow(sin_latdiff, 2) + cos_lat0 * cos_lat1 * std::pow(sin_londiff, 2))) };
		decltype(p0.phi()) const dist_nm { radians2nm(dist_rad) };

		return dist_nm;
	}

	template <typename T>
	auto grtcrcl_dist_nm(T p0, T p1) -> decltype(p0.phi()) {
		//d=acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon1-lon2))
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlat1 { p1.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const rlon1 { p1.lambda() };

		decltype(p0.phi()) const rlon0diff { rlon1 - rlon0 };
		decltype(p0.phi()) const cos_londiff { std::cos(rlon0diff) };
		decltype(p0.phi()) const cos_lat0 { std::cos(rlat0) };
		decltype(p0.phi()) const cos_lat1 { std::cos(rlat1) };
		decltype(p0.phi()) const sin_lat0 { std::sin(rlat0) };
		decltype(p0.phi()) const sin_lat1 { std::sin(rlat1) };
		decltype(p0.phi()) const dist_rad { std::acos((sin_lat0 * sin_lat1) + (cos_lat0 * cos_lat1 * cos_londiff)) };
		decltype(p0.phi()) const dist_nm { radians2nm(dist_rad) };

		return dist_nm;
	}

	template <typename T>
	auto grtcrcl_dist_haversine_nm(T p0, T p1) -> decltype(p0.phi()) {
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlat1 { p1.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const rlon1 { p1.lambda() };
		decltype(p0.phi()) const rlatdiff { rlat1 - rlat0 };
		decltype(p0.phi()) const rlondiff { rlon1 - rlon0 };
		decltype(p0.phi()) const rsinlatdiff { std::sin(rlatdiff / 2) };
		decltype(p0.phi()) const rsinlondiff { std::sin(rlondiff / 2) };

		decltype(p0.phi()) const ra { std::pow(rsinlatdiff, 2) + std::cos(rlat0) * std::cos(rlat1) * std::pow(rsinlondiff, 2) };
		decltype(p0.phi()) const dist_rad { 2 * std::atan2(std::sqrt(ra), std::sqrt(1 - ra)) };
		decltype(p0.phi()) const dist_nm { radians2nm(dist_rad) };

		return dist_nm;
	}

	template <typename T>
	auto rectl_dist_nm(T p0, T p1) -> decltype(p0.phi()) {
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlat1 { p1.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const rlon1 { p1.lambda() };
		decltype(p0.phi()) const x_ { (rlat1 - rlat0) * std::cos((rlon0 + rlon1) / 2) };
		decltype(p0.phi()) const y_ { rlon1 - rlon0 };


		decltype(p0.phi()) const dist_rad { std::sqrt(std::pow(x_, 2) + std::pow(y_, 2)) };
		decltype(p0.phi()) const dist_nm { radians2nm(dist_rad) };

		return dist_nm;
	}

	template <typename T>
	auto rhumb_dist_nm(T p0, T p1) -> decltype(p0.phi()) {
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlat1 { p1.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const rlon1 { p1.lambda() };

		decltype(p0.phi()) const delta_phi { rlat1 - rlat0 };

		decltype(p0.phi()) const delta_psi { std::log(std::tan(NavigationConstantsNS::my_pi<decltype(p0.phi())> / 4 + rlat1 / 2) / std::tan(NavigationConstantsNS::my_pi<decltype(p0.phi())> / 4 + rlat0 / 2)) };

		constexpr decltype(p0.phi()) eps { std::numeric_limits<decltype(p0.phi())>::min() };
		decltype(p0.phi()) const q { (std::abs(delta_psi) > eps) ? (delta_phi) / (delta_psi) : std::cos(rlat0) };

		decltype(p0.phi()) delta_lambda { rlon1 - rlon0 };
		if (std::abs(rlon1 - rlon0) > NavigationConstantsNS::my_pi<decltype(p0.phi())>) {
			delta_lambda = (delta_lambda > 0) ? -(2 * NavigationConstantsNS::my_pi<decltype(p0.phi())> -delta_lambda) : (2 * NavigationConstantsNS::my_pi<decltype(p0.phi())> -delta_lambda);
		}

		decltype(p0.phi()) const dist_rad { std::sqrt(std::pow(delta_phi, 2) + std::pow(q, 2) * std::pow(delta_lambda, 2)) };
		decltype(p0.phi()) const dist_nm { radians2nm(dist_rad) };

		return dist_nm;
	}

	template <typename T>
	auto grtcrcl_init_brng(T p0, T p1) -> decltype(p0.phi()) {
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlat1 { p1.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const rlon1 { p1.lambda() };

		decltype(p0.phi()) const y_ { std::sin(rlon1 - rlon0) * std::cos(rlat1) };
		decltype(p0.phi()) const x_ { std::cos(rlat0) * std::sin(rlat1) - std::sin(rlat0) * std::cos(rlat1) * std::cos(rlon1 - rlon0) };
		decltype(p0.phi()) const theta { std::atan2(y_, x_) };

		decltype(p0.phi()) const brng { std::remainder(radians2degrees(theta) + static_cast<decltype(p0.phi())>(360), static_cast<decltype(p0.phi())>(360)) };

		return brng;
	}

	template <typename T>
	auto grtcrcl_midpoint(T p0, T p1) -> T {
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlat1 { p1.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const rlon1 { p1.lambda() };

		decltype(p0.phi()) const Bx { std::cos(rlat1) * std::cos(rlon1 - rlon0) };
		decltype(p0.phi()) const By { std::cos(rlat1) * std::sin(rlon1 - rlon0) };

		decltype(p0.phi()) const rlat2 { std::atan2(std::sin(rlat0) + std::sin(rlat1), std::sqrt(std::pow(std::cos(rlat0) + Bx, 2) + std::pow(By, 2))) };

		decltype(p0.phi()) const rlon2 { rlon0 + std::atan2(By, std::cos(rlat0) + Bx) };

		decltype(p0.phi()) const lat2 { radians2degrees(rlat2) };
		decltype(p0.phi()) const lon2 { std::remainder((radians2degrees(rlon2) + static_cast<decltype(p0.phi())>(540)), static_cast<decltype(p0.phi())>(360)) - static_cast<decltype(p0.phi())>(180) };


		CoordinatesNS::D_t<decltype(p0.phi())> const lat2D { lat2 };
		CoordinatesNS::D_t<decltype(p0.phi())> const lon2D { lon2 };

		T ret {};
		ret.lat(lat2D);
		ret.lon(lon2D);

		return ret;
	}

	template <typename T>
	auto grtcrcl_frac_point(T p0, T p1, decltype(p0.phi()) frac, decltype(p0.phi()) dist) -> T {
		assert(frac < static_cast<decltype(p0.phi())>(1));
		assert(frac > static_cast<decltype(p0.phi())>(0));

		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlat1 { p1.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const rlon1 { p1.lambda() };

		decltype(p0.phi()) const delta { nm2radians(dist) };
		decltype(p0.phi()) const a_ { std::sin((1 - frac) * delta) / std::sin(delta) };
		decltype(p0.phi()) const b_ { std::sin(frac * delta) / std::sin(delta) };
		decltype(p0.phi()) const x_ { a_ * std::cos(rlat0) * std::cos(rlon0) + b_ * std::cos(rlat1) * std::cos(rlon1) };
		decltype(p0.phi()) const y_ { a_ * std::cos(rlat0) * std::sin(rlon0) + b_ * std::cos(rlat1) * std::sin(rlon1) };
		decltype(p0.phi()) const z_ { a_ * std::sin(rlat0) + b_ * std::sin(rlat1) };

		decltype(p0.phi()) const rlat2 { std::atan2(z_, std::sqrt(std::pow(x_, 2) + std::pow(y_, 2))) };
		decltype(p0.phi()) const rlon2 { std::atan2(y_, x_) };

		decltype(p0.phi()) const lat2 { radians2degrees(rlat2) };
		decltype(p0.phi()) const lon2 { radians2degrees(rlon2) };


		CoordinatesNS::D_t<decltype(p0.phi())> const lat2D { lat2 };
		CoordinatesNS::D_t<decltype(p0.phi())> const lon2D { lon2 };

		T ret {};
		ret.lat(lat2D);
		ret.lon(lon2D);

		return ret;
	}

	template <typename T0, typename T1>
	auto grtcrcl_start_vec(T0 p0,  T1 vec) -> T0 {
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const theta { degress2radians(vec.direction) };
		decltype(p0.phi()) const delta { nm2radians(vec.distance) };


		decltype(p0.phi()) const rlat1 { std::asin(std::sin(rlat0) * std::cos(delta) + std::cos(rlat0) * std::sin(delta) * std::cos(theta)) };
		decltype(p0.phi()) const rlon1 { rlon0 + std::atan2(std::sin(theta) * std::sin(delta) * std::cos(rlat0), std::cos(delta) - std::sin(rlat0) * std::sin(rlat1)) };
		decltype(p0.phi()) const lat1 { radians2degrees(rlat1) };
		decltype(p0.phi()) const lon1 { std::remainder(radians2degrees(rlon1) + static_cast<decltype(p0.phi())>(540), static_cast<decltype(p0.phi())>(360)) - static_cast<decltype(p0.phi())>(180) };


		CoordinatesNS::D_t<decltype(p0.phi())> const lat1D { lat1 };
		CoordinatesNS::D_t<decltype(p0.phi())> const lon1D { lon1 };

		T0 ret {};
		ret.lat(lat1D);
		ret.lon(lon1D);

		return ret;
	}

}