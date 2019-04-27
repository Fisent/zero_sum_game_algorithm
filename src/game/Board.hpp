#include <string>
#include <iostream>

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

class Board{
public:
    Board(): phase{GamePhase::FIRST_PHASE}{
        for(int i = 0; i < 21; i++){
            fields.push_back(Field::EMPTY);
        }
    }

    GamePhase get_phase(){
        return phase;
    }

    Field get_field(int index){
        return fields.at(index);
    }

    bool place_pawn(int index, Field color){
        if(color == Field::EMPTY){
            std::cout << "ERROR: cannot place empty pawn!\n";
            return false;
        }
        if(phase != GamePhase::FIRST_PHASE){
            std::cout << "ERROR: cannot place pawns in other phase than first!\n";
            return false;
        }
        if(index < 0 or index >= 21){
            std::cout << "ERROR: index out of range!\n";
            return false;
        }   

        auto& field = fields.at(index);
        field = color;
        return true;
    }

private:
    std::vector<Field> fields;
    GamePhase phase;
};
