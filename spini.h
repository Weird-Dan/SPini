
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

    /*
      Tests if the given filename ends with ".ini", and returns true if it does.

      If this fails the object will carry on working as usual!
    */
    bool Init(std::string filename);

    /*
      Searches the ini-file for the given section, if found, the content of the
      section will be added to the ini_object and the function will return true.
    */
    bool GetSection(std::string section, IniObject & obj);

    /*
    Searches the ini-file for the given section, if found, the content will be
    added to the ini_object and then the ini_object will be written in the section.
    if section was not found, the section will be created and the contents of the
    ini_object will be added to the file. if able to read and write to the file,
    the function will return true.
    */
    bool SimpleSection(std::string section, IniObject & obj);

    /*
      Searches the ini-file for the given section, if found, the section of the
      section of the file will be overwritten with the contents of the ini_object.
      returns true if able to write to the file.
    */
    bool SetSection(std::string section, IniObject & obj);

    /*
      Searches ini-file to find key in section, if found, the value will be
      returned as a string in the output variable. If not found, the key with the value of def
      as the value will be written to the ini-file.
    */
    void GetSetValueAsString(std::string section, std::string key, std::string def, std::string & output);

    /*
      Searches ini-file to find key in section, if found, the value will be
      returned as an int in the output variable. If not found, the key with the value of def
      as the value will be written to the ini-file.
    */
    void GetSetValueAsInt(std::string section, std::string key, int def, int & output);

    /*
      Searches ini-file to find key in section, if found, the value will be
      returned as a long in the output variable. If not found, the key with the value of def
      as the value will be written to the ini-file.
    */
    void GetSetValueAsLong(std::string section, std::string key, long def, long & output);

    /*
      Searches ini-file to find key in section, if found, the value will be
      returned as a float in the output variable. If not found, the key with the value of def
      as the value will be written to the ini-file.
    */
    void GetSetValueAsFloat(std::string section, std::string key, float def, float & output);

    /*
      Searches ini-file to find key in section, if found, the value will be
      returned as a double in the output variable. If not found, the key with the value of def
      as the value will be written to the ini-file.
    */
    void GetSetValueAsDouble(std::string section, std::string key, double def, double & output);

    /*
      Searches ini-file to find key in section, if found, the value will be
      returned as a boolean in the output variable. If not found, the key with the value of def
      as the value will be written to the ini-file.
    */
    void GetSetValueAsBool(std::string section, std::string key, bool def, bool & output);

    /*
      Searches ini-file to find key in section, if found, the value will be
      returned in the defout variable. If not found, the key with the value of defout
      as the value will be written to the ini-file.
    */
    void SimpleAsString(std::string section, std::string key, std::string & defout);

    /*
      Searches ini-file to find key in section, if found, the value will be
      returned as an int in the defout variable. If not found, the key with the value of defout
      as the value will be written to the ini-file.
    */
    void SimpleAsInt(std::string section, std::string key, int & defout);

    /*
      Searches ini-file to find key in section, if found, the value will be
      returned as a long in the defout variable. If not found, the key with the value of defout
      as the value will be written to the ini-file.
    */
    void SimpleAsLong(std::string section, std::string key, long & defout);

    /*
      Searches ini-file to find key in section, if found, the value will be
      returned as a float in the defout variable. If not found, the key with the value of defout
      as the value will be written to the ini-file.
    */
    void SimpleAsFloat(std::string section, std::string key, float & defout);

    /*
      Searches ini-file to find key in section, if found, the value will be
      returned as a double in the defout variable. If not found, the key with the value of defout
      as the value will be written to the ini-file.
    */
    void SimpleAsDouble(std::string section, std::string key, double & defout);

    /*
      Searches ini-file to find key in section, if found, the value will be
      returned as a boolean in the defout variable. If not found, the key with the value of defout
      as the value will be written to the ini-file.
    */
    void SimpleAsBool(std::string section, std::string key, bool & defout);

    /*
      Searches ini-file for the value of the key in the section. If found the
      result variable will be set to the value of the key and the function will
      return true, else it returns false.
    */
    bool GetValueAsString(std::string section, std::string key, std::string & result);

    /*
      Searches ini-file for the value of the key in the section. If found the
      result variable will be set to the value of the key and the function will
      return true, else it returns false.
    */
    bool GetValueAsInt(std::string section, std::string key, int & result);

    /*
      Searches ini-file for the value of the key in the section. If found the
      result variable will be set to the value of the key and the function will
      return true, else it returns false.
    */
    bool GetValueAsLong(std::string section, std::string key, long & result);

    /*
      Searches ini-file for the value of the key in the section. If found the
      result variable will be set to the value of the key and the function will
      return true, else it returns false.
    */
    bool GetValueAsFloat(std::string section, std::string key, float & result);

    /*
      Searches ini-file for the value of the key in the section. If found the
      result variable will be set to the value of the key and the function will
      return true, else it returns false.
    */
    bool GetValueAsDouble(std::string section, std::string key, double & result);

    /*
      Searches ini-file for the value of the key in the section. If found the
      result variable will be set to the value of the key and the function will
      return true, else it returns false.
    */
    bool GetValueAsBool(std::string section, std::string key, bool & result);

    /*
      Opens the ini-file and tries to replace the key/value in the given section,
      section is not found, it will be created and if the key is not found, it will be created.
      Returns true if able to write changes to the file.
    */
    bool SetValue(std::string setion, std::string key, std::string value);

    /*
      Test if the ini-file of the SPini object is an existing file of the system,
      if so, returns true.

      The test is preformed by trying to open the file.
    */
    bool IniExists();

    /*
      Searches the ini-file for sections, if secations are found the
      out vector of strings is set to the section names and returns true.
    */
    bool GetSections(std::vector<std::string> &out);

    /*
      Searches the ini-file for the given key in the given section and returns it's value if found
      else it returns an empty string.
    */
    std::string GetValue(std::string section, std::string key);

    /*
      returns the string of the filename variable in the SPini object.
    */
    std::string GetIniFilename();

private:

    /*
      returns the location of the first character that is not some sort of whitespace.
    */
    size_t getFirstChar(const std::string & str);

    /*
      returns true if the string is of the structure "key=nonwhitespace" and
      the given key is in the string.
    */
    bool isKey(const std::string & s, const std::string & key);

    /*
      returns true if the string is of structure "[sectionname]"
      but only if it starts with either whitespace then structure or directly
      starts with the structure
    */
    bool isSection(const std::string & s);

    /*
      returns true if the strings first non shitespace character is either '#' or ';'
    */
    bool isComment(const std::string & s);

    /*
      returns true if the srting only contains whitespace.
    */
    bool isWhitespace(const std::string & s);

    /*
      returns the value part of "key=value" of the given string if the string starts with "key=",
      if the string does not contain "key=" it returns an ampty string.
    */
    std::string value_for_key(const std::string & s, const std::string key);

    /*
      removes all whitespace from the start and end of the string , the returns it.
    */
    std::string trim(std::string s);

    /*
      returns the given string in lowercase characters.
    */
    std::string toLower(const std::string & s);

    /*
      returns true if string s is a 'key'='value' formatted string
      if so key is set to the key of the string and value is set to the value of the string.
    */
    bool isKeyValue(const std::string &s, std::string &key, std::string &value);
};

/// override << for ini_object
/*
  overrides the << operator of ini_object to enable printing the properties of
  the object to a stream.
*/
std::ostream &operator<<(std::ostream &os, IniObject const &m);

#endif
