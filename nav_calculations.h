#pragma once

#include <cmath>
#include <cstdlib>

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

		decltype(p0.phi()) const delta_psi { std::log( std::tan(NavigationConstantsNS::my_pi<decltype(p0.phi())>/4 + rlat1 / 2) / std::tan(NavigationConstantsNS::my_pi<decltype(p0.phi())> / 4 + rlat0 / 2)) };

		constexpr decltype(p0.phi()) eps { std::numeric_limits<decltype(p0.phi())>::min() };
		decltype(p0.phi()) const q { (std::abs(delta_psi) > eps) ? (delta_phi) / (delta_psi) : std::cos(rlat0) };

		decltype(p0.phi()) delta_lambda { rlon1 - rlon0 };
		if (std::abs(rlon1 - rlon0) > NavigationConstantsNS::my_pi<decltype(p0.phi())>) {
			delta_lambda = (delta_lambda > 0) ? -(2 * NavigationConstantsNS::my_pi<decltype(p0.phi())> - delta_lambda) : (2 * NavigationConstantsNS::my_pi<decltype(p0.phi())> - delta_lambda);
		}

		decltype(p0.phi()) const dist_rad { std::sqrt(std::pow(delta_phi, 2) + std::pow(q, 2) * std::pow(delta_lambda, 2)) };
		decltype(p0.phi()) const dist_nm { radians2nm(dist_rad) };

		return dist_nm;
	}

