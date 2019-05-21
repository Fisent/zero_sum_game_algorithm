#pragma once

#include <memory>

#include "HumanPlayer.hpp"
/*
    I think that this class will control the flow of the whole game.
    In constructor there will be passed two player objects:
    Player will be and abstract class, for which there will be two main specifications
    HumanPlayer and also AIPlayer.
    Game class will ask human player for move when it will be its move.
    In case of human player the person will have to move on GUI, and then it will be passed to the game with Move struct.
    AI player will calculate the best move and return it also in form of Move struct

    Im thinking about implementing GUI in python. It will be faster, but I will have to find some proper interface beetween
    C++ and Python

    The interface will be XML RPC.
    Python GUI will be the localhost server to which c++ app will send messages with move inqury and it will return the move
*/

std::ostream & operator << (std::ostream& out, const Move& move)
{
    out << "Move: " << move.first_index << ", " << move.second_index;
    return out;
}

class Game{
public:
    Game(std::shared_ptr<Player> player_one, std::shared_ptr<Player> player_two): 
        player_one_{player_one}, player_two_{player_two}, in_progress_{false} {}

    void play(){
        board_ = std::make_shared<Board>();
        std::cout << "board created with phase " << static_cast<int>(board_->get_phase()) << '\n';
        in_progress_ = true;
        
        Move move{-1};
        while(in_progress_){
            move = player_one_->move(board_);
            apply_move(move);
            move = player_two_->move(board_);
            apply_move(move);
        }
    }

private:
    bool apply_move(Move move){
        std::cout << "Applying move: " << move <<  "\n";
        auto phase = board_->get_phase();
        if(phase == GamePhase::FIRST_PHASE){
            return board_->place_pawn(move.first_index);
        }
        else if(phase == GamePhase::SECOND_PHASE){
            return board_->make_move(move.first_index, move.second_index);
        }
        else
            std::cout << "Third phase, not implemented yet\n";
        return false;
    }

    bool                        in_progress_;
    std::shared_ptr<Board>      board_;
    std::shared_ptr<Player>     player_one_;
    std::shared_ptr<Player>     player_two_;
};
