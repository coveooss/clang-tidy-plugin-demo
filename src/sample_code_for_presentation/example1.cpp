class Example1 {
public:
    Example1(const Example1&) = default;
    Example1(Example1&&) = default;
    Example1& operator=(const Example1& that);
    Example1& operator=(Example1&& that) noexcept;
    ~Example1() = default;
private:
    int* p = nullptr;
};

inline Example1& Example1::operator=(const Example1& that)
{
    p = that.p;
    return *this;
}