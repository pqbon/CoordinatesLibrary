// coordinates_classes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "nav_coordinates.h"
#include "nav_vectors.h"
#include "nav_types.h"
#include "nav_calculations.h"


using namespace CoordinatesNS;
using namespace std::literals::string_literals;

int main()
{
    std::cout << "Hello World!\n";

    CoordinatesNS::CoordinatesDF test0DF { 40.7030526_ND, 74.0157877_WD }; //New York Battery Part
    CoordinatesNS::CoordinatesDF copytest0DF(test0DF);
    //CoordinatesNS::CoordinatesDMF copytest0DMF(test0DF);
    CoordinatesNS::CoordinatesDMF copytest0DMF;
    convert(copytest0DMF, test0DF);
    //CoordinatesNS::CoordinatesDMSF copytest0DMSF(test0DF);
    CoordinatesNS::CoordinatesDMSF copytest0DMSF;
    convert(copytest0DMSF, test0DF);

    CoordinatesNS::CoordinatesDMF test1DMF { DM_tF {51.0f, 30.11666666666666666666666666f}, DM_tF {0.0f, 5.366666666666666f} }; //London Gallons Hill 51.5014684 0.0912972
    //CoordinatesNS::CoordinatesDF copytest1DF(test1DMF);
    CoordinatesNS::CoordinatesDF copytest1DF;
    convert(copytest1DF, test1DMF);
    CoordinatesNS::CoordinatesDMF copytest1DMF(test1DMF);
    //CoordinatesNS::CoordinatesDMSF copytest1DMSF(test1DMF);
    CoordinatesNS::CoordinatesDMSF copytest1DMSF;
    convert(copytest1DMSF, test1DMF);

    CoordinatesNS::CoordinatesDMSF test2DMSF { DMS_tF {52.0f, 12.0f, 17.0f}, DMS_tF {0.0f, 7.0f, 2.0f} }; //Cambridge Kings College Catherderal front lawn
    //CoordinatesNS::CoordinatesDF copytest2DF { test2DMSF };
    CoordinatesNS::CoordinatesDF copytest2DF;
    convert(copytest2DF, test2DMSF);
    //CoordinatesNS::CoordinatesDMF copytest2DMF { test2DMSF };
    CoordinatesNS::CoordinatesDMF copytest2DMF;
    convert(copytest2DMF, test2DMSF);
    CoordinatesNS::CoordinatesDMSF copytest2DMSF(test2DMSF);

    CoordinatesNS::Cart_vec_tF testCartVec0 { 10, 10 };
    CoordinatesNS::Cart_vec_tF testCartVec1 { 20, 20 };
    CoordinatesNS::Cart_vec_tF testCartVecA { testCartVec0 + testCartVec1 };


    CoordinatesNS::Nav_vec_tF testNavVec0 { 20, 45 };
    CoordinatesNS::Nav_vec_tF testNavVec1 { 30, 45 };

    CoordinatesNS::Nav_vec_tF testNavVecA { testNavVec0 + testNavVec1 };

    std::cout << "test0DF "s << test0DF << " "s << copytest0DF << " "s << copytest0DMF << " "s << copytest0DMSF << " Phi "s << test0DF.phi() << " Lambda "s << test0DF.lambda() << std::endl;
    std::cout << "test1DMF "s << test1DMF << " "s << copytest1DF << " "s << copytest1DMF << " "s << copytest1DMSF << " Phi "s << test1DMF.phi() << " Lambda "s << test1DMF.lambda() << std::endl;
    std::cout << "test2DMSF "s << test2DMSF << " "s << copytest2DF << " "s << copytest2DMF << " "s << copytest2DMSF << " Phi "s << test2DMSF.phi() << " Lambda "s << test2DMSF.lambda() << std::endl;
    std::cout << "testCartVec0 "s << testCartVec0 << " + testCartVec1 "s << testCartVec1 << " = testCartVecA "s << testCartVecA << std::endl;
    std::cout << "testNavVec0 "s << testNavVec0 << " + testNavVec1 "s << testNavVec1 << " = testNavVecA "s << testNavVecA << std::endl;

    std::cout << "Maths test..." << std::endl;
    CoordinatesNS::CoordinatesDMF LAX { DM_tF {33.0f, 57.0f},  DM_tF {-118.0f, 24.0f} };
    CoordinatesNS::CoordinatesDMF JFK { DM_tF {40.0f, 38.0f}, DM_tF {-73.0f, 47.0f} };

    auto great_circle_sm { grtcrcl_dist_small_nm(LAX, JFK) };
    auto great_circle { grtcrcl_dist_nm(LAX, JFK) };
    auto great_circle_haversine { grtcrcl_dist_haversine_nm(LAX, JFK) };
    auto great_circle_bearing { grtcrcl_init_brng(LAX, JFK) };
    auto great_circle_midpoint { grtcrcl_midpoint(LAX, JFK) };
    auto great_circle_frac { grtcrcl_frac_point(LAX, JFK, 0.50, great_circle) };
    Nav_vec_tF LAX_JFK { great_circle, great_circle_bearing };
    auto calc_jfk { grtcrcl_start_vec(LAX, LAX_JFK) };
    auto rect_linear { rectl_dist_nm(LAX, JFK) };
    auto rhumb_line { rhumb_dist_nm(LAX, JFK) };

    std::cout << "LAX ("s << LAX << ") JFK ("s << JFK << ") Great Circle "s << great_circle << "nm  Small Great Circle "s << great_circle_sm << "nm Great Circle Haversine "s << great_circle_haversine << "nm Inital bearing " << great_circle_bearing << " Midpoint " << great_circle_midpoint << " Midpoint (frac 50%) " << great_circle_frac << " Calc JFK (" << calc_jfk << ")" << std::endl;
    std::cout << "Rectolinear "s << rect_linear << "nm Rhumb line "s << rhumb_line << "nm"s << std::endl;
}
