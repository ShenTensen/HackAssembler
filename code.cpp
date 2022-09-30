#include "code.h"

using std::string;

string Code::dest(string symbolic)
{
  auto iter = dest_jump_.find(symbolic);
  if (iter != dest_jump_.end()) {
    return iter->second;
  } else {
    return string();
  }
}

string Code::comp(string symbolic)
{
  auto iter = comp_.find(symbolic);
  if (iter != comp_.end()) {
    return iter->second;
  } else {
    return string();
  }
}

string Code::jump(string symbolic)
{
  auto iter = dest_jump_.find(symbolic);
  if (iter != dest_jump_.end()) {
    return iter->second;
  } else {
    return string();
  }
}
