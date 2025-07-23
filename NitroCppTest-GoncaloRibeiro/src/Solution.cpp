#include <fstream>
#include <iostream>
#include <filesystem>
#include <optional>

#include "Solution.hpp"

void Solution::parse(const std::string& path)
{
    if(path.empty())
    {
        throw std::invalid_argument("Path is empty");
    }

    if(!std::filesystem::exists(path))
    {
        throw std::invalid_argument("JSON file doesn't exists: " + path);
    }

    std::ifstream file(path);

    if(!file)
    {
        throw std::runtime_error("Could not read from file: " + path);
    }

    JSON json;
    file >> json;

    parse(json);
}

void Solution::parse(const JSON& json)
{
    if(!json.is_object())
    {
        throw std::runtime_error("Invalid JSON");
    }

    if(!json.contains("rects"))
    {
        throw std::runtime_error("Missing field: 'rects'");
    }

    if(!json["rects"].is_array())
    {
        throw std::runtime_error("Invalid field: 'rects' should be array");
    }

    for(const auto& rect : json["rects"])
    {
        if(Rectangle::get_rectangle_counter() >= MAX_RECTANGLES) break;
        rectangle_vector_.push_back(Rectangle(rect));
    }
}

void Solution::calc() noexcept
{
    for(std::size_t head = 0; head < rectangle_vector_.size(); head++)
    {
        for(std::size_t tail = 0; tail < head; tail++)
        {
            const Rectangle& head_rectangle = rectangle_vector_[head];
            const Rectangle& tail_rectangle = rectangle_vector_[tail];

            if(tail_rectangle.parents_are_subset_of(head_rectangle)) continue;

            std::optional<Rectangle> intersection = head_rectangle.intersect(tail_rectangle);

            if(!intersection) continue;

            const RectangleKey key = intersection->to_string();
            auto [_, inserted] = rectangle_set_.insert(key);

            if(!inserted) continue;

            rectangle_vector_.push_back(std::move(*intersection));
        }
    }
}

void Solution::print() const noexcept
{
    std::size_t i = 0;

    std::cout << "Input:" << std::endl;

    for(; i < rectangle_vector_.size(); i++)
    {
        const Rectangle& rect = rectangle_vector_[i];

        if(rect.get_parents().size() != 1) break;

        std::cout << "\t";
        std::cout << i + 1;
        std::cout << ": Rectangle at (";
        std::cout << rect.get_x();
        std::cout << ",";
        std::cout << rect.get_y();
        std::cout << "), w=";
        std::cout << rect.get_w();
        std::cout << ", h=";
        std::cout << rect.get_h();
        std::cout << "." << std::endl;
    }

    std::cout << "Intersections" << std::endl;

    for(; i < rectangle_vector_.size(); i++)
    {
        const Rectangle& rect = rectangle_vector_[i];
        const Parents& rect_parents = rect.get_parents();
        std::vector<RectangleId> rect_parents_ids(rect_parents.begin(),rect_parents.end());

        std::cout << "\tBetween rectangle ";

        for(size_t j = 0; j < rect_parents_ids.size(); j++)
        {
            std::cout << rect_parents_ids[j];

            if (j < rect_parents_ids.size() - 2)
            {
                std::cout << ", ";
            }
            else if (j == rect_parents_ids.size() - 2)
            {
                std::cout << " and ";
            }
        }

        std::cout << " at (";
        std::cout << rect.get_x();
        std::cout << ",";
        std::cout << rect.get_y();
        std::cout << "), w=";
        std::cout << rect.get_w();
        std::cout << ", h=";
        std::cout << rect.get_h();
        std::cout << "." << std::endl;
    }
}
