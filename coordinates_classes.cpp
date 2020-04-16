// coordinates_classes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "coordinates.h"


using namespace CoordinatesNS;

int main()
{
    std::cout << "Hello World!\n";

    CoordinatesNS::CoordinatesDF test0DF { 10.6666_D, 10.666_D };
    CoordinatesNS::CoordinatesDF copytest0DF(test0DF);
    //CoordinatesNS::CoordinatesDMF copytest0DMF(test0DF);
    CoordinatesNS::CoordinatesDMF copytest0DMF;
    convert(copytest0DMF, test0DF);
    //CoordinatesNS::CoordinatesDMSF copytest0DMSF(test0DF);
    CoordinatesNS::CoordinatesDMSF copytest0DMSF;
    convert(copytest0DMSF, test0DF);

    CoordinatesNS::CoordinatesDMF test1DMF { DM_tF {10.0f, 10.666f}, DM_tF {10.0f, 10.666f} };
    //CoordinatesNS::CoordinatesDF copytest1DF(test1DMF);
    CoordinatesNS::CoordinatesDF copytest1DF;
    convert(copytest1DF, test1DMF);
    CoordinatesNS::CoordinatesDMF copytest1DMF(test1DMF);
    //CoordinatesNS::CoordinatesDMSF copytest1DMSF(test1DMF);
    CoordinatesNS::CoordinatesDMSF copytest1DMSF;
    convert(copytest1DMSF, test1DMF);

    CoordinatesNS::CoordinatesDMSF test2DMSF { DMS_tF {10.0f, 10.0f, 10.666f}, DMS_tF {10.0f, 10.0f, 10.666f} };
    //CoordinatesNS::CoordinatesDF copytest2DF { test2DMSF };
    CoordinatesNS::CoordinatesDF copytest2DF;
    convert(copytest2DF, test2DMSF);
    //CoordinatesNS::CoordinatesDMF copytest2DMF { test2DMSF };
    CoordinatesNS::CoordinatesDMF copytest2DMF;
    convert(copytest2DMF, test2DMSF);
    CoordinatesNS::CoordinatesDMSF copytest02MSF(test2DMSF);

    CoordinatesNS::Cart_vec_tF testCartVec0 { 10, 10 };
    CoordinatesNS::Cart_vec_tF testCartVec1 { 20, 20 };
    CoordinatesNS::Cart_vec_tF testCartVecA { testCartVec0 + testCartVec1 };


    CoordinatesNS::Nav_vec_tF testNavVec0 { 20, 45 };
    CoordinatesNS::Nav_vec_tF testNavVec1 { 30, 45 };

    CoordinatesNS::Nav_vec_tF testNavVecA { testNavVec0 + testNavVec1 }; //Bugbug

    std::cout << "test0DF " << test0DF << std::endl;
    std::cout << "test1DMF " << test1DMF << std::endl;
    std::cout << "test2DMSF " << test2DMSF << std::endl;
    std::cout << "testCartVec0 " << testCartVec0 << " + testCartVec1 " << testCartVec1 << " = testCartVecA " << testCartVecA << std::endl;
    std::cout << "testNavVec0 " << testNavVec0 << " + testNavVec1 " << testNavVec1 << " = testNavVecA " << testNavVecA << std::endl;
}
