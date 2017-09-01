
#ifndef INI_OBJECT_H
#define INI_OBJECT_H

#include <string>
#include <map>

/*
  This structure is use to store the data of a ini-file when loaded into memory.
*/
struct IniObject {

  /*
    Name of the latest ini-file imported to the data of this object.
  */
  std::string filename;

  /*
    Name of the section this object stores.
  */
  std::string section;

  /*
    The all the "key=value" data is stored in "data".
  */
  std::map<std::string, std::string> data;
};

#endif
