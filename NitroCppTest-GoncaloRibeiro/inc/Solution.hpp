#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <string>
#include <vector>
#include <unordered_set>

#include "Rectangle.hpp"

using RectangleVector = std::vector<Rectangle>;
using RectangleKey = std::string;
using RectangleSet = std::unordered_set<RectangleKey>;

class Solution
{
public:
    friend class SolutionTest;
    void run(const std::string& path)
    {
        parse(path);
        calc();
        print();
    };

private:
    RectangleVector rectangle_vector_;
    RectangleSet rectangle_set_;

    void run(const JSON& json)
    {
        parse(json);
        calc();
        print();
    };
    void parse(const std::string& path);
    void parse(const JSON& json);
    void calc() noexcept;
    void print() const noexcept;
};

#endif /* SOLUTION_HPP */
