//*****************************************************************************
//
//  main.cpp
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
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "getopt.h"
#include "hex.h"
#include "memory.h"
#include "rv32i.h"
#include "registerfile.h"

using namespace std;

/**
* Print a usage message and abort the program.
*********************************************************************/
static void usage()
{
	cerr << "Usage: [-d] [-i] [-l execution-limit] [-m hex-mem-size] [-r] [-z] infile" << endl;
	cerr << "    -d show disassembly before program simulation" << endl;
	cerr << "    -i show instruction printing during execution" << endl;
	cerr << "    -l execution-limit" << endl;
	cerr << "    -m specify memory size (default = 0x10000)" << endl;
	cerr << "    -r show dump of hart status before each instruction" << endl;
	cerr << "    -z show dump of hart status and memory after simulation has halted" << endl;
	exit(1);
}

/**
* Read a file of RV32I instructions and execute them.
********************************************************************/
int main(int argc, char** argv)
{
	bool show_disassembly = false;
	bool show_instruction_printing = false; 
	uint64_t instruction_limit = 0;
	bool instruction_limit_set = false;
	uint32_t memory_limit = 0x10000;		         //default memory size = 64k
	bool repeat_hart_dump = false;
	bool end_hart_memory_dump = false;

	int opt;

	while ((opt = getopt(argc, argv, "dil:m:rz")) != -1)
	{
		switch (opt)
		{
		case 'd':
			show_disassembly = true;
			break;
		case 'i':
			show_instruction_printing = true;
			break;
		case 'l':
			instruction_limit = std::stoul(optarg, nullptr, 10);
			instruction_limit_set = true;
			break;
		case 'm':
			memory_limit = std::stoul(optarg, nullptr, 16);
			break;
		case 'r':
			repeat_hart_dump = true;
			break;
		case 'z':
			end_hart_memory_dump = true;
			break;
		default: // '?'
			usage();
		}
	}

	if (optind >= argc)
		usage();	// missing filename

	memory mem(memory_limit);

	if (!mem.load_file(argv[optind]))
		usage();

	//allinsns5 test file
	//memory mem(0x100);
	//mem.load_file("allinsns5.bin");
	//show_disassembly = true;
	//show_instruction_printing = true;
	//repeat_hart_dump = true;

	//torture5 test file
	//memory mem(0x8500);
	//mem.load_file("torture5.bin");
	//show_disassembly = true;
	//show_instruction_printing = true;
	//repeat_hart_dump = true;
	//end_hart_memory_dump = true;

	//sieve test file
	//memory mem(0x8000000);
	//mem.load_file("sieve.bin");
	//end_hart_memory_dump = true;

	//Creates rv32i object
	rv32i sim(&mem);
	
	//Conditional show disassembly before simulation start
	if (show_disassembly)
	{
		sim.disasm();
		sim.reset();
	}

	//Conditional show instructions while simulating
	if (show_instruction_printing)
	{
		sim.set_show_instructions(true);
	}

	//Conditional dump hart while simulating
	if (repeat_hart_dump)
	{
		sim.set_show_registers(true);
	}

	//Conditional instruction limit
	if (instruction_limit_set)
	{
		sim.set_has_insn_limit(true);
	}

	//Runs simulation
	sim.run(instruction_limit);

	//Conditional dump hart after simulation
	if (end_hart_memory_dump)
	{
		sim.dump();
		mem.dump();
	}
	
	return 0;
}
