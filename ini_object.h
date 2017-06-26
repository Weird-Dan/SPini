
#ifndef INI_OBJECT_H
#define INI_OBJECT_H

#include <string>
#include <map>

struct IniObject {
  std::string filename; // file
  std::string section;
  std::map<std::string, std::string> data; //key /value
};

#endif
