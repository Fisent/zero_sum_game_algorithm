#pragma once

#include <string>
#include <iostream>
#include <vector>

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

std::string getFieldName(Field field);

class Board{
public:
    Board();

    GamePhase get_phase() const;
    Field get_field(int index) const;
    bool place_pawn(int index, Field color);

private:
    bool place_pawn_checks(int index, Field color);
    void place_pawn_after(Field color);
    void maybe_advance_phase();

    std::vector<Field> fields;
    GamePhase phase;
    int white_counter;
    int black_counter;
};

std::ostream & operator << (std::ostream& out, const Board& board);