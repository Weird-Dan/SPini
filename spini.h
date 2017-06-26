
#ifndef SPINI_H
#define SPINI_H


#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include "ini_object.h"


class SPini {
private:
  std::string m_Filename;

public:
    bool Init(std::string filename);

    //fe-manini
    bool GetSection(std::string section, IniObject & obj);
    bool SimpleSection(std::string section, IniObject & obj);
    bool SetSection(std::string section, IniObject & obj);

    //fe-spini
    void GetSetValueAsString(std::string section, std::string key, std::string def, std::string & output);
    void GetSetValueAsInt(std::string section, std::string key, int def, int & output);
    void GetSetValueAsLong(std::string section, std::string key, long def, long & output);
    void GetSetValueAsFloat(std::string section, std::string key, float def, float & output);
    void GetSetValueAsDouble(std::string section, std::string key, double def, double & output);
    void GetSetValueAsBool(std::string section, std::string key, bool def, bool & output);

    void SimpleAsString(std::string section, std::string key, std::string & defout);
    void SimpleAsInt(std::string section, std::string key, int & defout);
    void SimpleAsLong(std::string section, std::string key, long & defout);
    void SimpleAsFloat(std::string section, std::string key, float & defout);
    void SimpleAsDouble(std::string section, std::string key, double & defout);
    void SimpleAsBool(std::string section, std::string key, bool & defout);

    //old-mod-rwini
    bool GetValueAsString(std::string section, std::string key, std::string & result);
    bool GetValueAsInt(std::string section, std::string key, int & result);
    bool GetValueAsLong(std::string section, std::string key, long & result);
    bool GetValueAsFloat(std::string section, std::string key, float & result);
    bool GetValueAsDouble(std::string section, std::string key, double & result);
    bool GetValueAsBool(std::string section, std::string key, bool & result);

    bool SetValue(std::string setion, std::string key, std::string value);
    bool IniExists();

    bool GetSections(std::vector<std::string> &out);

    std::string GetValue(std::string section, std::string key);
    std::string GetIniFilename();

private:
    //old-mod-rwini
    size_t getFirstChar(const std::string & str);
    bool isKey(const std::string & s, const std::string & key);
    bool isSection(const std::string & s);
    bool isComment(const std::string & s);
    bool isWhitespace(const std::string & s);
    std::string value_for_key(const std::string & s, const std::string key);
    std::string trim(std::string s);
    std::string toLower(const std::string & s);

    //fe-manini
    bool isKeyValue(const std::string &s, std::string &key, std::string &value);
};

/// override << for ini_object
std::ostream &operator<<(std::ostream &os, IniObject const &m);

#endif
