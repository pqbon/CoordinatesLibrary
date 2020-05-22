// coordinates_classes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "nav_coordinates.h"
#include "nav_vectors.h"
#include "nav_types.h"
#include "nav_calculations.h"


using namespace CoordinatesNS;
using namespace CoordinatesNS::NavCalculations;
using namespace CoordinatesNS::Double;

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

template <typename T0, typename T1>
void nav_info_dump(T0 const& P0, T1 const& P1, std::string_view&& name0, std::string_view&& name1);

int main()
{
    std::cout << "Test code for navigation code"sv << std::endl;

    CoordinatesDegrees test0DF { 40.7030526_ND, 74.0157877_WD }; //New York Battery Part
    CoordinatesDegrees copytest0DF(test0DF);
    CoordinatesDegreesMinutes copytest0DMF(test0DF);
    //CoordinatesDegreesMinutes copytest0DMF;
    //convert(copytest0DMF, test0DF);
    CoordinatesDegreesMinutesSeconds copytest0DMSF(test0DF);
    //CoordinatesDegreesMinutesSeconds copytest0DMSF;
    //convert(copytest0DMSF, test0DF);

    CoordinatesDegreesMinutes test1DMF { DegreesMinutes {51.0f, 30.11666666666666666666666666f}, DegreesMinutes {0.0f, 5.366666666666666f} }; //London Gallons Hill 51.5014684 0.0912972
    CoordinatesDegrees copytest1DF(test1DMF);
    //CoordinatesNS::CoordinatesDegrees copytest1DF;
    //convert(copytest1DF, test1DMF);
    CoordinatesDegreesMinutes copytest1DMF(test1DMF);
    CoordinatesDegreesMinutesSeconds copytest1DMSF(test1DMF);
    //CoordinatesNS::CoordinatesDegreesMinutesSeconds copytest1DMSF;
    //convert(copytest1DMSF, test1DMF);

    CoordinatesDegreesMinutesSeconds test2DMSF { DegreesMinutesSeconds {52.0f, 12.0f, 17.0f}, DegreesMinutesSeconds {0.0f, 7.0f, 2.0f} }; //Cambridge Kings College Catherderal front lawn
    CoordinatesDegrees copytest2DF { test2DMSF };
    //CoordinatesNS::CoordinatesDegrees copytest2DF;
    //convert(copytest2DF, test2DMSF);
    CoordinatesDegreesMinutes copytest2DMF { test2DMSF };
    //CoordinatesNS::CoordinatesDegreesMinutes copytest2DMF;
    //convert(copytest2DMF, test2DMSF);
    CoordinatesDegreesMinutesSeconds copytest2DMSF(test2DMSF);

    CartesianVector const testCartVec0 { 10, 10 };
    CartesianVector const testCartVec1 { 20, 20 };
    CartesianVector const testCartVecA { testCartVec0 + testCartVec1 };

    NavigationVector const testNavVec0 { 20, 45 };
    NavigationVector const testNavVec1 { 30, 45 };

    NavigationVector const testNavVecA { testNavVec0 + testNavVec1 };

    NavigationVector const testNavVec0A { 20, 45 };
    NavigationVector const testNavVec1A { 30, 180 + 45 };

    NavigationVector const testNavVecAA { testNavVec0A + testNavVec1A };

    NavigationVector const testNavVec0B { 30, 0 };
    NavigationVector const testNavVec1B { 30, 180 };

    NavigationVector const testNavVecAB { testNavVec0B + testNavVec1B };

    NavigationVector const testNavVec0C { 20, 90 };
    NavigationVector const testNavVec1C { 30, 270 };

    NavigationVector const testNavVecAC { testNavVec0C + testNavVec1C };

    NavigationVector const testNavVec0D { 30, 90 + 45 };
    NavigationVector const testNavVec1D { 30, 180 + 45 };

    NavigationVector const testNavVecAD { testNavVec0D + testNavVec1D };

    std::cout << "test0DF "sv << test0DF << " "sv << copytest0DF << " "sv << copytest0DMF << " "sv << copytest0DMSF << " Phi "sv << test0DF.phi() << " Lambda "sv << test0DF.lambda() << std::endl;
    std::cout << "test1DMF "sv << test1DMF << " "sv << copytest1DF << " "sv << copytest1DMF << " "sv << copytest1DMSF << " Phi "sv << test1DMF.phi() << " Lambda "sv << test1DMF.lambda() << std::endl;
    std::cout << "test2DMSF "sv << test2DMSF << " "sv << copytest2DF << " "sv << copytest2DMF << " "sv << copytest2DMSF << " Phi "sv << test2DMSF.phi() << " Lambda "sv << test2DMSF.lambda() << std::endl;
    std::cout << "testCartVec0 "sv << testCartVec0 << " + testCartVec1 "sv << testCartVec1 << " = testCartVecA "sv << testCartVecA << std::endl;
    std::cout << "testNavVec0 "sv << testNavVec0 << " + testNavVec1 "sv << testNavVec1 << " = testNavVecA "sv << testNavVecA << std::endl;
    std::cout << "testNavVec0A "sv << testNavVec0A << " + testNavVec1A "sv << testNavVec1A << " = testNavVecAA "sv << testNavVecAA << std::endl;
    std::cout << "testNavVec0B "sv << testNavVec0B << " + testNavVec1B "sv << testNavVec1B << " = testNavVecAB "sv << testNavVecAB << std::endl;
    std::cout << "testNavVec0C "sv << testNavVec0C << " + testNavVec1C "sv << testNavVec1C << " = testNavVecAC "sv << testNavVecAC << std::endl;
    std::cout << "testNavVec0D "sv << testNavVec0D << " + testNavVec1D "sv << testNavVec1D << " = testNavVecAD "sv << testNavVecAD << std::endl;

    std::cout << "Maths test..." << std::endl << std::endl << std::endl;
    CoordinatesDegreesMinutes LAX { DegreesMinutes {33.0f, 57.0f}, DegreesMinutes {-118.0f, 24.0f} };
    CoordinatesDegreesMinutes JFK { DegreesMinutes {40.0f, 38.0f}, DegreesMinutes {-73.0f, 47.0f} };
    CoordinatesDegrees SFO { Degrees {37.615223f}, Degrees {-122.389977f} };
    CoordinatesDegreesMinutesSeconds LHR { DegreesMinutesSeconds {51.0f, 28.0f, 12.0720f}, DegreesMinutesSeconds {-0.0f, 27.0f, 15.4620f} };
    CoordinatesDegreesMinutesSeconds PCG { DegreesMinutesSeconds {49.0f, 0.0f, 35.0064f}, DegreesMinutesSeconds {2.0f, 32.0f, 52.0008f} };
    CoordinatesDegrees SPBH { Degrees {-36.788433f}, Degrees {174.688766f} };
    CoordinatesDegrees JSIA { Degrees {-26.1372399f}, Degrees {28.1975f} };

    nav_info_dump(LAX, JFK, "LAX"sv, "JFK"sv);
    std::cout << std::endl;
    nav_info_dump(JFK, LAX, "JFK"sv, "LAX"sv);
    std::cout << std::endl;
    nav_info_dump(SFO, LHR, "SFO"sv, "LHR"sv);
    std::cout << std::endl;
    nav_info_dump(LHR, SFO, "LHR"sv, "SFO"sv);
    std::cout << std::endl;
    nav_info_dump(LAX, PCG, "LAX"sv, "PCG"sv);
    std::cout << std::endl;
    nav_info_dump(PCG, LAX, "PCG"sv, "LAX"sv);
    std::cout << std::endl;
    nav_info_dump(LHR, SPBH, "LHR"sv, "SPBH"sv);
    std::cout << std::endl;
    nav_info_dump(SPBH, LHR, "SPBH"sv, "LHR"sv);
    std::cout << std::endl;
    nav_info_dump(LAX, JSIA, "LAX"sv, "JSIA"sv);
    std::cout << std::endl;
    nav_info_dump(JSIA, LAX, "JSIA"sv, "LAX"sv);
}

