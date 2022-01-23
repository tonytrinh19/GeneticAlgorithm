#ifndef ASSIGNMENT2_CITY_HPP
#define ASSIGNMENT2_CITY_HPP

#include <string>

using namespace std;

class City {
private:
    // coordinates are limited to range [0,1000] inclusive
    pair<unsigned int, unsigned int> coordinates;
    int                              id;
    string                           name;
    static int                       numOfCity;

public:

    /**
     * Constructor for City, initializes ID, name, and coordinates for City.
     * @param coordinates x,y coordinates for City.
     */
    City(pair<unsigned int, unsigned int> coordinates) : coordinates(move(coordinates)) {
        this->id   = numOfCity++;
        this->name = "City " + to_string(id);
    }

    /**
     * Getter function for name.
     * @return string name of the city
     */
    string getName() const {
        return name;
    }

    /**
     * Getter function for x coordinate of the city.
     * @return unsigned int x coordinate
     */
    unsigned int getX() const {
        return coordinates.first;
    }

    /**
     * Getter function for y coordinate of the city.
     * @return unsigned int y coordinate
     */
    unsigned int getY() const {
        return coordinates.second;
    }

    /**
     * Overloaded == function for City, two cities are
     * considered equals when ID, name, and coordinates match.
     * @param rhs City to compare to
     * @return bool result whether two City are equals
     */
    bool operator==(const City *rhs);

    friend ostream& operator<<(ostream &os, City& rhs);
};


#endif //ASSIGNMENT2_CITY_HPP
