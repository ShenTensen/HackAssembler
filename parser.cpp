#include "parser.h"

#include <iostream>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;

Parser::Parser(ifstream &is)
{
  string assemble;
  while (std::getline(is, assemble)) {
    // windows line
    assemble.erase(remove(assemble.begin(), assemble.end(), '\r'),
		   assemble.end());
    // TODO: needs improve
    if (assemble.rfind("//", 2) != string::npos) {
      continue;
    }
    if (assemble.empty()) {
      continue;
    }
    assemble = assemble.substr(assemble.find_first_of("@(ADM0"));
    assemble = assemble.substr(0, assemble.find_first_of(" "));
    instructions.push_back(assemble);
  }

  present = instructions.begin();
  /*
  for (auto instruction: instructions) {
    cout << ":" << instruction << ":" << endl;
  }
  cout << "  ******  " << endl;
  */
}

bool Parser::hasMoreLines()
{
  return (present != instructions.end());
}
 
void Parser::advance()
{
  present++;
}
 
Type Parser::instructionType()
{
  if (present->rfind("(", 1) != string::npos)
    return Type::L_INSTRUCTION;
  else if (present->rfind("@", 1) != string::npos)
    return Type::A_INSTRUCTION;
  else
    return Type::C_INSTRUCTION;
}
 
string Parser::symbol()
{
  auto type = instructionType();
  if (type == Type::L_INSTRUCTION)
    return present->substr(1, present->size()-2);
  else if (type == Type::A_INSTRUCTION)
    return present->substr(1);
  else
    return string();
}
 
string Parser::dest()
{
  auto pos = 0;
  if ((pos = present->find("=")) != string::npos) {
    return present->substr(0, pos);
  } else
    return string("null");
}
 
string Parser::comp()
{
  string::size_type pos_equal = 0, pos_comma = 0;
  pos_equal = present->find("=");
  pos_comma = present->find(";");
  if (pos_equal == string::npos) {
    pos_equal = 0;
  } else {
    pos_equal++;
  }
  return present->substr(pos_equal, pos_comma - pos_equal);
}
 
string Parser::jump()
{
  string::size_type pos;
  if ((pos = present->find(";")) != string::npos)
    return present->substr(pos+1);
  else	
    return string("null");
}

string Parser::ins()
{
  return *present;
}

void Parser::reset()
{
  present = instructions.begin();
}
