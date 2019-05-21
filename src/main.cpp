#include <iostream>
#include <string>

#include "game/Board.hpp"
#include "game/Game.hpp"
#include "game/XmlRpc.hpp"

int main(){
    Board b;
    b.phase = GamePhase::SECOND_PHASE;
    b.place_pawn(0);
    b.place_pawn(1);
    auto fields = b.get_fields_for_gui();
    auto phase = b.get_phase();
    std::cout << "phase: " << phase_to_int(phase) << '\n';
    xml_rpc(fields, phase_to_int(b.get_phase()));
}
