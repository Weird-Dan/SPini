#include "spini.h"

std::ostream &operator<<(std::ostream &os, IniObject const &m) {
    os << "_Section: " << m.section << std::endl;
    for (const auto &ent : m.data) {
        os << " |" << ent.first << "=" << ent.second << std::endl;
    }
    return os;
}

bool SPini::Init(std::string filename) {
    m_Filename = filename;
    std::string ini = std::string(".ini");
    if (filename.length() >= ini.length()) {
        return (0 == filename.compare(filename.length() - ini.length(), filename.length(), ini));
    }
    return false;
}

bool SPini::GetSection(std::string section, IniObject &obj) {
    std::string ls, sec = std::string("[") + toLower(section) + std::string("]");
    if (IniExists()) {
        std::ifstream file(m_Filename.c_str());
        bool right_section = false;
        bool changes = false;
        while (std::getline(file, ls)) {
            if (isComment(ls) | isWhitespace(ls)) continue;
            if (right_section) {
                if (isSection(ls)) {
                    right_section = false;
                }
                else {
                    // is key/value, add to map
                    std::string key, value;
                    if (isKeyValue(ls, key, value)) {
                        obj.data[key] = value;
                        changes = true;
                    }
                }
            } else {
                if (trim(toLower(ls)).compare(sec) == 0) {
                    right_section = true;
                    continue;
                }
            }
        }
        if (changes) {
            obj.section = section;
            obj.filename = m_Filename;
            return true;
        }
    }
    return false;
}

bool SPini::SimpleSection(std::string section, IniObject &obj) {
    std::string ls, sec = std::string("[") + toLower(section) + std::string("]"), key, value;
    std::vector<std::string> buffer, spacebuffer;
    bool changes = false;
    if (IniExists()) {
        std::ifstream file(m_Filename.c_str());
        if (!file) return false;
        bool right_section = false;
        while (std::getline(file, ls)) {
            if (isWhitespace(ls)) {
                spacebuffer.push_back(ls);
            } else {
                if (isComment(ls)) {
                } else if (right_section) {
                    if (isSection(ls)) {
                        if(!changes) {
                            if (obj.data.size() > 0) {
                                for (auto ent : obj.data) {
                                    std::string line = ent.first +"="+ ent.second;
                                    buffer.push_back(line);
                                }
                                changes = true;
                            }
                        }
                        if (spacebuffer.size() > 0) { // empty spacebuffer
                            for (int i = 0; i < spacebuffer.size(); ++i) {
                                buffer.push_back(spacebuffer[i]);
                            }
                            spacebuffer.clear();
                        }
                        right_section = false;
                    } else {
                        if (isKeyValue(ls, key, value)) {
                            obj.data[key] = value;
                        }
                    }
                } else {
                    if (trim(toLower(ls)) == sec) {
                        right_section = true;
                    } if (spacebuffer.size() > 0) {
                        for (int i = 0; i < spacebuffer.size(); ++i) {
                            buffer.push_back(spacebuffer[i]);
                        }
                        spacebuffer.clear();
                    }
                    buffer.push_back(ls);
                }
            }
        }
        file.close();
    }
    if (!changes) {
        if (obj.data.size() > 0) {
            buffer.push_back(sec);
            for (auto ent : obj.data) {
                std::string line = ent.first +"="+ ent.second;
                buffer.push_back(line);
            }
        }
        changes = true;
    }
    std::ofstream wfile(m_Filename);
    if (!wfile) return false;

    for (size_t i =0;  i < buffer.size(); i++) {
        wfile << buffer.at(i) << '\n';
    }    wfile.close();
    obj.section = section;
    obj.filename = m_Filename;
    return true;
}

