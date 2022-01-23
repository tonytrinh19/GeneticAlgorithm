#ifndef ASSIGNMENT2_TOUR_HPP
#define ASSIGNMENT2_TOUR_HPP

#include "City.hpp"
#include <utility>
#include <vector>
#include <random>

using engine = mt19937;

class Tour {
private:
    double fitness  = 0;
    double distance = 0;
    std::vector<City *> tour;
public:

    /**
     * Constructor for Tour
     *
     * @param unshuffledCities
     */
    Tour(std::vector<City *> unshuffledCities, bool firstTimeOnly = false);

    /**
     * Getter for Fitness for the Tour.
     *
     * @return Fitness value for the tour.
     */
    double getFitness() { return fitness; }

    /**
     * Getter for the distance for the Tour.
     *
     * @return distance
     */
    double getDistance() { return distance; }

    /**
     * Getter function for tour, get the tour vector.
     * @return vector<City *>& the tour vector
     */
    std::vector<City *> &getTour() { return tour; }

    /**
     * Calculates the fitness level of the tour
     * fitness level of a tour is the inverse of total distance
     * to cover all cities in tour multiply by
     */
    void calculateFitness();

    /**
     * Overload operatorr < for Tour class.
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator<(const Tour& lhs, const Tour& rhs);

    /**
     * Overload insertion operator for Tour class.
     * @param os
     * @param rhs
     * @return
     */
    friend ostream& operator<<(ostream& os, Tour& rhs);

};

#endif //ASSIGNMENT2_TOUR_HPP
