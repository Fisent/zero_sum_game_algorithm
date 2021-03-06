#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <map>

#include "Edge.hpp"
#include "Move.hpp"


enum class GamePhase{
    FIRST_PHASE = 0,
    SECOND_PHASE = 1,
    THIRD_PHASE = 2
};

inline int phase_to_int(GamePhase phase){
    if(phase == GamePhase::FIRST_PHASE)
        return 0;
    else if(phase == GamePhase::SECOND_PHASE)
        return 1;
    else if(phase == GamePhase::THIRD_PHASE)
        return 2;
    std::cout << "Cos sie, cos sie posulo\n";
    return -1; 
}

enum class Field{
    EMPTY,
    WHITE,
    BLACK
};

enum class Advantage{
    PAWN,
    TWO_IN_A_ROW,
    THREE_IN_A_ROW
};


const int NUMBER_OF_FIELDS{24};

const std::map<Advantage, int> cost_map{
    {Advantage::PAWN, 10},
    {Advantage::TWO_IN_A_ROW, 20},
    {Advantage::THREE_IN_A_ROW, 50}
};

class Board{
public:
    Board();

    GamePhase get_phase() const;
    Field get_field(int index) const;
    std::vector<int> get_fields_for_gui() const;
    // get all edges for field
    std::vector<Edge> get_edges_for_field(int field_index) const;
    // get only those fields, to which move is possible
    // (size of returned vector is 0 if field at field_index is empty)
    std::vector<int> get_possible_moves(int field_index) const;
    // first phase
    bool place_pawn(int index);
    // second phase
    bool make_move(int start_index, int destination_index);

    bool take_pawn(int index);
    uint evaluate_points(Field player);

    bool is_it_time_to_take();

// protected:
    bool check_index(int index);
    void next_player();
    bool place_pawn_checks(int index, Field color);
    void place_pawn_after(Field color);
    bool are_fields_connected(int first_index, int second_index);
    bool make_move_checks(int start_index, int destination_index, Field color);
    void make_move_after(Field color);
    bool take_pawn_checks(int index, Field color);
    void take_pawn_after(Field color);
    void maybe_advance_phase();
    void evaluate_scores();
    void after_move_check_threes(Field color);

    std::vector<Field> fields;
    std::vector<Edge> edges;
    GamePhase phase;
    int white_counter;
    int black_counter;
    Field current_player;
    bool time_to_take;
};

std::string getFieldName(Field field);
std::ostream & operator << (std::ostream& out, const Board& board);
bool operator==(const Board& lhs, const Board& rhs);
