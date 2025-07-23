#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <optional>
#include <set>

#include "json.hpp"
using JSON = nlohmann::json;

using RectangleId = std::uint32_t;
using Parents = std::set<RectangleId>;

constexpr std::size_t MAX_RECTANGLES = 10;

class Rectangle
{
public:
    friend class RectangleTest;
    Rectangle(const JSON& json);
    Rectangle(std::uint32_t x, std::uint32_t y, std::uint32_t w, std::uint32_t h, Parents parents);

    std::uint32_t get_x() const noexcept;
    std::uint32_t get_y() const noexcept;
    std::uint32_t get_w() const noexcept;
    std::uint32_t get_h() const noexcept;
    const Parents& get_parents() const noexcept;

    std::optional<Rectangle> intersect(const Rectangle& other) const noexcept;
    bool parents_are_subset_of(const Rectangle& other) const noexcept;
    std::string to_string() const noexcept;

    static std::uint8_t get_rectangle_counter() noexcept;

private:
    static std::uint8_t rectangle_counter_;
    std::uint32_t x_;
    std::uint32_t y_;
    std::uint32_t w_;
    std::uint32_t h_;
    Parents parents_;
};


#endif /* RECTANGLE_HPP */