bool SPini::SetSection(std::string section, IniObject &obj) {
    if (obj.data.size() < 1){
        return false;
    }
    std::string ls, sec = std::string("[") + toLower(section) + std::string("]"), key, value;
    std::vector<std::string> spacebuffer;
    std::queue<std::string> buffer;
    bool kv_written = false;
    bool sec_found = false;
    if (IniExists()) {
        std::ifstream file(m_Filename.c_str());
        bool right_section = false;
        while (std::getline(file, ls)) {
            if (isWhitespace(ls) | isComment(ls)) {
                spacebuffer.push_back(ls);
            } else if (right_section) {
                if (isSection(ls)) {
                    if (spacebuffer.size() > 0) { // empty spacebuffer to buffer
                        for (int i = 0; i < spacebuffer.size(); ++i) {
                            buffer.push(spacebuffer[i]);
                        }
                        spacebuffer.clear();
                    }
                    if (!trim(toLower(ls)).compare(sec) == 0) {
                        for (auto ent : obj.data) { // write key/values to buffer
                            std::string line = ent.first +"="+ ent.second;
                            buffer.push(line);
                        }
                        kv_written = true;
                        buffer.push(ls);
                        right_section = false;
                    } else {
                        buffer.push("#"+ls);
                    }
                    // write to section
                } else {// gather information
                    if (isKeyValue(ls, key, value)) {
                        auto ks = obj.data.find(key);
                        if (ks == obj.data.end()) {
                            obj.data[key] = value;
                        }
                    } else {}
                }
            } else {
                if (isSection(ls)) {
                    if (spacebuffer.size() > 0) { // empty spacebuffer to buffer
                        for (int i = 0; i < spacebuffer.size(); ++i) {
                            buffer.push(spacebuffer[i]);
                        }
                        spacebuffer.clear();
                    }
                    if(trim(toLower(ls)).compare(sec) == 0) {
                        right_section = true;
                        sec_found = true;
                    }
                    buffer.push(ls);
                } else {
                    buffer.push(ls);
                }
            }
        }
        file.close();
    }
    if (spacebuffer.size() > 0) { // empty whitespace to buffer
        for (int i = 0; i < spacebuffer.size(); ++i) {
            buffer.push(spacebuffer[i]);
        }
        spacebuffer.clear();
    }
    if (!kv_written) {
        if (!sec_found) {
            buffer.push(sec);
        }
        for (auto ent : obj.data) { // write key/values to buffer
            std::string line = ent.first +"="+ ent.second;
            buffer.push(line);
        }
        std::cout << std::endl;
    }
    std::ofstream wfile(m_Filename);
    if (!wfile) return false;

    while (!buffer.empty()) {
        wfile << buffer.front() << '\n';
        buffer.pop();
    }
    wfile.close();
    obj.section = section;
    obj.filename = m_Filename;
    return true;
}

void SPini::GetSetValueAsString(std::string section, std::string key, std::string def, std::string &output) {
    if (!GetValueAsString(section, key, output)) {
        SetValue(section, key, def);
        output = def;
    }
}

void SPini::GetSetValueAsInt(std::string section, std::string key, int def, int &output) {
    if (!GetValueAsInt(section, key, output)) {
        SetValue(section, key, std::to_string(def));
        output = def;
    }
}

void SPini::GetSetValueAsLong(std::string section, std::string key, long def, long &output) {
    if (!GetValueAsLong(section, key, output)) {
        SetValue(section, key, std::to_string(def));
        output = def;
    }
}

void SPini::GetSetValueAsFloat(std::string section, std::string key, float def, float &output) {
    if (!GetValueAsFloat(section, key, output)) {
        SetValue(section, key, std::to_string(def));
        output = def;
    }
}

void SPini::GetSetValueAsDouble(std::string section, std::string key, double def, double &output) {
    if (!GetValueAsDouble(section, key, output)) {
        SetValue(section, key, std::to_string(def));
        output = def;
    }
}

void SPini::GetSetValueAsBool(std::string section, std::string key, bool def, bool &output) {
    if (!GetValueAsBool(section, key, output)) {
        if (def) {
            SetValue(section, key, "true");
        } else {
            SetValue(section, key, "false");
        }
        output = def;
    }
}

void SPini::SimpleAsString(std::string section, std::string key, std::string &defout) {
    std::string def = defout;
    if(!GetValueAsString(section, key, defout)) {
        SetValue(section, key, def);
        defout = def;
    }
}

void SPini::SimpleAsInt(std::string section, std::string key, int &defout) {
    int def = defout;
    if (!GetValueAsInt(section, key, defout)) {
        SetValue(section, key, std::to_string(def));
        defout = def;
    }
}

void SPini::SimpleAsLong(std::string section, std::string key, long &defout) {
    long def = defout;
    if (!GetValueAsLong(section, key, defout)) {
        SetValue(section, key, std::to_string(def));
        defout = def;
    }
}

