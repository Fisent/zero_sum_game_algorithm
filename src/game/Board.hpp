
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

class Board{
public:
    Board(): phase{GamePhase::FIRST_PHASE}{
        for(int i = 0; i < 21; i++){
            fields.push_back(Field::EMPTY);
        }
    }

    GamePhase getPhase(){
        return phase;
    }

    Field getField(int index){
        return fields.at(index);
    }

private:
    std::vector<Field> fields;
    GamePhase phase;
};
