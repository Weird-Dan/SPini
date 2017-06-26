
#ifndef SPINI_MANAGER_H
#define  SPINI_MANAGER_H

#include "spini.h"

class IniManager {
private:
  std::map<std::string, IniObject> data; // (section, object)
  SPini ini_man;
  std::string m_Filename;

public:
  void Init(std::string filename);

  bool IniExists();
  std::string GetIniFilename();
  void Clear();

  bool LoadIni(std::string filename);

  void SetValue(std::string filename, std::string section, std::string key, std::string value);
  void SetValue(std::string section, std::string key, std::string value);

  bool GetValue(std::string filename, std::string section, std::string key, std::string &res);
  bool GetValue(std::string section, std::string key, std::string &res);
  
  bool GetSection(std::string section, IniObject &obj);

  bool WriteSection(std::string filename, std::string section);
  bool WriteSection(std::string filename, int argc, std::string argv[]);
  bool WriteData(std::string filename);

  // using seperate filename
  void GetSetValueAsString(std::string filename, std::string section, std::string key, std::string & res);
  void GetSetValueAsInt(std::string filename, std::string section, std::string key, int & res);
  void GetSetValueAsLong(std::string filename, std::string section, std::string key, long & res);
  void GetSetValueAsFloat(std::string filename, std::string section, std::string key, float & res);
  void GetSetValueAsDouble(std::string filename, std::string section, std::string key, double & res);
  void GetSetValueAsBool(std::string filename, std::string section, std::string key, bool & res);

  void GetSetValueAsString( std::string section, std::string key, std::string & res);
  void GetSetValueAsInt(std::string section, std::string key, int & res);
  void GetSetValueAsLong(std::string section, std::string key, long & res);
  void GetSetValueAsFloat(std::string section, std::string key, float & res);
  void GetSetValueAsDouble(std::string section, std::string key, double & res);
  void GetSetValueAsBool(std::string section, std::string key, bool & res);

  bool GetValueAsString(std::string section, std::string key, std::string & res);
  bool GetValueAsInt(std::string section, std::string key, int & res);
  bool GetValueAsLong(std::string section, std::string key, long &res);
  bool GetValueAsFloat(std::string section, std::string key, float &res);
  bool GetValueAsDouble(std::string section, std::string key, double &res);
  bool GetValueAsBool(std::string section, std::string key, bool &res);

private:
  size_t getFirstChar(const std::string & str);
  std::string trim(std::string s);
  std::string toLower(const std::string & s);
};

#endif
