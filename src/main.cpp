#include <iostream>
#include <string>
#include <memory>

#include "game/Board.hpp"
#include "game/Game.hpp"
#include "game/HumanPlayer.hpp"


int main(){
    auto player_one = std::shared_ptr<Player>(new HumanPlayer{});
    auto player_two = std::shared_ptr<Player>(new HumanPlayer{});

    Game g{player_one, player_two};
    g.play();
}
