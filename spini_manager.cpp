#include "spini_manager.h"

void IniManager::Init(std::string filename) {
    m_Filename = filename;
}

bool IniManager::IniExists() {
    std::ifstream f(m_Filename);
    if (!f) return false;
    f.close();
    return true;
}

std::string IniManager::GetIniFilename() {
    return m_Filename;
}

void IniManager::Clear() {
    this->data.clear();
}

bool IniManager::LoadIni(std::string filename) {
    std::vector<std::string> sections;
    ini_man.Init(filename);
    if (!ini_man.GetSections(sections)) {
        return false;
    } else {
        for (int i = 0; i < sections.size(); i++) {
            auto search = data.find(sections[i]);
            if (search != data.end()) {
                ini_man.GetSection(sections[i], search->second);
            } else {
                IniObject obj;
                ini_man.GetSection(sections[i], obj);
                data[sections[i]] = obj;
            }
        }
        return true;
    }
}

bool IniManager::LoadIni() {
  std::vector<std::string> sections;
  ini_man.Init(m_Filename);
  if (!ini_man.GetSections(sections)) {
    return false;
  } else {
    for (int i = 0; i < sections.size(); i++) {
      auto search = data.find(sections[i]);
      if (search != data.end()) {
          ini_man.GetSection(sections[i], search->second);
      } else {
          IniObject obj;
          ini_man.GetSection(sections[i], obj);
          data[sections[i]] = obj;
      }
    }
    return true;
  }
}

void IniManager::SetValue(std::string filename, std::string section, std::string key, std::string value) {
    auto search = data.find(section);
    if (search != data.end()) { // if section found in data:
        search->second.data[key] = value; // the value of key in memory is set to value param
        ini_man.Init(filename);
        ini_man.SetValue(section, key, value); // write new value to file
    } else {
        ini_man.Init(filename);
        IniObject obj;
        obj.filename = filename;
        obj.section = section;
        obj.data[key] = value;// add value to obj
        ini_man.SetValue(section, key, value);
        this->data[section] = obj;
        /*if (ini_man.SimpleSection(section, obj)) { // this would load the value of key in file if found, before setting to the value param
            this->data[section] = obj;
        }*/
    }

}

void IniManager::SetValue(std::string section, std::string key, std::string value) {
    // find section in data, then
    auto search = data.find(section);
    if (search != data.end()) {
        search->second.data[key] = value;
        ini_man.Init(m_Filename);
        ini_man.SetValue(section, key, value);
    } else {
        ini_man.Init(m_Filename);
        IniObject obj;
        obj.filename = filename;
        obj.section = section;
        obj.data[key] = value;// add value to obj
        this->data[section] = obj;
        /*if (ini_man.SimpleSection(section, obj)) { // this would load the value of key in file if found, before setting to the value param
            this->data[section] = obj;
        }*/
    }
}

bool IniManager::GetValue(std::string filename ,std::string section, std::string key, std::string &res) {
    ini_man.Init(filename);
    std::string value; // value to be returned
    bool success = ini_man.GetValueAsString(section, key, value); // tries to read value from file
    if (success) {
        auto search = data.find(section);
        if (search != data.end()) {
            search->second.data[key] = value;
        } else {
            IniObject obj;
            obj.filename = filename;
            obj.section = section;
            obj.data[key] = value;
            // add to data
            data[section] = obj;
        }
    }
    // is not success , shall it try to find it in the data variable?
    res = value;// return value in result
    return success;

}

bool IniManager::GetValue(std::string section, std::string key, std::string &res) {
    if (this->data.size() > 0) {
        auto search = data.find(section);
        if (search != data.end()) {
            auto keysearch = search->second.data.find(key);
            if (keysearch != search->second.data.end()) {
                res = keysearch->second;
                return true;
            }
        }
    }

    return false;

}

bool IniManager::GetSection(std::string section, IniObject &obj) {
  // should it search the ini-file for the section if not found?
    auto search = data.find(section);
    if (search != data.end()) {
        obj = search->second;
        return true;
    } else {
        return false;
    }
}

