#include "Tour.hpp"
#include "Population.hpp"
#include <cmath>
#include <ostream>


void Tour::calculateFitness() {
    for (int index = 0; index < static_cast<int>(tour.size() - 1); ++index) {
        double xDifference = static_cast<int>(tour.at(index + 1)->getX()) - static_cast<int>(tour.at(index)->getX());
        double yDifference = static_cast<int>(tour.at(index + 1)->getY()) - static_cast<int>(tour.at(index)->getY());
        double num1        = pow(xDifference, SQUARE);
        double num2        = pow(yDifference, SQUARE);

        distance += sqrt(num1 + num2);
    }
    // Last city goes back to the starting city.
    double xDifference = static_cast<int>(tour.at(0)->getX()) - static_cast<int>(tour.at(tour.size() - 1)->getX());
    double yDifference = static_cast<int>(tour.at(0)->getY()) - static_cast<int>(tour.at(tour.size() - 1)->getY());
    double num1        = pow(xDifference, SQUARE);
    double num2        = pow(yDifference, SQUARE);
    distance += sqrt(num1 + num2);

    fitness = 1 / distance * SCALAR_VALUE;
}

Tour::Tour(std::vector<City *> unshuffledCities, bool firstTimeOnly) {
    if (firstTimeOnly) {
        shuffle(unshuffledCities.begin(), unshuffledCities.end(), engine(random_device()()));
    }
    for (City *c: unshuffledCities) {
        tour.push_back(c);
    }
    calculateFitness();
}

ostream &operator<<(ostream &os, Tour &rhs) {
    vector<City*> currentTour = rhs.tour;
    os << "Start tour: ";
    for (City* city: rhs.tour) {
        os << *city << " -> ";
    }
    os << *rhs.tour.at(0);
    return os;
}

bool operator<(const Tour &lhs, const Tour &rhs) {
    return (lhs.distance < rhs.distance)&&(lhs.fitness > rhs.fitness);
}




