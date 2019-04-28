#pragma once

#include <iostream>

class Edge{
public:
    Edge(int first_field, int second_field): first_field{first_field}, second_field{second_field}
    {}

    bool connects(int first_index, int second_index) const{
        bool first_way = first_index == first_field and second_index == second_field;
        bool second_way = first_index == second_field and second_index == first_field;
        return first_way or second_way;
    }

    bool contains(int field_index) const{
        return first_field == field_index or second_field == field_index;
    }

    bool operator==(const Edge& other) const{
        bool first_way = first_field == other.first_field and second_field == other.second_field;
        bool second_way = first_field == other.second_field and second_field == other.first_field;
        return first_way or second_way;
    }

    int first_field;
    int second_field;
};

std::ostream & operator << (std::ostream& out, const Edge& edge);