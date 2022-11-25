#include <string>

class Example3
{
public:
    explicit Example3(const std::string& text) : m_Text(text){};

private:
    const std::string m_Text;
};

void Test()
{
    Example3 ex3(std::string("potatis"));
}