#pragma once

//forward declaration
class Board;

class Player{
public:
    virtual void move(Board& board) = 0;
};
