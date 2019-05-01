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
class Game{
    Game(std::shared_ptr<Player> player_one, std::shared_ptr<Player> player_two){}
};