//	template <typename T>
//	auto grtcrcl_dist_small(T p0, T p1) -> Nav_vec_t<decltype(p0.phi())> {
//		//d = 2 * asin(sqrt((sin[(lat1 - lat2) / 2]) ^ 2 +
//		//	cos(lat1) * cos(lat2) * (sin[(lon1 - lon2) / 2]) ^ 2))
//		decltype(p0.phi()) const lat0 { p0.phi() };
//		decltype(p0.phi()) const lat1 { p1.phi() };
//		decltype(p0.phi()) const lon0 { p0.lambda() };
//		decltype(p0.phi()) const lon1 { p1.lambda() };
//		decltype(p0.phi()) const rlat0 { degress2radians(lat0) };
//		decltype(p0.phi()) const rlat1 { degress2radians(lat1) };
//		decltype(p0.phi()) const rlon0 { degress2radians(lon0) };
//		decltype(p0.phi()) const rlon1 { degress2radians(lon1) };
//
//		decltype(p0.phi()) const rlatdiff { rlat0 - rlat1 };
//		decltype(p0.phi()) const rlondiff { rlon0 - rlon1 };
//		decltype(p0.phi()) const sin_latdiff { std::sin(rlatdiff / 2) };
//		decltype(p0.phi()) const sin_londiff { std::sin(rlondiff / 2) };
//		decltype(p0.phi()) const cos_lat0 { std::cos(rlat0) };
//		decltype(p0.phi()) const cos_lat1 { std::cos(rlat1) };
//		decltype(p0.phi()) const sin_lat0 { std::sin(rlat0) };
//		decltype(p0.phi()) const sin_lat1 { std::sin(rlat1) };
//		decltype(p0.phi()) const term0 { std::pow(sin_latdiff, 2) };
//		decltype(p0.phi()) const term1 { cos_lat0 * cos_lat1 * std::pow(sin_londiff, 2) };
//		decltype(p0.phi()) const dist_rad { 2 * std::asin(std::sqrt(term0 + term1)) };
//		decltype(p0.phi()) const dist_nm { radians2nm(dist_rad) };
//
//		//We obtain the initial course, tc1, (at point 1) from point 1 to point 2 by the following.The formula fails if the initial point is a pole.We can special case this with:
//		//	IF(cos(lat1) < EPS)   // EPS a small number ~ machine precision
//		//		IF(lat1 > 0)
//		//			tc1 = pi        //  starting from N pole
//		//		ELSE
//		//			tc1 = 2 * pi         //  starting from S pole
//		//		ENDIF
//		//	ENDIF
//		//		For starting points other than the poles :
//		//	IF sin(lon2 - lon1) < 0
//		//			tc1 = acos((sin(lat2) - sin(lat1) * cos(d)) / (sin(d) * cos(lat1)))
//		//	ELSE
//		//		tc1 = 2 * pi - acos((sin(lat2) - sin(lat1) * cos(d)) / (sin(d) * cos(lat1)))
//		//	ENDIF
//		decltype(p0.phi()) const sin_dist { std::sin(dist_rad) };
//		decltype(p0.phi()) const cos_dist { std::cos(dist_rad) };
//
//		decltype(p0.phi()) tc1 {};
//		constexpr decltype(p0.phi()) eps { std::numeric_limits<decltype(p0.phi())>::min() };
//		if (cos_lat0 < eps) {
//			if (rlat0 > 0) {
//				tc1 = NavigationConstantsNS::my_pi<decltype(p0.phi())>;
//			} else {
//				tc1 = 2 * NavigationConstantsNS::my_pi<decltype(p0.phi())>;
//			}
//		}
//		if (sin_londiff < 0) {
//			tc1 = std::acos((sin_lat0 - sin_lat1 * cos_dist) / (sin_dist * cos_lat0));
//		} else {
//			tc1 = {2 * NavigationConstantsNS::my_pi<decltype(p0.phi())>  - std::acos((sin_lat0 - sin_lat1 * cos_dist) / (sin_dist * cos_lat0))};
//		}
//
//		decltype(p0.phi()) const angle_deg { radians2degrees(tc1) };
//
//		Nav_vec_t<decltype(p0.phi())> ret {dist_nm, angle_deg};
//
//		return ret;
//	}
//
//	template <typename T>
//	auto grtcrcl_dist(T p0, T p1) -> Nav_vec_t<decltype(p0.phi())> {
//		//d=acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon1-lon2))
//		decltype(p0.phi()) const lat0 { p0.phi() };
//		decltype(p0.phi()) const lat1 { p1.phi() };
//		decltype(p0.phi()) const lon0 { p0.lambda() };
//		decltype(p0.phi()) const lon1 { p1.lambda() };
//		decltype(p0.phi()) const rlat0 { degress2radians(lat0) };
//		decltype(p0.phi()) const rlat1 { degress2radians(lat1) };
//		decltype(p0.phi()) const rlon0 { degress2radians(lon0) };
//		decltype(p0.phi()) const rlon1 { degress2radians(lon1) };
//
//		decltype(p0.phi()) const rlon0diff { rlon0 - rlon1 };
//		decltype(p0.phi()) const rlon1diff { rlon1 - rlon0 };
//		decltype(p0.phi()) const sin_londiff { std::sin(rlon1diff) };
//		decltype(p0.phi()) const cos_londiff { std::cos(rlon0diff) };
//		decltype(p0.phi()) const cos_lat0 { std::cos(rlat0) };
//		decltype(p0.phi()) const cos_lat1 { std::cos(rlat1) };
//		decltype(p0.phi()) const sin_lat0 { std::sin(rlat0) };
//		decltype(p0.phi()) const sin_lat1 { std::sin(rlat1) };
//		decltype(p0.phi()) const term0 { sin_lat0 * sin_lat1 };
//		decltype(p0.phi()) const term1 { cos_lat0 * cos_lat1 * cos_londiff };
//		decltype(p0.phi()) const tterm { term0 + term1 };
//		decltype(p0.phi()) const dist_rad { std::acos(tterm) };
//		decltype(p0.phi()) const dist_nm { radians2nm(dist_rad) };
//
////We obtain the initial course, tc1, (at point 1) from point 1 to point 2 by the following.The formula fails if the initial point is a pole.We can special case this with:
////	IF(cos(lat1) < EPS)   // EPS a small number ~ machine precision
////		IF(lat1 > 0)
////			tc1 = pi        //  starting from N pole
////		ELSE
////			tc1 = 2 * pi         //  starting from S pole
////		ENDIF
////	ENDIF
////		For starting points other than the poles :
////	IF sin(lon2 - lon1) < 0
////			tc1 = acos((sin(lat2) - sin(lat1) * cos(d)) / (sin(d) * cos(lat1)))
////	ELSE
////		tc1 = 2 * pi - acos((sin(lat2) - sin(lat1) * cos(d)) / (sin(d) * cos(lat1)))
////	ENDIF
//		decltype(p0.phi()) const sin_dist { std::sin(dist_rad) };
//		decltype(p0.phi()) const cos_dist { std::cos(dist_rad) };
//
//		decltype(p0.phi()) tc1 {};
//		constexpr decltype(p0.phi()) eps { std::numeric_limits<decltype(p0.phi())>::min() };
//		if (cos_lat0 < eps) {
//			if (rlat0 > 0) {
//				tc1 = NavigationConstantsNS::my_pi<decltype(p0.phi())>;
//			}
//			else {
//				tc1 = 2 * NavigationConstantsNS::my_pi<decltype(p0.phi())>;
//			}
//		} else {
//			if (sin_londiff < 0) {
//				tc1 = std::acos((sin_lat1 - sin_lat0 * cos_dist) / (sin_dist * cos_lat0));
//			} else {
//				tc1 = { 2 * NavigationConstantsNS::my_pi<decltype(p0.phi())> -std::acos((sin_lat1 - sin_lat0 * cos_dist) / (sin_dist * cos_lat0)) };
//			}
//		}
//
//		decltype(p0.phi()) const angle_deg { radians2degrees(tc1) };
//
//		Nav_vec_t<decltype(p0.phi())> ret {dist_nm, angle_deg};
//
//		return ret;
//	}
//
//
//	template <typename T>
//	auto rhmbln_dist(T p0, T p1) -> Nav_vec_t<decltype(p0.phi())> {
//		Nav_vec_t<decltype(p0.phi())> ret {};
//
//		return ret;
//	}
};

//
////   tc1=mod(atan2(sin(lon1-lon2)*cos(lat2),
////      cos(lat1)* sin(lat2) - sin(lat1) * cos(lat2) * cos(lon1 - lon2)), 2 * pi)
//decltype(p0.phi()) tc1 {};
//constexpr decltype(p0.phi()) eps { std::numeric_limits::min() };
//if (cos_lat0 < eps) {
//	if (rlat0 > 0) {
//		tc1 = NavigationConstantsNS::my_pi<decltype(p0.phi())>;
//	}
//	else {
//		tc1 = 2 * NavigationConstantsNS::my_pi<decltype(p0.phi())>;
//	}
//}
//else {
//	tc1 = { XXX(std::atan2(sin_londiff * cos_lat1, cos_lat0 * sin_lat1 - sin_lat0 * cos_londiff), 2 * NavigationConstantsNS::my_pi<decltype(p0.phi())>) };
//}