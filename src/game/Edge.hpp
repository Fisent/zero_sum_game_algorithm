#pragma once

class Edge{
public:
    Edge(int first_field, int second_field): first_field{first_field}, second_field{second_field}
    {}

    bool connects(int first_index, int second_index){
        bool first_way = first_index == first_field and second_index == second_field;
        bool second_way = first_index == second_field and second_index == first_field;
        return first_way or second_way;
    }
private:
    int first_field;
    int second_field;
};