void SPini::SimpleAsFloat(std::string section, std::string key, float &defout) {
    float def = defout;
    if (!GetValueAsFloat(section, key, defout)) {
        SetValue(section, key, std::to_string(def));
        defout = def;
    }
}


void SPini::SimpleAsDouble(std::string section, std::string key, double &defout) {
    double def = defout;
    if  (!GetValueAsDouble(section, key, defout)) {
        SetValue(section, key, std::to_string(def));
        defout = def;
    }
}

void SPini::SimpleAsBool(std::string section, std::string key, bool &defout) {
    bool def = defout;
    if (!GetValueAsBool(section, key, defout)) {
        if (def) {
            SetValue(section, key, "true");
        } else {
            SetValue(section, key, "false");
        }
        defout = def;
    }
}

bool SPini::GetValueAsString(std::string section, std::string key, std::string & result) {
    std::string val = GetValue(section, key);
    if (val == std::string("")) return false;
    result = val;
    return true;
}

bool SPini::GetValueAsInt(std::string section, std::string key, int & result) {
    std::string val = GetValue(section, key);
    if (val == std::string("")) return false;
    result = std::stoi(val);
    if (!result) return false;
    return true;
}

bool SPini::GetValueAsLong(std::string section, std::string key, long & result) {
    std::string val = GetValue(section, key);
    if (val == std::string("")) return false;
    result = std::stol(val);
    if (!result) return false;
    return true;
}

bool SPini::GetValueAsFloat(std::string section, std::string key, float & result) {
    std::string val = GetValue(section, key);
    if (val == std::string("")) return false;
    result = std::stof(val);
    if (!result) return false;
    return true;
}

bool SPini::GetValueAsDouble(std::string section, std::string key, double & result) {
    std::string val = GetValue(section, key);
    if (val == std::string("")) return false;
    result = std::stod(val);
    if (!result) return false;
    return true;
}

bool SPini::GetValueAsBool(std::string section, std::string key, bool & result) {
    std::string val = GetValue(section, key);
    if (val == std::string("")) return false;
    size_t first = getFirstChar(val);
    if (trim(toLower(val.substr(first, first+4))) == std::string("true")) {
        result = true;
        return true;
    } else if (trim(toLower(val.substr(first, first+5))) == std::string("false")) {
        result = false;
        return true;
    }
    return false;
}

bool SPini::SetValue(std::string section, std::string key, std::string value) {
    // set value of key in section in ini-file
    std::string ls, sec = std::string("[") + toLower(section) + std::string("]");
    std::vector<std::string> buffr;
    std::vector<std::string> spacebuffer;

    if (IniExists()) { // ini exists, read and modify content
        std::ifstream file(m_Filename.c_str());
        if (!file) return false;
        bool right_section = false;
        bool value_set = false;
        while (std::getline(file, ls)) {
            if (isWhitespace(ls)) {
                spacebuffer.push_back(ls);
            } else {
            if (isComment(ls)) {
            } else if (right_section) {
                // check if its new section
                if (isSection(ls)) {
                    if (!value_set) {
                        // append key=value
                        buffr.push_back(key+"="+value);
                        value_set = true;
                    }
                } else {
                    // check if line starts with key=
                    if (isKey(ls, key) && !value_set) {// key found, replace line with key=value
                        buffr.push_back(key+"="+value);
                        value_set = true;
                        continue;
                    }
                }
            } else {
                if (trim(toLower(ls)) == sec) {
                    right_section = true;
                }
            }
            if (spacebuffer.size() > 0) {
                for (int i = 0; i < spacebuffer.size(); ++i) {
                    buffr.push_back(spacebuffer[i]);
                }
                spacebuffer.clear();
            }
            buffr.push_back(ls);
            }
        }
        file.close();
        if (!value_set) {
            if (right_section) {
                buffr.push_back(key+"="+value);
            }
            else {
                buffr.push_back(sec);
                buffr.push_back(key+"="+value);
            }
        }
    } else { // ini does not exit, create content and file
        buffr.push_back(sec);
        buffr.push_back(key+"="+value);
    }
    std::ofstream wfile(m_Filename);
    if (!wfile) return false;
    for (size_t i =0;  i < buffr.size(); i++) {
        wfile << buffr.at(i) << '\n';
    }
    wfile.close();
    return true;
}

