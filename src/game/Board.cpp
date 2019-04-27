#include "Board.hpp"

std::string getFieldName(Field field){
    if(field == Field::EMPTY)
        return "EMPTY";
    else if(field == Field::WHITE)
        return "WHITE";
    else if(field == Field::BLACK)
        return "BLACK";
    else
        return "ERROR";
}


Board::Board(): phase{GamePhase::FIRST_PHASE},
                white_counter{0},
                black_counter{0}
{
    for(int i = 0; i < 21; i++){
        fields.push_back(Field::EMPTY);
    }
}

GamePhase Board::get_phase(){
    return phase;
}

Field Board::get_field(int index){
    return fields.at(index);
}

bool Board::place_pawn_checks(int index, Field color){
    if(color == Field::EMPTY){
        std::cout << "WARNING: cannot place empty pawn!\n";
        return false;
    }

    if(phase != GamePhase::FIRST_PHASE){
        std::cout << "WARNING: cannot place pawns in other phase than first!\n";
        return false;
    }

    if(index < 0 or index >= 21){
        std::cout << "WARNING: index out of range!\n";
        return false;
    }

    auto& field = fields.at(index);

    if(field == Field::BLACK or field == Field::WHITE){
        std::cout << "WARNING: field is already occupied!\n";
        return false;
    }
    return true;
}

void Board::place_pawn_after(Field color){
    if(color == Field::WHITE)
        white_counter++;
    else if(color == Field::BLACK)
        black_counter++;
    maybe_advance_phase();
}

bool Board::place_pawn(int index, Field color){

    if(not place_pawn_checks(index, color))
        return false;

    fields.at(index) = color;

    place_pawn_after(color);

    return true;
}

void Board::maybe_advance_phase(){
    if(white_counter >= 8 and black_counter >= 8){
        if(phase == GamePhase::FIRST_PHASE)
            phase = GamePhase::SECOND_PHASE;
        else if(phase == GamePhase::SECOND_PHASE)
            phase = GamePhase::THIRD_PHASE;
        else
            std::cout << "Phase wasn't advanced\n";
    }
}
