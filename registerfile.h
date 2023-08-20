//*****************************************************************************
//
//  registerfile.h
//  CSCI 463 Assignment 5
//
//  Created by Daniel Widing (z1838064)
//
//*****************************************************************************
#ifndef registerfile_H
#define registerfile_H

#include <cstdint>
#include <string>
#include <iostream>
#include <iomanip>

#include "hex.h"

class registerfile
{
private:
	int32_t registers [32];

public:
	registerfile();
	void reset();
	void set(uint32_t r, int32_t val);
	int32_t get(uint32_t r) const;
	void dump() const;
};

#endif