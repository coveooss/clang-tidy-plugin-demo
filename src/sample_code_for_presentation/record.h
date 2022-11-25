#include <string>

struct Record {
    Record(std::string key, std::string data): m_Key(std::move(key)), m_Data(std::move(data)) {}

    std::string m_Key;
    std::string m_Data;
};