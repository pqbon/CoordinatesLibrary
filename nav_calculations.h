#pragma once

#include "nav_constants.h"
#include "nav_types.h"
#include "nav_coordinates.h"


namespace CoordinatesNS {

	template <typename T>
	auto grtcrcl_dist_small(T p0, T p1) -> Nav_vec_t<decltype(p0.phi())> {
		//d = 2 * asin(sqrt((sin[(lat1 - lat2) / 2]) ^ 2 +
		//	cos(lat1) * cos(lat2) * (sin[(lon1 - lon2) / 2]) ^ 2))
		auto const lat0 { p0.phi() };
		auto const lat1 { p1.phi() };
		auto const lon0 { p0.lambda() };
		auto const lon1 { p1.lambda() };
		auto const rlat0 { degress2radians(lat0) };
		auto const rlat1 { degress2radians(lat1) };
		auto const rlon0 { degress2radians(lon0) };
		auto const rlon1 { degress2radians(lon1) };

		auto const rlatdiff { std::abs(rlat0 - rlat1) };
		auto const rlondiff { std::abs(rlon0 - rlon1) };
		auto const sin_latdiff { std::sin(rlatdiff / 2) };
		auto const sin_londiff { std::sin(rlondiff / 2) };
		auto const cos_lat0 { std::cos(rlat0) };
		auto const cos_lat1 { std::cos(rlat1) };
		auto const sin_lat0 { std::sin(rlat0) };
		auto const sin_lat1 { std::sin(rlat1) };
		auto const term0 { std::pow(sin_latdiff, 2) };
		auto const term1 { cos_lat0 * cos_lat1 * std::pow(sin_londiff, 2) };
		auto const dist_rad { 2 * std::asin(std::sqrt(term0 + term1)) };
		auto const dist_nm { radians2nm(dist_rad) };

		//We obtain the initial course, tc1, (at point 1) from point 1 to point 2 by the following.The formula fails if the initial point is a pole.We can special case this with:
		//	IF(cos(lat1) < EPS)   // EPS a small number ~ machine precision
		//		IF(lat1 > 0)
		//			tc1 = pi        //  starting from N pole
		//		ELSE
		//			tc1 = 2 * pi         //  starting from S pole
		//		ENDIF
		//	ENDIF
		//		For starting points other than the poles :
		//	IF sin(lon2 - lon1) < 0
		//			tc1 = acos((sin(lat2) - sin(lat1) * cos(d)) / (sin(d) * cos(lat1)))
		//	ELSE
		//		tc1 = 2 * pi - acos((sin(lat2) - sin(lat1) * cos(d)) / (sin(d) * cos(lat1)))
		//	ENDIF
		auto const sin_dist { std::sin(dist_rad) };
		auto const cos_dist { std::cos(dist_rad) };

		decltype(p0.phi()) tc1 {};
		constexpr decltype(p0.phi()) eps { std::numeric_limits::min() };
		if (cos_lat0 < eps) {
			if (rlat0 > 0) {
				tc1 = NavigationConstantsNS::my_pi<decltype(p0.phi())>;
			} else {
				tc1 = 2 * NavigationConstantsNS::my_pi<decltype(p0.phi())>;
			}
		}
		if (sin_londiff < 0) {
			tc1 = std::acos((sin_lat0 - sin_lat1 * cos_dist) / (sin_dist * cos_lat0));
		} else {
			tc1 = {2 * NavigationConstantsNS::my_pi<decltype(p0.phi())>  - std::acos((sin_lat0 - sin_lat1 * cos_dist) / (sin_dist * cos_lat0))};
		}

		auto const angle_deg { radians2degrees(tc1) };

		Nav_vec_t<decltype(p0.phi())> ret {dist_nm, angle_deg};

		return ret;
	}

	template <typename T>
	auto grtcrcl_dist(T p0, T p1) -> Nav_vec_t<decltype(p0.phi())> {
		//d=acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon1-lon2))
		auto const lat0 { p0.phi() };
		auto const lat1 { p1.phi() };
		auto const lon0 { p0.lambda() };
		auto const lon1 { p1.lambda() };
		auto const rlat0 { degress2radians(lat0) };
		auto const rlat1 { degress2radians(lat1) };
		auto const rlon0 { degress2radians(lon0) };
		auto const rlon1 { degress2radians(lon1) };

		auto const rlatdiff { std::abs(rlat0 - rlat1) };
		auto const rlondiff { std::abs(rlon0 - rlon1) };
		auto const cos_londiff { std::cos(rlondiff) };
		auto const sin_londiff { std::sin(rlondiff) };
		auto const cos_lat0 { std::cos(rlat0) };
		auto const cos_lat1 { std::cos(rlat1) };
		auto const sin_lat0 { std::sin(rlat0) };
		auto const sin_lat1 { std::sin(rlat1) };
		auto const term0 { sin_lat0 * sin_lat1 };
		auto const term1 { cos_lat0 * cos_lat1 * cos_londiff };
		auto const dist_rad { std::asin(term0 + term1) };
		auto const dist_nm { radians2nm(dist_rad) };
		//   tc1=mod(atan2(sin(lon1-lon2)*cos(lat2),
		//      cos(lat1)* sin(lat2) - sin(lat1) * cos(lat2) * cos(lon1 - lon2)), 2 * pi)
		decltype(p0.phi()) tc1 {};
		constexpr decltype(p0.phi()) eps { std::numeric_limits::min() };
		if (cos_lat0 < eps) {
			if (rlat0 > 0) {
				tc1 = NavigationConstantsNS::my_pi<decltype(p0.phi())>;
			}
			else {
				tc1 = 2 * NavigationConstantsNS::my_pi<decltype(p0.phi())>;
			}
		} else {
			tc1 = { XXX(std::atan2(sin_londiff * cos_lat1, cos_lat0 * sin_lat1 - sin_lat0 * cos_londiff), 2 * NavigationConstantsNS::my_pi<decltype(p0.phi())>) };
		}

		auto const angle_deg { radians2degrees(tc1) };

		Nav_vec_t<decltype(p0.phi())> ret {dist_nm, angle_deg};

		return ret;
	}


	template <typename T>
	auto rhmbln_dist(T p0, T p1) -> Nav_vec_t<decltype(p0.phi())> {
		Nav_vec_t<decltype(p0.phi())> ret {};

		return ret;
	}


};