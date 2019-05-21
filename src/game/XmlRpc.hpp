#pragma once

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

#include <vector>
#include <string>
#include <sstream>

#include "Board.hpp"

std::string fields_to_string(const std::vector<int>& fields);

Move ask_player_about_move(std::vector<int> fields, int phase);

// void xml_rpc(std::vector<int> fields, int phase);