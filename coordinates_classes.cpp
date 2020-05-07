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

    auto great_circle { grtcrcl_dist(LAX, JFK) };
    auto great_circle2 { grtcrcl_dist_small(LAX, JFK) };

    std::cout << "LAX ("s << LAX << ") JFK ("s << JFK << ") Great Circle "s << great_circle << std::endl;
    std::cout << "LAX ("s << LAX << ") JFK ("s << JFK << ") Great Circle "s << great_circle2 << std::endl;
}


//Worked Examples :
//
//Suppose point 1 is LAX : (33deg 57min N, 118deg 24min W)
//Suppose point 2 is JFK : (40deg 38min N, 73deg 47min W)
//
//In radians LAX is
//lat1 = (33 + 57 / 60) * pi / 180 = 0.592539, lon1 = (118 + 24 / 60) * pi / 180 = 2.066470
//
//and JFK is
//(lat2 = 0.709186, lon2 = 1.287762)
//
//The distance from LAX to JFK is
//d = 2 * asin(sqrt((sin((lat1 - lat2) / 2)) ^ 2 +
//    cos(lat1) * cos(lat2) * (sin((lon1 - lon2) / 2)) ^ 2))
//    = 2 * asin(sqrt((sin((0.592539 - 0.709186) / 2)) ^ 2 +
//        cos(0.592539) * cos(0.709186) * (sin((2.066470 - 1.287762) / 2)) ^ 2))
//    = 2 * asin(sqrt((-0.05829) ^ 2 + 0.829525 * 0.758893 * 0.379591 ^ 2))
//    = 2 * asin(0.306765)
//    = 0.623585 radians
//    = 0.623585 * 180 * 60 / pi = 2144nm
//    or
//
//    d = acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon1 - lon2))
//    = acos(sin(0.592539) * sin(0.709186) +
//        cos(0.592539) * cos(0.709186) * cos(0.778708))
//    = acos(0.811790)
//    = 0.623585 radians
//    = 0.623585 * 180 * 60 / pi = 2144nm
//
//    The initial true course out of LAX is :
//sin(-0.778708) = -0.702 < 0 so
//
//    tc1 = acos((sin(lat2) - sin(lat1) * cos(d)) / (sin(d) * cos(lat1)))
//    = acos((sin(0.709186) - sin(0.592539) * cos(0.623585)) /
//        (sin(0.623585) * cos(0.592535))
//        = acos(0.408455)
//        = 1.150035 radians
//        = 66 degrees
//
//        An enroute waypoint 100nm from LAX on the 66 degree radial(100nm along the GC to JFK) has lat and long given by :
//
//
//100nm = 100 * pi / (180 * 60) = 0.0290888radians
//lat = asin(sin(lat1) * cos(d) + cos(lat1) * sin(d) * cos(tc))
//= asin(sin(0.592539) * cos(0.0290888)
//    + cos(0.592539) * sin(0.0290888) * cos(1.150035))
//    = asin(0.568087)
//    = 0.604180radians
//    = 34degrees 37min N
//
//    lon = mod(lon1 - asin(sin(tc) * sin(d) / cos(lat)) + pi, 2 * pi) - pi
//    = mod(2.066470 - asin(sin(1.150035) * sin(0.0290888) / cos(0.604180)) + pi, 2 * pi) - pi
//    = mod(2.034206 + pi, 2 * pi) - pi radians
//    = 2.034206 radians
//    = 116 degrees 33min W
//
//
//    The great circle route from LAX to JFK crosses the 111degree W meridian at a latitude of :
//(111degrees = 1.937315 radians)
//
//lat = atan((sin(lat1) * cos(lat2) * sin(lon - lon2)
//    - sin(lat2) * cos(lat1) * sin(lon - lon1)) / (cos(lat1) * cos(lat2) * sin(lon1 - lon2)))
//    = atan((sin(0.592539) * cos(0.709186) * sin(0.649553)
//        - sin(0.709186) * cos(0.592539) * sin(-0.129154)) / (cos(0.592539) * cos(0.709186)
//            * sin(0.778708)))
//    = atan(0.737110)
//    = 0.635200radians
//    = 36 degrees 24min
//
//    Cross track error
//
//    Suppose enroute from LAX to JFK you find yourself at(D) N34:30 W116 : 30, which in radians is(0.6021386, 2.033309) (See earlier for LAX, JFK coordinatesand course)
//
//    From LAX to D the distance is :
//dist_AD = acos(sin(0.592539) * sin(0.6021386) +
//    cos(0.592539) * cos(0.6021386) * cos(2.066470 - 2.033309))
//    = 0.02905 radians(99.8665 nm)
//
//    From LAX to D the course is :
//
//
//crs_AD = acos((sin(0.6021386) - sin(0.592539) * cos(0.02905)) /
//    (sin(0.02905) * cos(0.592539)))
//    = 1.22473 radians(70.17 degrees)
//
//    At point D the cross track error is :
//
//
//xtd = asin(sin(0.02905) * sin(1.22473 - 1.15003))
//= 0.00216747 radians
//= 0.00216747 * 180 * 60 / pi = 7.4512 nm right of course
//
//atd = acos(cos(0.02905) / cos(0.00216747))
//= 0.0289691 radians
//= 0.0289691 * 180 * 60 / pi = 99.588 nm along course
//
//The point 40 % of the way from LAX to JFK is found by :
//
//d = 2 * asin(sqrt((sin((lat1 - lat2) / 2)) ^ 2 +
//    cos(lat1) * cos(lat2) * (sin((lon1 - lon2) / 2)) ^ 2))
//    = 2 * asin(sqrt((-0.05829) ^ 2 + 0.829525 * 0.758893 * 0.379591 ^ 2))
//    = 2 * asin(0.306765)
//    = 0.623585 radians(as above)
//    f = 0.4    (40 %)
//    A = sin((1 - f) * d) / sin(d)
//    = sin(0.6 * 0.623585) / sin(0.623585)
//    = 0.62588
//    B = sin(f * d) / sin(d)
//    = sin(0.4 * 0.623585) / sin(0.623585)
//    = 0.422735
//    x = A * cos(lat1) * cos(lon1) + B * cos(lat2) * cos(lon2)
//    = -0.157344
//    y = A * cos(lat1) * sin(lon1) + B * cos(lat2) * sin(lon2)
//    = 0.764745
//    z = A * sin(lat1) + B * sin(lat2)
//    = 0.624826
//    lat = atan2(z, sqrt(x ^ 2 + y ^ 2))
//    = 0.674909 radians
//    = 38 deg 40.167' N
//    lon = atan2(y, x)
//    = 1.77371 radians
//    = 101 degrees 37.570 W
//
//    Example of an intersection calc(briefly) :
//
//    Let point 1 be REO(42.600N, 117.866W) = (0.74351, 2.05715)rad
//    Let point 2 be BKE(44.840N, 117.806W) = (0.782606, 2.056103)rad
//
//    The 51 degree(= 0.890118rad) bearing from REO intersects with 137 degree(= 2.391101rad) from BKE at(lat3, lon3) :
//
//    Then :
//
//    dst12 = 0.039103
//    crs12 = 0.018996
//    crs21 = 3.161312
//    ang1 = 0.871122
//    ang2 = 0.770211
//    ang3 = 1.500667
//    dst13 = 0.027290
//    (dst23 = 0.029986)
//    lat3 = 0.760473 = 43.572N
//    lon3 = 2.027876 = 116.189W  at BOI!
//
