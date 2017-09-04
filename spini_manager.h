
#ifndef SPINI_MANAGER_H
#define  SPINI_MANAGER_H

#include "spini.h"

class IniManager {
  
private:

  /*
    Local data-map to store loaded ini-file data.
  */
  std::map<std::string, IniObject> data;

  /*
    Local ini-parser object
  */
  SPini ini_man;

  /*
    The filename of the default ini-file to read and write to.
  */
  std::string m_Filename;

public:

  /*
    Sets the filename of the ini-file to read from.
  */
  void Init(std::string filename);

  /*
    Returns true if the ini-file exists. To determine the result the program
    tries to open the file.
  */
  bool IniExists();

  /*
    Returns the filename of the current ini-file.
  */
  std::string GetIniFilename();

  /*
    Clears the memory of all the data loaded from and to ini-files.
  */
  void Clear();

  /*
    Loads all the section data from the file of the filename parameter to the
    data map in this spini_manager object.
  */
  bool LoadIni(std::string filename);

  /*
    Loads all the section data from the file of the current filename to the
    data map in this spini_manager object.
  */
  bool LoadIni();

  /*
    Changes or creates the key=value in section for the data in the spini_manager
    and writes changes to the file of the given filename parameter.
  */
  void SetValue(std::string filename, std::string section, std::string key, std::string value);

  /*
    Changes or creates the key=value in section for the data in the spini_manager
    and writes changes to current ini-file.
  */
  void SetValue(std::string section, std::string key, std::string value);

  /*
    Searches the given file for the value of key in section. if found the value
    will be stored in the data-map in memory and returned in the res parameter
    and the function will return true, otherwise the function will return false
    and the res variable will not be modified.
  */
  bool GetValue(std::string filename, std::string section, std::string key, std::string &res);

  /*
    Searches the current ini-file for the value of key in section. if found the value
    will be stored in the data-map in memory and returned in the res parameter
    and the function will return true, otherwise the function will return false
    and the res variable will not be modified.
  */
  bool GetValue(std::string section, std::string key, std::string &res);

  /*
    Searches for the section in the data-map of this object and returns the
    ini_object with all the section data and the function will return true.
    If not found, the function will not search any file for the section, it will
    only return false. (at least for now.)
  */
  bool GetSection(std::string section, IniObject &obj);

  /*
    Searches for section in memory, if found, the section and it's data will be
    written to the file of the filename parameter, and the function will return true.
    If section was not found or the program could not write the data to file, the
    function will return false.
  */
  bool WriteSection(std::string filename, std::string section);

  /*
    Writes all sections of the argv to the file of the filename parameter.
    if all the sections where found, and the program was able to write them to
    the file, the function will return true, else it returns false.
  */
  bool WriteSection(std::string filename, int argc, std::string argv[]);

  /*
    Writes all the data in the data-map in memory to the given filename.
    If able to write to file, the functio will return true, else it returns false.
  */
  bool WriteData(std::string filename);

  /*
    Searches the parsed ini-file to find key in section, if found, the value will be
    returned as a string in the res variable. If not found, the key with the value of res
    as the value will be written to the ini-file.
  */
  void GetSetValueAsString(std::string filename, std::string section, std::string key, std::string & res);

  /*
    Searches the parsed ini-file to find key in section, if found, the value will be
    returned as an int in the res variable. If not found, the key with the value of res
    as the value will be written to the ini-file.
  */
  void GetSetValueAsInt(std::string filename, std::string section, std::string key, int & res);

  /*
    Searches the parsed ini-file to find key in section, if found, the value will be
    returned as a long in the res variable. If not found, the key with the value of res
    as the value will be written to the ini-file.
  */
  void GetSetValueAsLong(std::string filename, std::string section, std::string key, long & res);

  /*
    Searches the parsed ini-file to find key in section, if found, the value will be
    returned as a float in the res variable. If not found, the key with the value of res
    as the value will be written to the ini-file.
  */
  void GetSetValueAsFloat(std::string filename, std::string section, std::string key, float & res);

