#pragma once

#include "Move.hpp"

class Board;

class Player{
public:
    virtual Move move(Board& board) = 0;
};
