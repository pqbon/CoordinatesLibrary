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

		decltype(p0.phi()) const rlat2 { std::atan2(std::sin(rlat0) + std::sin(rlat1), std::hypot(std::cos(rlat0) + Bx, By)) };

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

		decltype(p0.phi()) const rlat2 { std::atan2(z_, std::hypot(x_, y_)) };
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

	template <typename T>
	auto rectl_dist_nm(T p0, T p1) -> decltype(p0.phi()) {
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlat1 { p1.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const rlon1 { p1.lambda() };
		decltype(p0.phi()) const x_ { (rlat1 - rlat0) * std::cos((rlon0 + rlon1) / 2) };
		decltype(p0.phi()) const y_ { rlon1 - rlon0 };


		decltype(p0.phi()) const dist_rad { std::hypot(x_, y_) };
		decltype(p0.phi()) const dist_nm { radians2nm(dist_rad) };

		return dist_nm;
	}

	template <typename T>
	auto rectl_brng(T p0, T p1) -> decltype(p0.phi()) {
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlat1 { p1.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const rlon1 { p1.lambda() };
		decltype(p0.phi()) const drlat { rlat1 - rlat0 };
		decltype(p0.phi()) const drlon { rlon1 - rlon0 };

		decltype(p0.phi()) const a {3443.9184665};
		decltype(p0.phi()) const R1 { a * (1 - std::exp(2)) / std::pow(1 - std::exp(2) * std::pow(std::sin(rlat0),2), (static_cast<decltype(p0.phi())>(3) / static_cast<decltype(p0.phi())>(2))) };
		decltype(p0.phi()) const R2 { a / std::sqrt(1 - std::exp(2) * (std::sin(rlat0)) ^ 2) };

		decltype(p0.phi()) const distance_North { R1 * drlat };
		decltype(p0.phi()) const distance_East { R2 * std::cos(rlat0) * drlon };

		decltype(p0.phi()) const rbrng { std::remainder(std::atan2(distance_East, distance_North), 2 * NavigationConstantsNS::my_pi<decltype(p0.phi())>) };

		decltype(p0.phi()) const dbrng { radians2deg(rbrng) };

		return dbrng;
	}

	template <typename T>
	auto rhumb_dist_nm(T p0, T p1) -> decltype(p0.phi()) {
		//if (abs(lat2 - lat1) < sqrt(TOL)) {
		//	q = cos(lat1)
		//} else {
		//	q = (lat2 - lat1) / log(tan(lat2 / 2 + pi / 4) / tan(lat1 / 2 + pi / 4))
		//}
		//d = sqrt((lat2 - lat1) ^ 2 + q ^ 2 * (lon2 - lon1) ^ 2)
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

		decltype(p0.phi()) const dist_rad { std::hypot(delta_phi, q * delta_lambda) };
		decltype(p0.phi()) const dist_nm { radians2nm(dist_rad) };

		return dist_nm;
	}

	template <typename T>
	auto rhumb_brng(T p0, T p1) -> decltype(p0.phi()) {
		//tc= mod(atan2(lon1-lon2,log(tan(lat2/2+pi/4)/tan(lat1/2+pi/4))),2*pi)
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlat1 { p1.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const rlon1 { p1.lambda() };

		decltype(p0.phi()) const term0 { NavigationConstantsNS::my_pi<decltype(p0.phi())> / 4 + rlat1 / 2 };
		decltype(p0.phi()) const term1 { NavigationConstantsNS::my_pi<decltype(p0.phi())> / 4 + rlat0 / 2 };

		decltype(p0.phi()) const deltaPsi { std::log(std::tan(term0) / std::tan(term1)) };

		decltype(p0.phi()) deltaLon { rlon1 - rlon0 };
		if (std::fabs(deltaLon) > NavigationConstantsNS::my_pi<decltype(p0.phi())>) {
			deltaLon = deltaLon > 0 ? -(2 * NavigationConstantsNS::my_pi<decltype(p0.phi())> -deltaLon) : (2 * NavigationConstantsNS::my_pi<decltype(p0.phi())> -deltaLon);
		}

		decltype(p0.phi()) const theta { std::atan2(deltaLon, deltaPsi) };

		decltype(p0.phi()) const dbrng { radians2degrees(theta) };

		return dbrng;
	}

	template <typename T0, typename T1>
	auto rhumb_start_vec(T0 p0, T1 vec) -> T0 {
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlon0 { p0.lambda() };
		decltype(p0.phi()) const theta { degress2radians(vec.direction) };
		decltype(p0.phi()) const delta { nm2radians(vec.distance) };

		decltype(p0.phi()) const diffLat { delta * std::cos(theta) };

		decltype(p0.phi()) const rlat1t { rlat0 + diffLat };

		decltype(p0.phi()) const diffPsi { std::log(std::tan(rlat1t / 2 + NavigationConstantsNS::my_pi<decltype(p0.phi())> / 4) / std::tan(rlat0 / 2 + NavigationConstantsNS::my_pi<decltype(p0.phi())> / 4)) };
		constexpr decltype(p0.phi()) eps { std::numeric_limits<decltype(p0.phi())>::min() };
 		decltype(p0.phi()) const q_ { (std::fabs(diffPsi) > eps) ? diffLat / diffPsi : std::cos(rlat0) };

		decltype(p0.phi()) const diffLon { delta * std::sin(theta) / q_ };

		decltype(p0.phi()) const rlon1 { rlon0 + diffLon };

		decltype(p0.phi()) rlat1 { rlat1t };
		if (std::fabs(rlat1) > NavigationConstantsNS::my_pi<decltype(p0.phi())> / 2)
			rlat1 = rlat1t > 0 ? NavigationConstantsNS::my_pi<decltype(p0.phi())> - rlat1t : -NavigationConstantsNS::my_pi<decltype(p0.phi())> - rlat1t;

		decltype(p0.phi()) const lat1 { radians2degrees(rlat1) };
		decltype(p0.phi()) const lon1 { std::remainder(radians2degrees(rlon1) + static_cast<decltype(p0.phi())>(540), static_cast<decltype(p0.phi())>(360)) - static_cast<decltype(p0.phi())>(180) };

		CoordinatesNS::D_t<decltype(p0.phi())> const lat1D { lat1 };
		CoordinatesNS::D_t<decltype(p0.phi())> const lon1D { lon1 };

		T0 ret {};
		ret.lat(lat1D);
		ret.lon(lon1D);

		return ret;
	}

	template <typename T>
	auto rhumb_midpoint(T p0, T p1) -> T {
		decltype(p0.phi()) const rlat0 { p0.phi() };
		decltype(p0.phi()) const rlat1 { p1.phi() };
		decltype(p0.phi()) rlon0 { p0.lambda() };
		decltype(p0.phi()) const rlon1 { p1.lambda() };

		if (std::fabs(rlon1 - rlon0) > NavigationConstantsNS::my_pi<decltype(p0.phi())> * 2) {
			rlon0 += 2 * NavigationConstantsNS::my_pi<decltype(p0.phi())>;
		}

		decltype(p0.phi()) const rlat2 { (rlat0 + rlat1) / 2 };
		decltype(p0.phi()) const f1 {std::tan(NavigationConstantsNS::my_pi<decltype(p0.phi())> / 4 + rlat0 / 2) };
		decltype(p0.phi()) const f2 { std::tan(NavigationConstantsNS::my_pi<decltype(p0.phi())> / 4 + rlat1 / 2) };
		decltype(p0.phi()) const f3 { std::tan(NavigationConstantsNS::my_pi<decltype(p0.phi())> / 4 + rlat2 / 2) };

		decltype(p0.phi()) rlon2 { ((rlon1 - rlon0) * std::log(f3) + rlon0 * std::log(f2) - rlon1 * std::log(f1)) / std::log(f2 / f1) };

		if (!std::isfinite(rlon2)) {
			rlon2 = (rlon0 + rlon1) / 2;
		}

		decltype(p0.phi()) const lat2 { radians2degrees(rlat2) };
		decltype(p0.phi()) const lon2 { std::remainder(radians2degrees(rlon2) + static_cast<decltype(p0.phi())>(540), static_cast<decltype(p0.phi())>(360)) - static_cast<decltype(p0.phi())>(180) };

		CoordinatesNS::D_t<decltype(p0.phi())> const lat2D { lat2 };
		CoordinatesNS::D_t<decltype(p0.phi())> const lon2D { lon2 };

		T ret {};
		ret.lat(lat2D);
		ret.lon(lon2D);

		return ret;
	}
}