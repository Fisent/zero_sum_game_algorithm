#pragma once

#include "Move.hpp"

class Board;

class Player{
public:
    virtual Move move(std::shared_ptr<Board>& board) = 0;
};
