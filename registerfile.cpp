//*****************************************************************************
//
//  registerfile.cpp
//  CSCI 463 Assignment 5
//
//  Created by Daniel Widing (z1838064)
//
//*****************************************************************************
#include "registerfile.h"

using namespace std;

/**
 * Calls the reset method to set all registers
 **/
registerfile::registerfile()
{
	reset();
}

/**
 * Initializes register 0 to 0, and all others to 0xf0f0f0f0
 **/
void registerfile::reset()
{
	registers[0] = 0x00000000;

	//Sets all other registers
	for (int i = 1; i < 32; i++)
	{
		registers[i] = 0xf0f0f0f0;
	}
}

/**
 * Assigns given register to given value, unless register 0
 * 
 * @param   r: number of register to assign to
 * @param val: value to assign to register
 **/
void registerfile::set(uint32_t r, int32_t val)
{
	if (r != 0)
	{
		registers[r] = val;
	}
}

/**
 * Returns value of given register, unless register 0 which returns 0
 *
 * @param r: number of register to return value of
 * 
 * @return: value of register, or 0 if r is 0
 **/
int32_t registerfile::get(uint32_t r) const
{
	if (r == 0)
	{
		return 0x00000000;
	}

	else
	{
		return registers[r];
	}
}

/**
 * Outputs a dump of all registers to standard out
 **/
void registerfile::dump() const
{
	int regCount = 0;
	
	//Creates string of dump to print to stdout
	for (int i = 0; i < 32; i++)
	{
		//Leading register counter every 8 registers
		if (regCount == 0 || regCount == 8 || regCount == 16 || regCount == 24)
		{
			cout << setw(3) << setfill(' ') << right << "x" + to_string(regCount);
		}

		//Register value
		cout << " " + hex32(get(i));

		regCount++;

		//Newline for every 8 registers
		if (regCount == 8 || regCount == 16 || regCount == 24 || regCount == 32)
		{
			cout << endl;
		}
	}
}