//*****************************************************************************
//
//  hex.h
//  CSCI 463 Assignment 5
//
//  Created by Daniel Widing (z1838064)
//
//*****************************************************************************
#ifndef hex_H
#define hex_H

#include <string>
#include <stdint.h>

std::string hex8(uint8_t i);
std::string hex32(uint32_t i);
std::string hex0x32(uint32_t i);

#endif