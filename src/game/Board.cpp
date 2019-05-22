#include <algorithm>
#include <array>

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

const std::vector<Edge> all_edges{
    //horizontal edges
    Edge{0, 1}, Edge{1, 2},
    Edge{3, 4}, Edge{4, 5},
    Edge{6, 7}, Edge{7, 8},
    Edge{9, 10}, Edge{10, 11},  Edge{12, 13}, Edge{13, 14},
    Edge{15, 16}, Edge{16, 17},
    Edge{18, 19}, Edge{19, 20},
    Edge{21, 22}, Edge{22, 23},

    //vertical edges
    Edge{0, 9}, Edge{9, 21},
    Edge{3, 10}, Edge{10, 18},
    Edge{1, 4}, Edge{4, 7}, Edge{16, 19}, Edge{19, 22},
    Edge{8, 12}, Edge{12, 17},
    Edge{5, 13}, Edge{13, 20},
    Edge{2, 14}, Edge{14, 23}
};

const std::vector<std::array<int, 3>> rows_cols_to_check{
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {9, 10, 11},
    {12, 13, 14},
    {15, 16, 17},
    {18, 19, 20},
    {21, 22, 23},
    {0, 9, 21},
    {3, 10, 18},
    {6, 11, 15},
    {1, 4, 7},
    {16, 19, 22},
    {8, 12, 17},
    {5, 13, 20},
    {2, 14, 23}
};

/*
0-----1-----2
|     |     |
| 3---4---5 |
| |   |   | |
| | 6-7-8 | |
| | |   | | |
9-1011 12-1314
| | |   | | |
| |15-1617| |
| |   |   | |
| 18--19--20|
|     |     |
21----22---23

*/

Board::Board(): phase{GamePhase::FIRST_PHASE},
                white_counter{0},
                black_counter{0},
                current_player{Field::WHITE},
                edges(all_edges),
                time_to_take{false}
{
    for(int i = 0; i < NUMBER_OF_FIELDS; i++){
        fields.push_back(Field::EMPTY);
    }
}

GamePhase Board::get_phase() const{
    return phase;
}

Field Board::get_field(int index) const{
    return fields.at(index);
}

std::vector<int> Board::get_fields_for_gui() const{
    std::vector<int> result{};
    for(auto field : fields)
        result.push_back(static_cast<int>(field));
    return result;
}

std::vector<Edge> Board::get_edges_for_field(int field_index) const{
    std::vector<Edge> results{};
    for(auto edge : edges){
        if(edge.contains(field_index)){
            results.push_back(edge);
        }
    }
    return results;
}

std::vector<int> Board::get_possible_moves(int field_index) const{
    std::vector<int> results{};
    if(get_field(field_index) == Field::EMPTY){
        return {};
    }

    auto field_edges = get_edges_for_field(field_index);
    for(auto edge : field_edges){
        int other_end = edge.get_other_end(field_index);
        if(get_field(other_end) == Field::EMPTY){
            results.push_back(other_end);
        }
    }
    return results;
}

/*
SCORING
for every pawn - 10 points
for two pawns in a row - 20 points
for three pawns in a row(mlynek) - 50 points
*/
uint Board::evaluate_points(Field player_color){
    int result{0};

    //count pawns
    int pawn_number{player_color == Field::WHITE ? white_counter : black_counter};
    result += pawn_number * cost_map.at(Advantage::PAWN);

    //check twos and threes
    int twos{0};
    for(auto row_col : rows_cols_to_check){
        int counter{0};
        for(int i = 0; i < 3; i++){
            if(fields.at(row_col.at(i)) == player_color)
                counter++;
        }
        if(counter == 2)
            result += cost_map.at(Advantage::TWO_IN_A_ROW);
        else if(counter == 3)
            result += cost_map.at(Advantage::THREE_IN_A_ROW);
    }

    return result;
}

void Board::next_player(){
    if(current_player == Field::WHITE)
        current_player = Field::BLACK;
    else if(current_player == Field::BLACK)
        current_player = Field::WHITE;
    else
        std::cout << "CRITICAL ERROR: current player cant be empty";
}

void Board::after_move_check_threes(Field player_color){
    for(auto row_col : rows_cols_to_check){
        int counter{0};
        for(int i = 0; i < 3; i++){
            if(fields.at(row_col.at(i)) == player_color)
                counter++;
        }
        if(counter == 3){
            time_to_take = true;
        }
    }
}

bool Board::check_index(int index){
    return index >=0 and index <= NUMBER_OF_FIELDS - 1;
}

bool Board::place_pawn_checks(int index, Field color){
    if(phase != GamePhase::FIRST_PHASE){
        std::cout << __func__ << " WARNING: it is not first phase\n";
        return false;
    }
    if(time_to_take){
        std::cout << __func__ << " WARNING: it is time to take, not place pawn\n";
        return false;
    }
    if(color == Field::EMPTY){
        std::cout << __func__ << "WARNING: cannot place empty pawn!\n";
        return false;
    }

    if(phase != GamePhase::FIRST_PHASE){
        std::cout << __func__ << " WARNING: cannot place pawns in other phase than first!\n";
        return false;
    }

    if(not check_index(index)){
        std::cout << __func__ << " WARNING: index out of range!\n";
        return false;
    }

    auto& field = fields.at(index);

    if(current_player != color){
        std::cout << "WARNING: this is not " << getFieldName(color) << " turn!\n";
        std::cout << getFieldName(current_player) << " should move now!\n";
        return false;
    }

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
    next_player();
    after_move_check_threes(color);
}