bool IniManager::WriteSection(std::string filename, std::string section) {
    auto search = data.find(section);
    if(search != data.end()) {// if the section exists in memory
        ini_man.Init(filename);
        if (ini_man.SetSection(section, search->second)) return true; // write section to file
    }
    return false;
}

bool IniManager::WriteSection(std::string filename, int argc, std::string *argv) {
    bool res = true;
    for (int i = 0; i < argc; i++) {
        if (!WriteSection(filename, argv[i])) res = false;
    }
    return res;
}

bool IniManager::WriteData(std::string filename) {
    bool res = true;
    for (auto ent : data) {
        if (!WriteSection(filename, ent.first)) res = false;
    }
    return res;
}

void IniManager::GetSetValueAsString(std::string filename, std::string section, std::string key, std::string &res) {
    std::string value;
    bool got = GetValue(filename, section, key, value);
    if (!got) {
        SetValue(filename, section, key, res);
    } else {
        res = value;
    }
}

void IniManager::GetSetValueAsInt(std::string filename, std::string section, std::string key, int &res) {
    std::string value;
    bool got = GetValue(filename, section, key, value);
    if (!got) {
        SetValue(filename, section, key, std::to_string(res));
    } else {
        res = std::stoi(value);
    }
}

void IniManager::GetSetValueAsLong(std::string filename, std::string section, std::string key, long &res) {
    std::string value;
    bool got = GetValue(filename, section, key, value);
    if (!got) {
        SetValue(filename, section, key, std::to_string(res));
    } else {
        res = std::stol(value);
    }
}

void IniManager::GetSetValueAsFloat(std::string filename, std::string section, std::string key, float &res) {
    std::string value;
    bool got = GetValue(filename, section, key, value);
    if (!got) {
        SetValue(filename, section, key, std::to_string(res));
    } else {
        res = std::stof(value);
    }
}

void IniManager::GetSetValueAsDouble(std::string filename, std::string section, std::string key, double &res) {
    std::string value;
    bool got = GetValue(filename, section, key, value);
    if (!got) {
        SetValue(filename, section, key, std::to_string(res));
    } else {
        res = std::stod(value);
    }
}

void IniManager::GetSetValueAsBool(std::string filename, std::string section, std::string key, bool &res) {
    std::string value;
    bool got = GetValue(filename, section, key, value);
    if (!got) {
        if (res) {
            SetValue(filename, section, key, "true");
        } else {
            SetValue(filename, section, key, "false");
        }
    } else {
        size_t first = getFirstChar(value);
        if (trim(toLower(value.substr(first, first+4))) == std::string("true")) {
            res = true;
        } else if (trim(toLower(value.substr(first, first+5))) == std::string("false")) {
            res = false;
        }

    }
}

void IniManager::GetSetValueAsString(std::string section, std::string key, std::string &res) {
    std::string value;
    bool got = GetValue(m_Filename, section, key, value);
    if (!got) {
        SetValue(m_Filename, section, key, res);
    } else {
        res = value;
    }
}

void IniManager::GetSetValueAsInt(std::string section, std::string key, int &res) {
    std::string value;
    bool got = GetValue(m_Filename, section, key, value);
    if (!got) {
        SetValue(m_Filename, section, key, std::to_string(res));
    } else {
        res = std::stoi(value);
    }
}

void IniManager::GetSetValueAsLong(std::string section, std::string key, long &res) {
    std::string value;
    bool got = GetValue(m_Filename, section, key, value);
    if (!got) {
        SetValue(m_Filename, section, key, std::to_string(res));
    } else {
        res = std::stol(value);
    }
}

void IniManager::GetSetValueAsFloat(std::string section, std::string key, float &res) {
    std::string value;
    bool got = GetValue(m_Filename, section, key, value);
    if (!got) {
        SetValue(m_Filename, section, key, std::to_string(res));
    } else {
        res = std::stof(value);
    }
}

