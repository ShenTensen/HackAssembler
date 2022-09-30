#include "symboltable.h"

#include <iostream>

void SymbolTable::addEntry(std::string symbol, int address)
{
  symbol_table_.insert({symbol, address});
}

bool SymbolTable::contains(std::string symbol)
{
  auto iter = symbol_table_.find(symbol);
  if (iter != symbol_table_.end()) {
    return true;
  } else {
    return false;
  }
}

// Ensures contains then uses getAddress
int SymbolTable::getAddress(std::string symbol)
{
  auto iter = symbol_table_.find(symbol);
  return iter->second;
}

void SymbolTable::test()
{
  auto map_it = symbol_table_.cbegin();
  while (map_it != symbol_table_.cend()) {
    std::cout << map_it->first << " "
	      << map_it->second << std::endl;
    ++map_it;
  }
}