bool Board::place_pawn(int index){

    Field color = current_player;

    if(not place_pawn_checks(index, color))
        return false;

    fields.at(index) = color;

    place_pawn_after(color);

    return true;
}

void Board::maybe_advance_phase(){
    if(white_counter >= 9 and black_counter >= 9){
        if(phase == GamePhase::FIRST_PHASE)
            phase = GamePhase::SECOND_PHASE;
        else if(phase == GamePhase::SECOND_PHASE)
            phase = GamePhase::THIRD_PHASE;
        else
            std::cout << "Phase wasn't advanced\n";
    }
}

bool Board::are_fields_connected(int first_field, int second_field){
    bool result{false};
    Edge temp_edge{first_field, second_field};
    for(auto edge : edges){
        result = result or temp_edge == edge; 
    }
    return result;
}

bool Board::make_move_checks(int start_index, int destination_index, Field color){
    if(time_to_take){
        std::cout << __func__ << " WARNING: it is time to take, not for normal move\n";
        return false;
    }
    if(not check_index(start_index) or not check_index(destination_index)){
        std::cout << __func__ << " WARNING: one of indexes is wrong!\n";
        return false;
    }
    if(fields.at(start_index) == Field::EMPTY){
        std::cout << __func__ << " WARNING: cannot move from empty field\n";
        return false;
    }

    if(fields.at(destination_index) != Field::EMPTY){
        std::cout << __func__ << " WARNING: cannot move to not empty field!\n";
        return false;
    }
    if(not are_fields_connected(start_index, destination_index)){
        std::cout << __func__ << " WARNING: move not made, because fields are not connected\n";
        return false;
    }
    if(fields.at(start_index) != current_player){
        std::cout << __func__ << "WARNING: move not made, because pawn at start_index doesn't belong to current_player\n";
        return false;
    }

    return true;
}

void Board::make_move_after(Field color){
    next_player();
    after_move_check_threes(color);
}

bool Board::make_move(int start_index, int destination_index){
    Field color = current_player;

    if(not make_move_checks(start_index, destination_index, color))
        return false;

    //make move
    Field field = fields.at(start_index);
    fields.at(start_index) = Field::EMPTY;
    fields.at(destination_index) = field;


    make_move_after(color);
    return true;
}

bool Board::take_pawn_checks(int index, Field color){
    if(not time_to_take){
        std::cout << __func__ << " WARNING: it isn't time to take\n";
        return false;
    }
    if(not check_index(index)){
        std::cout << __func__ << " WARNING: index is wrong\n";
        return false;
    }
    Field field_color = fields.at(index);

    if(field_color == Field::EMPTY){
        std::cout << __func__ << " WARNING cannot take from empty field\n";
        return false;
    }

    if(field_color != color){
        std::cout << __func__ << " WARNING: this player cannot take from this field\n";
        return false;
    }

    return true;
}

void Board::take_pawn_after(Field color){
    time_to_take = false;

    after_move_check_threes(color);
}

bool Board::take_pawn(int index){
    Field color_of_taking_player = current_player;

    if(not take_pawn_checks(index, color_of_taking_player)){
        return false;
    }

    fields.at(index) = Field::EMPTY;

    take_pawn_after(color_of_taking_player);

    return true;
}

bool Board::is_it_time_to_take(){
    return time_to_take;
}

char get_fields_char(int index, const Board& board){
    Field field = board.get_field(index);
    if(field == Field::BLACK)
        return 'B';
    else if(field == Field::WHITE)
        return 'W';
    else if(field == Field::EMPTY)
        return 'o';
    else
        return 'E';
}

std::ostream & operator << (std::ostream& out, const Board& board)
{
    out << '\n';

    out << get_fields_char(0, board);
    out << "-----";
    out << get_fields_char(1, board);
    out << "-----";
    out << get_fields_char(2, board) << '\n';

    out << "|     |     |" << '\n';

    out << "| ";
    out << get_fields_char(3, board);
    out << "---";
    out << get_fields_char(4, board);
    out << "---";
    out << get_fields_char(5, board);
    out << " |" << '\n';

    out << "| |   |   | |" << '\n';

    out << "| | ";
    out << get_fields_char(6, board);
    out << '-';
    out << get_fields_char(7, board);
    out << '-';
    out << get_fields_char(8, board);
    out << " | |" << '\n';

    out << "| | |   | | |" << '\n';

    out << get_fields_char(9, board);
    out << '-';
    out << get_fields_char(10, board);
    out << '-';
    out << get_fields_char(11, board);
    out << "   ";
    out << get_fields_char(12, board);
    out << '-';
    out << get_fields_char(13, board);
    out << '-';
    out << get_fields_char(14, board) << '\n';

    out << "| | |   | | |" << '\n';

    out << "| | ";
    out << get_fields_char(15, board);
    out << '-';
    out << get_fields_char(16, board);
    out << '-';
    out << get_fields_char(17, board);
    out << " | |" << '\n';

    out << "| |   |   | |" << '\n';

    out << "| ";
    out << get_fields_char(18, board);
    out << "---";
    out << get_fields_char(19, board);
    out << "---";
    out << get_fields_char(20, board);
    out << " |" << '\n';

    out << "|     |     |" << '\n';

    out << get_fields_char(21, board);
    out << "-----";
    out << get_fields_char(22, board);
    out << "-----";
    out << get_fields_char(23, board) << '\n';

    return out;
}

bool operator==(const Board& lhs, const Board& rhs)
{
    bool result{true};
    for(int i = 0; i < NUMBER_OF_FIELDS; i++){
        result = result and lhs.get_field(i) == rhs.get_field(i);
    }
    return result;
}

