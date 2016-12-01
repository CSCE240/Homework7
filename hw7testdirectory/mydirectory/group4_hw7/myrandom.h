/****************************************************************
 * Header file for the random number generator.
 * This is declaring the functions used for the RNG. The .cc file
 * should be considered for black box testing purposes; not much
 * of this class should be modified in the future.
 *
 * Author/copyright:  Duncan Buell
 * Used with permission and modified by: Group 4
 *                                       Erik Akeyson
 *                                       Matthew Clapp
 *                                       Harrison Goodman
 *                                       Andy Michels
 *                                       Steve Smero
 * Date: 1 December 2016
 *
**/

#ifndef MYRANDOM_H
#define MYRANDOM_H

#include <iostream>
#include <random>
#include <cassert>
using namespace std;

#include "../Utilities/scanner.h"
#include "../Utilities/scanline.h"

#undef NDEBUG

class MyRandom {
public:
 MyRandom();
 MyRandom(unsigned seed);
 virtual ~MyRandom();

 int RandomExponentialInt(double mean);
 double RandomNormal(double mean, double dev);
 double RandomUniformDouble(double lower, double upper);
 int RandomUniformInt(int lower, int upper);

private:
 unsigned int seed_;

 std::mt19937 generator_;
};

#endif
