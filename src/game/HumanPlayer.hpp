#pragma once

#include <memory>

#include "Player.hpp"
#include "Move.hpp"
#include "XmlRpc.hpp"

class HumanPlayer : public Player{
public:
    Move move(std::shared_ptr<Board>& board) override{
        auto fields = board->get_fields_for_gui();
        auto phase = board->get_phase();
        return ask_player_about_move(fields, phase_to_int(board->get_phase()));
    }
};
