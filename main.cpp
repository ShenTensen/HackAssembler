// Hack Assembler
// Nand2Tetris Project06
// 2022.09
// g++ -std=c++11 -o HackAssembler main.cpp parser.cpp code.cpp symboltable.cpp

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include "parser.h"
#include "code.h"
#include "symboltable.h"

using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::istringstream;
using std::ostringstream;

int main(int argc, char *argv[])
{
  if (argc < 2) {
    cerr << "no filename" << endl;
    return -1;
  }

  string ifilename = argv[1];
  string::size_type pos = 0;
  if ((pos = ifilename.find(".asm", ifilename.size()-4)) == string::npos) {
    cerr << "assembly file must ends .asm!" << endl;
    return -2;
  }
  
  ifstream in(ifilename);
  string ofilename(ifilename);
  ofstream out(ofilename.replace(pos, 4, ".hack"));
  string assemble;

  Parser parser(in);
  Code code;
  SymbolTable table;
  string binary;
  int line = 0;

  while (parser.hasMoreLines()) {
    auto type = parser.instructionType();
    if (type  == Type::L_INSTRUCTION) {
      string symbol = parser.symbol();
      if (!table.contains(symbol)) {
	table.addEntry(symbol, line);
      }
    } else {
      line++;
    }
    parser.advance();
  }
  // table.test();

  parser.reset();
  int address = 16;
  while (parser.hasMoreLines()) {
    // cout << "ins    :" << parser.ins() << ":" << endl;
    auto type = parser.instructionType();
    if (type  == Type::C_INSTRUCTION) {
      /*
      cout << "dest   " << parser.dest() << endl;
      cout << "       " << code.dest(parser.dest()) << endl;
      cout << "comp   " << parser.comp() << endl;
      cout << "       " << code.comp(parser.comp()) << endl;
      cout << "jump   " << parser.jump() << endl;
      cout << "       " << code.jump(parser.jump()) << endl;
      */
      binary = "111" + code.comp(parser.comp()) +
	code.dest(parser.dest()) + code.jump(parser.jump());
    } else if (type == Type::A_INSTRUCTION) {
      string symbol = parser.symbol();
      // cout << "symbol " << parser.symbol() << endl;
      if (isalpha(symbol[0])) {
	binary = "0";
	if (table.contains(symbol)) {
	  binary += std::bitset<15>(table.getAddress(symbol)).to_string();
        } else {
	  table.addEntry(symbol, address);
	  binary += std::bitset<15>(address).to_string();
	  ++address;
	}
      } else {
        binary = "0" +
	  std::bitset<15>(std::stoull(parser.symbol())).to_string();
      }
    } else {
      binary = "";
    }
    
    if (!binary.empty()) { 
      // cout << "binary " << binary << endl;
      out << binary << endl;
    }
    parser.advance();
  }
  return 0;
}
