#include "Edge.hpp"

std::ostream & operator << (std::ostream& out, const Edge& edge){
    out << "Edge beetween " << edge.first_field << " and " << edge.second_field << '\n';
    return out;
}
