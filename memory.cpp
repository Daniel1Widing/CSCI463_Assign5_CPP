//*****************************************************************************
//
//  memory.cpp
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
#include <fstream>
#include <cstring>

#include "hex.h"
#include "memory.h"

using namespace std;

/**
 * Creates a new memory object by setting the size to the passed parameter and
 * allocating a new memory buffer of that size, filled with 0xa5
 *
 * @param siz: size of memory buffer to allocate
 **/
memory::memory(uint32_t siz)
{
	//Round memory size up to multiple of 16
	siz = (siz + 15) & 0xfffffff0;

	//Sets member variable to parameter
	size = siz;

	//Allocates "size" memory to mem array
	mem = new uint8_t[size];

	//Sets every byte in memory array to 0xa5
	memset(mem, 0xa5, size);
}

/**
 * Deallocates the memory buffer of the calling memory object
 **/
memory::~memory()
{
	delete mem;
}

/**
 * Checks if passed address is found in the calling memory
 *
 * @param i: address to check if in memory
 *
 * @return false: address not in memory
 *	        true: address in memory
 **/
bool memory::check_address(uint32_t i) const
{
	//Outputs error and returns false if address outside memory
	if (i > size)
	{
		cout << "WARNING: Address out of range: " << hex0x32(i) << endl;
		return false;
	}

	//Returns true if in memory
	else
	{
		return true;
	}
}

/**
 * Getter for size
 *
 * @return: size of calling's allocated memory
 **/
uint32_t memory::get_size() const
{
	return size;
}

/**
 * Gets the value of the byte at passed address and returns it.
 * Checks if passed address exists and returns 0 instead if not.
 *
 * @param addr: the address in calling memory of the data to return
 *
 * @return    0: if address not in memory
 *		   data: returns data in memory if address in memory
 **/
uint8_t memory::get8(uint32_t addr) const
{
	if (check_address(addr))
	{
		return mem[addr];
	}

	else
	{
		return 0;
	}
}

/**
 * Calls get8() method twice to get combined 2 bytes at address
 *
 * @param addr: the address in calling memory of the data to return
 *
 * @return    0: if address not in memory
 *		   data: returns data in memory if address in memory
 **/
uint16_t memory::get16(uint32_t addr) const
{
	//Creates vars for both parts of the 2 byte value and the combined 2 byte value 
	uint16_t combined = 0x0000;
	uint8_t part1 = get8(addr);
	uint8_t part2 = get8(addr + 1);

	//Combines the bytes
	combined = part2;
	combined = combined << 8;
	combined |= part1;

	return combined;
}

/**
 * Calls get16() method twice to get combined 4 bytes at address
 *
 * @param addr: the address in calling memory of the data to return
 *
 * @return    0: if address not in memory
 *		   data: returns data in memory if address in memory
 **/
uint32_t memory::get32(uint32_t addr) const
{
	//Creates vars for both parts of the 4 byte value and the combined 4 byte value 
	uint32_t combined = 0x00000000;
	uint16_t part1 = get16(addr);
	uint16_t part2 = get16(addr + 2);

	//Combines the bytes
	combined = part2;
	combined = combined << 16;
	combined |= part1;

	return combined;
}

/**
 * Sets the value of the byte at passed address to the passed value.
 * Checks if passed address exists and does nothing if not.
 *
 * @param addr: the address in calling memory of the data to return
 * @param  val: the value to set the data in memory to
 **/
void memory::set8(uint32_t addr, uint8_t val)
{
	if (check_address(addr))
	{
		mem[addr] = val;
	}
}

/**
 * Sets the value of the byte at passed address to the passed value.
 * Checks if passed address exists and does nothing if not.
 *
 * @param addr: the address in calling memory of the data to return
 * @param  val: the value to set the data in memory to
 **/
void memory::set16(uint32_t addr, uint16_t val)
{
	//Gets the single byte parts of the 2 byte value
	uint8_t part1 = (val >> 8) & 0xff;
	uint8_t part2 = (val >> 0) & 0xff;

	//Puts the least signifigant byte on the right of the combined bytes
	set8(addr, part2);
	set8(addr + 1, part1);
}

/**
 * Sets the value of the byte at passed address to the passed value.
 * Checks if passed address exists and does nothing if not.
 *
 * @param addr: the address in calling memory of the data to return
 * @param  val: the value to set the data in memory to
 **/
void memory::set32(uint32_t addr, uint32_t val)
{
	//Gets the 2 byte parts of the 4 byte value
	uint16_t part1 = (val >> 16) & 0xffff;
	uint16_t part2 = (val >> 0) & 0xffff;

	//Puts the least signifigant byte on the right of the combined bytes
	set16(addr, part2);
	set16(addr + 2, part1);
}

/**
 * Prints all the data in memory to standard out in a hex and ASCII formatted manner.
 *
 * Format:
 *   Every 16 bytes, ASCII rep and new line and address
 *   After 8 bytes, print extra space
 *   Every byte, print get(8) of address and print space
 **/
void memory::dump() const
{
	//Char array to store ascii representation of the line
	char ascii[17];

	//Loops through memory printing all values
	for (uint32_t i = 0; i < size; i++)
	{
		//For every new line except the last, puts the line's leading address at the front
		if (i % 16 == 0 && i + 1 != size)
		{
			cout << hex32(i) << ": ";
		}

		//Puts an extra space between the sets of 8 bytes
		if ((i + 8) % 16 == 0)
		{
			cout << " ";
		}

		//Gets byte at current address
		uint8_t byte = get8(i);

		//Prints byte and space
		cout << setw(2);
		cout << setfill('0');
		cout << hex << static_cast<int>(byte) << " ";
		cout << dec;

		//Adds ASCII representation of byte to ascii char array for the line
		ascii[i % 16] = isprint(byte) ? byte : '.';

		//Every 16 bytes prints out the ASCII array and goes to a new line
		if (i % 16 == 15)
		{
			cout << "*";

			for (int j = 0; j < 16; j++)
			{
				cout << ascii[j];
			}

			cout << "*\n";
		}
	}
}

/**
 * Opens passed file in binary mode and reads contents into calling memory
 *
 * @param fname: reference to file to open and read into memory
 *
 * @return false: file could not be opened or was too large for memory
 *		    true: file opened and read without problem
 **/
bool memory::load_file(const std::string& fname)
{
	//Opens file in binary mode
	ifstream infile(fname, ios::in | ios::binary);

	//Outputs error and returns false if file could not be opened
	if (!infile.is_open())
	{
		cerr << "Can't open file \"" << fname << "\" for reading." << endl;
		return false;
	}

	int8_t readByte;

	//Tells infile to not skip whitespaces while reading
	infile >> std::noskipws;

	//Reads file byte by byte and checks each byte address before writing to ensure file does not exceed memory size
	uint32_t address = 0;
	while (infile >> readByte)
	{
		//Adds byte to memory only if byte would be within memory size
		if (address <= size)
		{
			//Ignores /r for Windows newline (Windows formatting)
			//if (readByte != 0x0d)
			//{
			//	mem[address] = readByte;
			//	address++;
			//}
		
			//(Unix formatting)
			mem[address] = readByte;
			address++;
		}

		//Outputs error and returns false if file size exceeds memory size
		else
		{
			cerr << "Program too big." << endl;
			return false;
		}
	}

	return true;
}

