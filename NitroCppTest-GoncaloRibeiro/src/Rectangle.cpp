#include <optional>
#include <iostream>
#include "json.hpp"
#include "Rectangle.hpp"

std::uint8_t Rectangle::rectangle_counter_ = 0;

Rectangle::Rectangle(const JSON& json)
{
    if (!json.is_object())
    {
        throw std::invalid_argument("JSON must be an object");
    }

    if (!json.contains("x"))
    {
        throw std::invalid_argument("Missing field: 'x'");
    }

    if (!json.contains("y"))
    {
        throw std::invalid_argument("Missing field: 'y'");
    }

    if (!json.contains("w"))
    {
        throw std::invalid_argument("Missing field: 'w'");
    }

    if (!json.contains("h"))
    {
        throw std::invalid_argument("Missing field: 'h'");
    }

    if (!json["x"].is_number_unsigned())
    {
        throw std::invalid_argument("Invalid field: " + json["x"].dump());
    }

    if (!json["y"].is_number_unsigned())
    {
        throw std::invalid_argument("Invalid field: " + json["y"].dump());
    }

    if (!json["w"].is_number_unsigned())
    {
        throw std::invalid_argument("Invalid field: " + json["w"].dump());
    }

    if (!json["h"].is_number_unsigned())
    {
        throw std::invalid_argument("Invalid field: " + json["h"].dump());
    }

    x_ = json["x"].get<std::uint32_t>();
    y_ = json["y"].get<std::uint32_t>();
    h_ = json["h"].get<std::uint32_t>();
    w_ = json["w"].get<std::uint32_t>();

    if (w_ == 0 || h_ == 0)
    {
        throw std::invalid_argument("Width and height must be positive");
    }

    parents_.insert(++rectangle_counter_);
}

Rectangle::Rectangle(std::uint32_t x, std::uint32_t y, std::uint32_t w, std::uint32_t h, Parents parents)
{
    if (w == 0 || h == 0)
    {
        throw std::invalid_argument("Width and height must be positive");
    }

    x_ = x;
    y_ = y;
    h_ = w;
    w_ = h;
    parents_ = std::move(parents);
};

std::optional<Rectangle> Rectangle::intersect(const Rectangle& other) const noexcept
{
    std::uint32_t x_left, x_right, y_top, y_bottom;

    x_left = std::max(x_,other.x_);
    x_right = std::min(x_ + w_, other.x_ + other.w_);

    y_top = std::max(y_, other.y_);
    y_bottom = std::min(y_ + h_, other.y_ + other.h_);

    if (x_left >= x_right || y_top >= y_bottom) return std::nullopt;

    Parents merged;
    std::set_union(
        parents_.begin(),
        parents_.end(),
        other.parents_.begin(),
        other.parents_.end(),
        std::inserter(merged,merged.begin()
    ));

    return Rectangle(x_left, y_top, y_bottom - y_top, x_right - x_left, std::move(merged));
}

std::uint8_t Rectangle::get_rectangle_counter() noexcept
{
    return rectangle_counter_;
}

std::string Rectangle::to_string() const noexcept
{
    std::string str;
    str += "(";
    str += std::to_string(x_);
    str += ",";
    str += std::to_string(y_);
    str += ",";
    str += std::to_string(w_);
    str += ",";
    str += std::to_string(h_);
    str += ",";
    str += "{";

    auto it = parents_.begin();
    str += std::to_string(*it++);

    while(it != parents_.end())
    {
        str += ",";
        str += std::to_string(*it++);
    }
    str += "}";
    str += ")";

    return str;
}

bool Rectangle::parents_are_subset_of(const Rectangle& other) const noexcept
{
    return std::includes(
        other.parents_.begin(), other.parents_.end(),
        parents_.begin(), parents_.end()
    );
}

std::uint32_t Rectangle::get_x() const noexcept
{
    return x_;
}

std::uint32_t Rectangle::get_y() const noexcept
{
    return y_;
}

std::uint32_t Rectangle::get_w() const noexcept
{
    return w_;
}

std::uint32_t Rectangle::get_h() const noexcept
{
    return h_;
}

const Parents& Rectangle::get_parents() const noexcept
{
    return parents_;
}
