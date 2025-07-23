#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Solution.hpp"
#include "Rectangle.hpp"

class SolutionTest
{
    public:
    static void run(Solution& s, const JSON& json)
    {
        s.run(json);
    }
    static void parse(Solution& s, const std::string& path)
    {
        s.parse(path);
    };
    static void calc(Solution& s)
    {
        s.calc();
    };
    static void print(Solution& s)
    {
        s.print();
    };
    static RectangleVector get_rect_vector(Solution& s)
    {
        return s.rectangle_vector_;

    };
    static RectangleSet get_rect_set(Solution& s)
    {
        return s.rectangle_set_;
    };
    static void set_rect_vector(Solution& s, const RectangleVector& vec)
    {
        s.rectangle_vector_ = vec;
    };
    static void set_rect_set(Solution& s, const RectangleSet& set)
    {
        s.rectangle_set_ = set;
    };
};

class RectangleTest
{
    public:
    static void set_x(Rectangle& r, std::uint32_t x)
    {
        r.x_ = x;
    };
    static void set_y(Rectangle& r, std::uint32_t y)
    {
        r.y_ = y;
    };
    static void set_w(Rectangle& r, std::uint32_t w)
    {
        r.w_ = w;
    };
    static void set_h(Rectangle& r, std::uint32_t h)
    {
        r.h_ = h;
    };
    static void set_parents(Rectangle& r, const Parents& p)
    {
        r.parents_ = p;
    };
};

TEST_CASE("invalid path")
{
    std::string path = "";
    REQUIRE_THROWS(Solution().run(path));
}

TEST_CASE("invalid json")
{
    JSON json = {
        {"rects", {
            { {"x", -1}, {"y", 1}, {"w", 1}, {"h", 1} }
        }}
    };

    Solution s;

    REQUIRE_THROWS(SolutionTest::run(s,json));
}
