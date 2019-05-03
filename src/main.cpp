#include <iostream>
#include <string>

#include "game/Board.hpp"
#include "game/Game.hpp"
#include "game/XmlRpc.hpp"

int main(){
    Board b;
    b.place_pawn(0);
    auto fields = b.get_fields_for_gui();
    xml_rpc(fields, static_cast<int>(b.get_phase()));
}
