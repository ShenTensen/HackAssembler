#ifndef HACKASSEMBLER_PARSER_H_
#define HACKASSEMBLER_PARSER_H_

#include <fstream>
#include <string>
#include <vector>

enum class Type {
  A_INSTRUCTION = 0,
  C_INSTRUCTION = 1,
  L_INSTRUCTION = 2
};

class Parser {
 public:
  Parser(std::ifstream&);
  bool hasMoreLines();
  void advance();
  Type instructionType();
  std::string symbol();
  std::string dest();
  std::string comp();
  std::string jump();
  std::string ins();  // test
  void reset();
 private:
  std::vector<std::string> instructions;
  std::vector<std::string>::iterator present;
};

#endif  // HACKASSEMBLER_PARSER_H_
