#include "City.hpp"
#include <ostream>

int City::numOfCity = 1;

bool City::operator==(const City *rhs) {
    return (this->id == rhs->id) && (this->name == rhs->name)
           && (coordinates.first == rhs->coordinates.first)
           && (coordinates.second == rhs->coordinates.second);
}

ostream &operator<<(ostream &os, City &rhs) {
    os << "Name: " << rhs.name;
    return os;
}
