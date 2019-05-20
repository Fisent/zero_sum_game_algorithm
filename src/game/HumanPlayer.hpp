#pragma once

#include "Player.hpp"
#include "Move.hpp"

class HumanPlayer : public Player{
public:
    Move move(Board& board) override{
        return Move{0, 0};
    }
};
