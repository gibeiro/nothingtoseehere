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

// TEST_CASE("invalid path")
// {    
//     REQUIRE_THROWS_AS(Solution().run(""), std::invalid_argument);
// }

// TEST_CASE("unexistant json")
// {    
//     REQUIRE_THROWS_AS(Solution().run("prettysurethisdoesntexist.json"), std::invalid_argument);
// }

TEST_CASE("clustered")
{
    JSON json = {
        {"rects", {
            { {"x", 10}, {"y", 1}, {"w", 1}, {"h", 1} },
            { {"x", 10}, {"y", 2}, {"w", 2}, {"h", 2} },
            { {"x", 10}, {"y", 3}, {"w", 3}, {"h", 3} },
            { {"x", 10}, {"y", 4}, {"w", 4}, {"h", 4} },
            { {"x", 10}, {"y", 5}, {"w", 5}, {"h", 5} },
            { {"x", 10}, {"y", 6}, {"w", 6}, {"h", 6} },
            { {"x", 10}, {"y", 7}, {"w", 7}, {"h", 7} },
            { {"x", 10}, {"y", 8}, {"w", 8}, {"h", 8} },
            { {"x", 10}, {"y", 9}, {"w", 9}, {"h", 9} },
            { {"x", 10}, {"y", 10}, {"w", 10}, {"h", 10} }
        }}
    };

    Solution s;

    REQUIRE_NOTHROW(SolutionTest::run(s,json));
}

// TEST_CASE("clustered")
// {
//     JSON json = {
//         {"rects", {
//             { {"x", 0}, {"y", 1}, {"w", 1}, {"h", 1} },
//             { {"x", 0}, {"y", 2}, {"w", 2}, {"h", 2} },
//             { {"x", 0}, {"y", 3}, {"w", 3}, {"h", 3} },
//             { {"x", 0}, {"y", 4}, {"w", 4}, {"h", 4} }
//         }}
//     };

//     Solution s;
//     SolutionTest::set_rect_vector(s,RectangleVector{})
//     REQUIRE_THROWS_AS(Solution().run("prettysurethisdoesntexist.json"), std::invalid_argument);
// }
