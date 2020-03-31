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
    CoordinatesNS::CoordinatesDMF copytest1DMF(test1DMF);
    //CoordinatesNS::CoordinatesDMSF copytest1DMSF(test1DMF);

    CoordinatesNS::CoordinatesDMSF test2DMSF { DMS_tF {10.0f, 10.0f, 10.666f}, DMS_tF {10.0f, 10.0f, 10.666f} };
    //CoordinatesNS::CoordinatesDF copytest2DF { test2DMSF };
    //CoordinatesNS::CoordinatesDMF copytest2DMF { test2DMSF };
    CoordinatesNS::CoordinatesDMSF copytest02MSF(test2DMSF);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