void IniManager::GetSetValueAsDouble(std::string section, std::string key, double &res) {
    std::string value;
    bool got = GetValue(m_Filename, section, key, value);
    if (!got) {
        SetValue(m_Filename, section, key, std::to_string(res));
    } else {
        res = std::stod(value);
    }
}

void IniManager::GetSetValueAsBool(std::string section, std::string key, bool &res) {
    std::string value;
    bool got = GetValue(m_Filename, section, key, value);
    if (!got) {
        if (res) {
            SetValue(m_Filename, section, key, "true");
        } else {
            SetValue(m_Filename, section, key, "false");
        }
    } else {
        size_t first = getFirstChar(value);
        if (trim(toLower(value.substr(first, first+4))) == std::string("true")) {
            res = true;
        } else if (trim(toLower(value.substr(first, first+5))) == std::string("false")) {
            res = false;
        }

    }
}

bool IniManager::GetValueAsString(std::string section, std::string key, std::string &res) {
    auto secsearch = data.find(section);
    if (secsearch != data.end()) {
        auto search = secsearch->second.data.find(key);
        if (search != secsearch->second.data.end()) {
            res = search->second;
            return true;
        }
    }
    return false;
}

bool IniManager::GetValueAsInt(std::string section, std::string key, int &res) {
    auto secsearch = data.find(section);
    if (secsearch != data.end()) {
        auto search = secsearch->second.data.find(key);
        if (search != secsearch->second.data.end()) {
            res = std::stoi(search->second);
            return true;
        }
    }
    return false;
}

bool IniManager::GetValueAsLong(std::string section, std::string key, long &res) {
    auto secsearch = data.find(section);
    if (secsearch != data.end()) {
        auto search = secsearch->second.data.find(key);
        if (search != secsearch->second.data.end()) {
            res = std::stol(search->second);
            return true;
        }
    }
    return false;
}

bool IniManager::GetValueAsFloat(std::string section, std::string key, float &res) {
    auto secsearch = data.find(section);
    if (secsearch != data.end()) {
        auto search = secsearch->second.data.find(key);
        if (search != secsearch->second.data.end()) {
            res = std::stof(search->second);
            return true;
        }
    }
    return false;
}

bool IniManager::GetValueAsDouble(std::string section, std::string key, double &res) {
    auto secsearch = data.find(section);
    if (secsearch != data.end()) {
        auto search = secsearch->second.data.find(key);
        if (search != secsearch->second.data.end()) {
            res = std::stod(search->second);
            return true;
        }
    }
    return false;
}

bool IniManager::GetValueAsBool(std::string section, std::string key, bool &res) {
    auto secsearch = data.find(section);
    if (secsearch != data.end()) {
        auto search = secsearch->second.data.find(key);
        if (search != secsearch->second.data.end()) {
            std::string value = search->second;
            size_t first = getFirstChar(value);
            if (trim(toLower(value.substr(first, first+4))) == std::string("true")) {
                res = true;
                return true;
            } else if (trim(toLower(value.substr(first, first+5))) == std::string("false")) {
                res = false;
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////
// private metods
////////////////////////////////////////////////////////////////////////

std::string IniManager::trim(std::string s) {
    size_t l = s.length();
    if (l == 0) { // string s has size of 0
        return s;
    }
    size_t b = s.find_first_not_of(" \t\r\n\0");
    if (b == std::string::npos) {
        b = 0;
    }
    size_t e = s.find_last_not_of(" \t\r\n\0");
    if (e == std::string::npos) {
        return s.substr(b);
    }
    return s.substr(b, e-b+1);
}

std::string IniManager::toLower(const std::string & s) {
    std::string str = s;
    for (std::string::iterator i = str.begin(); i != str.end(); i++) {
        if (tolower(*i) != (int)*i) *i = (char)tolower(*i);
    }
    return str;
}

size_t IniManager::getFirstChar(const std::string & str) {
    return str.find_first_not_of(' ');
}
