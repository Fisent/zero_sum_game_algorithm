#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Edge.hpp"

enum class GamePhase{
    FIRST_PHASE,
    SECOND_PHASE,
    THIRD_PHASE
};

enum class Field{
    EMPTY,
    WHITE,
    BLACK
};

const int NUMBER_OF_FIELDS{24};

class Board{
public:
    Board();

    GamePhase get_phase() const;
    Field get_field(int index) const;
    // get all edges for field
    std::vector<Edge> get_edges_for_field(int field_index) const;
    // get only those edges for field, to which move is possible
    // (size of returned vector is 0 if field at field_index is empty)
    std::vector<Edge> get_proper_edges_for_field(int field_index) const;
    // first phase
    bool place_pawn(int index, Field color);
    // second phase
    bool make_move(int start_index, int destination_index);

private:
    bool check_index(int index);
    void next_player();
    bool place_pawn_checks(int index, Field color);
    void place_pawn_after(Field color);
    bool are_fields_connected(int first_index, int second_index);
    bool make_move_checks(int start_index, int destination_index);
    void make_move_after();
    void maybe_advance_phase();

    std::vector<Field> fields;
    std::vector<Edge> edges;
    GamePhase phase;
    int white_counter;
    int black_counter;
    Field current_player;
};

std::string getFieldName(Field field);
std::ostream & operator << (std::ostream& out, const Board& board);
bool operator==(const Board& lhs, const Board& rhs);
