//*****************************************************************************
//
//  hex.cpp
//  CSCI 463 Assignment 5
//
//  Created by Daniel Widing (z1838064)
//
//*****************************************************************************
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>

#include "hex.h"

using namespace std;

/**
 * Returns 2 hex digits of 8 bit input
 * 
 * @param i: 8 bits to be strung as hex
 * 
 * @return: string of 2 hex digits
 **/
string hex8(uint8_t i)
{
	ostringstream os;
	os << hex << setfill('0') << setw(2) << static_cast<uint16_t>(i); 
	return os.str();
}

/**
 * Returns 8 hex digits of 32 bit input
 *
 * @param i: 32 bits to be strung as hex
 *
 * @return: string of 8 hex digits
 **/
string hex32(uint32_t i)
{
	ostringstream os;
	os << hex << setfill('0') << setw(8) << static_cast<uint32_t>(i);
	return os.str();
}

/**
 * Returns 8 hex digits of 32 bit input with leading 0x
 * Calls hex32 function for conversion of 32 bit input
 * 
 * @param i: 32 bits to be strung as hex
 *
 * @return: string of 0x and 8 hex digits
 **/
string hex0x32(uint32_t i)
{
	return string("0x") + hex32(i);
}