  /*
    Searches the parsed ini-file to find key in section, if found, the value will be
    returned as a double in the res variable. If not found, the key with the value of res
    as the value will be written to the ini-file.
  */
  void GetSetValueAsDouble(std::string filename, std::string section, std::string key, double & res);

  /*
    Searches the parsed ini-file to find key in section, if found, the value will be
    returned as a boolean in the res variable. If not found, the key with the value of res
    as the value will be written to the ini-file.
  */
  void GetSetValueAsBool(std::string filename, std::string section, std::string key, bool & res);

  /*
    Searches the ini-file to find key in section, if found, the value will be
    returned as a string in the res variable. If not found, the key with the value of res
    as the value will be written to the ini-file.
  */
  void GetSetValueAsString( std::string section, std::string key, std::string & res);

  /*
    Searches the ini-file to find key in section, if found, the value will be
    returned as an int in the res variable. If not found, the key with the value of res
    as the value will be written to the ini-file.
  */
  void GetSetValueAsInt(std::string section, std::string key, int & res);

  /*
    Searches the ini-file to find key in section, if found, the value will be
    returned as a long in the res variable. If not found, the key with the value of res
    as the value will be written to the ini-file.
  */
  void GetSetValueAsLong(std::string section, std::string key, long & res);

  /*
    Searches the ini-file to find key in section, if found, the value will be
    returned as a float in the res variable. If not found, the key with the value of res
    as the value will be written to the ini-file.
  */
  void GetSetValueAsFloat(std::string section, std::string key, float & res);

  /*
    Searches the ini-file to find key in section, if found, the value will be
    returned as a double in the res variable. If not found, the key with the value of res
    as the value will be written to the ini-file.
  */
  void GetSetValueAsDouble(std::string section, std::string key, double & res);

  /*
    Searches the ini-file to find key in section, if found, the value will be
    returned as a boolean in the res variable. If not found, the key with the value of res
    as the value will be written to the ini-file.
  */
  void GetSetValueAsBool(std::string section, std::string key, bool & res);

  /*
    Searches the local data-map for the key in the parsed section. if found,
    the value will be returned as a string in the res parameter, and the function
    returns true, else res will remain unchanged and the function will return false.
  */
  bool GetValueAsString(std::string section, std::string key, std::string & res);

  /*
    Searches the local data-map for the key in the parsed section. if found,
    the value will be returned as an int in the res parameter, and the function
    returns true, else res will remain unchanged and the function will return false.
  */
  bool GetValueAsInt(std::string section, std::string key, int & res);

  /*
    Searches the local data-map for the key in the parsed section. if found,
    the value will be returned as a long in the res parameter, and the function
    returns true, else res will remain unchanged and the function will return false.
  */
  bool GetValueAsLong(std::string section, std::string key, long &res);

  /*
    Searches the local data-map for the key in the parsed section. if found,
    the value will be returned as a float in the res parameter, and the function
    returns true, else res will remain unchanged and the function will return false.
  */
  bool GetValueAsFloat(std::string section, std::string key, float &res);

  /*
    Searches the local data-map for the key in the parsed section. if found,
    the value will be returned as a double in the res parameter, and the function
    returns true, else res will remain unchanged and the function will return false.
  */
  bool GetValueAsDouble(std::string section, std::string key, double &res);

  /*
    Searches the local data-map for the key in the parsed section. if found,
    the value will be returned as a boolean in the res parameter, and the function
    returns true, else res will remain unchanged and the function will return false.
  */
  bool GetValueAsBool(std::string section, std::string key, bool &res);

private:

  /*
    Returns the location of the first nonwhitespace character in string.
  */
  size_t getFirstChar(const std::string & str);

  /*
    Returns a copy of the s parameter whithout whitespace in the start and end of the string.
  */
  std::string trim(std::string s);

  /*
    Returns a copy of the s parameter with all lowercase characters.
  */
  std::string toLower(const std::string & s);
};

#endif