template <typename T0, typename T1>
void nav_info_dump(T0 const& P0, T1 const& P1, std::string_view&& name0, std::string_view&& name1) {
    auto great_circle_sm { grtcrcl_dist_small_nm(P0, P1) };
    auto great_circle { grtcrcl_dist_nm(P0, P1) };
    auto great_circle_haversine { grtcrcl_dist_haversine_nm(P0, P1) };
    auto great_circle_bearing { grtcrcl_init_brng(P0, P1) };
    CoordinatesDegreesMinutesSeconds great_circle_midpoint { grtcrcl_midpoint(P0, P1) };
    CoordinatesDegreesMinutesSeconds great_circle_frac { grtcrcl_frac_point(P0, P1, 0.50, great_circle) };
    NavigationVector CP0_P1 { great_circle, great_circle_bearing };
    CoordinatesDegreesMinutesSeconds calc_P1 { grtcrcl_start_vec(P0, CP0_P1) };
    auto rect_linear { rectl_dist_nm(P0, P1) };
    auto rhumb_line { rhumb_dist_nm(P0, P1) };
    auto rhumb_brg { rhumb_brng(P0, P1) };
    CoordinatesDegreesMinutesSeconds rhumb_mp { rhumb_midpoint(P0, P1) };
    NavigationVector RP0_P1 { rhumb_line, rhumb_brg };
    CoordinatesDegreesMinutesSeconds rhumb_calc_P1 { rhumb_start_vec(P0, RP0_P1) };
    CoordinatesDegreesMinutesSeconds FP0 { P0 };
    CoordinatesDegreesMinutesSeconds FP1 { P1 };

    std::cout << name0 << " ("sv << P0 << ") "sv << name1 << " ("sv << P1 << ")"sv << std::endl;
    std::cout << "Great Circle "sv << great_circle << "nm  Small Great Circle "sv << great_circle_sm << "nm Great Circle Haversine "sv << great_circle_haversine << "nm"sv << std::endl;
    std::cout << "Inital bearing "sv << great_circle_bearing << " Midpoint "sv << great_circle_midpoint << " Midpoint(frac 50 %) "sv << great_circle_frac << std::endl;
    std::cout << "Calc "sv << name1 << " ("sv << calc_P1 << ")"sv << std::endl;
    std::cout << "Rectolinear "sv << rect_linear << "nm Rhumb line "sv << rhumb_line << "nm Rhumb bearing "sv << rhumb_brg << " Rhumb midpoint "sv << rhumb_mp << std::endl;
    std::cout << "Rhumb "sv << name1 << " "sv << rhumb_calc_P1 << std::endl;

    // Validation dump...
    //std::cout << name1 << " ("sv << P1 << ") -- "sv << FP1 << std::endl;
    //std::cout << "GC Calc\t"sv << calc_P1 << std::endl;
    //std::cout << "RL Cacl\t"sv << rhumb_calc_P1 << std::endl << std::endl;
    //std::cout << "Midpoint GC\t\t"sv << great_circle_midpoint << std::endl;
    //std::cout << "Midpoint GC (50%)\t"sv << great_circle_frac << std::endl;
    //std::cout << "Midpoint RL\t\t"sv << rhumb_mp << std::endl << std::endl;
}