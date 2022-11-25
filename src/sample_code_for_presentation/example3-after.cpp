#include <string>
#include <utility>

class Example3
{
public:
    explicit Example3(std::string text) : m_Text(std::move(text)){};

private:
    const std::string m_Text;
};

void Test()
{
    Example3 ex3(std::string("potatis"));
}