bool SPini::IniExists() {
    std::ifstream f(m_Filename);
    if (!f) return false;
    f.close();
    return true;
}

bool SPini::GetSections(std::vector<std::string> &out) {
    bool found = false;
    std::ifstream file(m_Filename.c_str());
    std::string ls;
    while (std::getline(file, ls)) {
        if (isSection(ls)) {
            std::string tmp = trim(ls);
            tmp = tmp.substr(1, tmp.length()-2);
            //std::cout << "found section: " << tmp << std::endl;
            out.push_back(tmp);
            // add to output
            found = true;
        }
    }
    return found;
}

std::string SPini::GetValue(std::string section, std::string key) {
    std::string tmp, result="", ls, sec = std::string("[") + toLower(section) + std::string("]");
    std::ifstream file(m_Filename.c_str());
    if (!file | !file.is_open()) return "";
    bool right_section = false;
    while (std::getline(file, ls)) {

        if (isComment(ls)) continue;

        if (right_section) {
            if (isSection(ls)) right_section = false;
            else {
                tmp = value_for_key(ls, trim(toLower(key)));
                if (tmp != "") result = tmp;
            }
        } else {
            if (trim(toLower(ls)) == sec) {
                right_section = true;
                continue;
            }
        }
    }

    file.close();
    return result;
}

std::string SPini::GetIniFilename() {
    return m_Filename;
}


///////////////////////////////////////////////////////////////////////////////
// protected methods
///////////////////////////////////////////////////////////////////////////////

size_t SPini::getFirstChar(const std::string & str) {
    return str.find_first_not_of(' ');
}

bool SPini::isKey(const std::string & s, const std::string & key) {
    size_t start = getFirstChar(s); // get start of string
    if (trim(toLower(s.substr(start, start+key.length()))) != key) return false; // test if the key passed in is in the string.
    // first word is equal to key
    size_t p =  s.find('='); // p is the location of the first '=' sign
    size_t fnos = s.find_first_not_of(' ', start+key.length()); // find loction of first non whitespace char after the first '=' sign
    if (p == std::string::npos || p != fnos) { // if p is not found  or p is the last character of the string: return false;
        return false;
    }
    return true;
}

bool SPini::isSection(const std::string &s) {
    size_t f = s.find_first_not_of(' ');
    size_t o = s.find(std::string("["));
    size_t c = s.find(std::string("]"));
    if (f == o && o < c) { // only whitespace before [ and ] is after [
        return true;
    }
    return false;
}

bool SPini::isComment(const std::string &s) {
    size_t hc = s.find(std::string("#"));
    size_t cc = s.find(std::string(";"));
    size_t f = s.find_first_not_of(' ');
    if (hc == f || cc == f) { // first character is either # or ; and is therefore a comment
        return true;
    }
    return false;
}

bool SPini::isWhitespace(const std::string &s) {
    size_t fnos = s.find_first_not_of(' \t\n');
    if (fnos == s.npos) {
        return true;
    }
    return false;
}

std::string SPini::value_for_key(const std::string & s, const std::string key) {
    size_t start = getFirstChar(s);
    if (trim(toLower(s.substr(start, start+key.length()))) != key) return "";
    // first word is equal to key

    size_t p =  s.find('=');
    size_t fnos = s.find_first_not_of(' ', start+key.length());

    if (p == std::string::npos || p != fnos) {
        return "";
    }

    p = s.find_first_not_of(" \t\n\r\0", p+1);
    if (p == std::string::npos) return "";
    return s.substr(p);
}

std::string SPini::trim(std::string s) {
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

std::string SPini::toLower(const std::string & s) {
    std::string str = s;
    for (std::string::iterator i = str.begin(); i != str.end(); i++) {
        if (tolower(*i) != (int)*i) *i = (char)tolower(*i);
    }
    return str;
}

bool SPini::isKeyValue(const std::string &s, std::string &key, std::string &value) {
    size_t start = getFirstChar(s);
    size_t eqt = s.find("=", start);
    if (eqt == std::string::npos) {
        return false;
    }
    key = s.substr(start, eqt-start);
    value = s.substr(eqt+1);
   // value = sstr.substr(eqt+1);
    return true;
}
