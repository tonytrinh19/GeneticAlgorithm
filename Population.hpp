#ifndef ASSIGNMENT2_POPULATION_HPP
#define ASSIGNMENT2_POPULATION_HPP

#include "Tour.hpp"
#include <vector>

// Number of candidates to be selected as parent for mutation
#define PARENT_POOL_SIZE 5
// Mutation rate
#define MUTATION_RATE    30

const int startingIndex         = 0;
// the number of cities we are using in each simulation.
const int CITIES_IN_TOUR        = 32;
// the number of candidate tours in our population.
const int POPULATION_SIZE       = 32;
// Random integer generator.
const int MAP_BOUNDARY          = 1000;
// Improvement factor, indicate desired improvement, 0.75 indicates
// an expectation of 25% improvement our total Tour distance.
const double improvement_factor = 0.75;
// Number of iterations to run genetic algorithm
const int ITERATIONS            = 1000;
// Percentage to take from population to mutate
const double PERCENTAGE         = 0.30;
// Scalar value
const unsigned int SCALAR_VALUE = 100000;
// ^2
const double SQUARE             = 2.0;

using namespace std;

class Population {
private:
    Tour *elite;
    double baseDistance;
    vector<Tour *> population;

    /**
     * Pick a random tour in the population, excluding the elite tour.
     * @return Tour* Tour picked
     */
    Tour *selectRandomTour();

public:
    /**
     * Constructor for Population
     * @param pop list of Tours.
     */
    Population(vector<Tour *> pop);

    /**
     * Returns the Tour pointer with Elite fitness.
     *
     * @return Tour pointer.
     */
    Tour *getEliteTour();

    /**
     * Get the population vector.
     * @return
     */
    vector<Tour *> &getPopulation();

    /**
     * Getters for base distance.
     *
     * @return base distance
     */
    double getbaseDistance() const { return baseDistance; }

    /**
     * Moves the elite tour to the front of the population.
     * Swaps with the first tour in the list.
     */
    void eliteToFront();

    /**
     * Performs crossing on two Tour. Generate a random index,
     * from parent Tour 1, copy from first element to and include
     * the index element to the child Tour, elements that's not in
     * child Tour yet will be copied from parent Tour 2.
     * @return Tour* child Tour
     */
    Tour *crossesParents();

    /**
     * Fill new Population with new merged(child) Tour.
     * @param newMergePopulation new population, as a vector of Tours
     */
    void setPopulation(vector<Tour *> &newMergePopulation);

    /**
     * Performs mutation on the Population.
     */
    void mutate();

    /**
     * Find the fittest tour in a list of tours.
     * @param list vector<Tour *> list of tours
     * @return the tour with highest fitness level in the given tour list
     */
    friend Tour *findTheFittest(vector<Tour *> &list);

    /**
     * Helper function for crossesParent function
     * @param parent1 Tour* Mother Tour
     * @param parent2 Tour* Father Tour
     * @return Tour* child Tour
     */
    friend Tour *crossingParent_helper(Tour *parent1, Tour *parent2);

    /**
     * Checks whether the city is in another list of cities.
     * @param list vector<City*> list of City
     * @param city City* city to check
     * @return bool true if the city is in the list of cities, else return false
     */
    friend bool checkDuplicateCity(vector<City *> &list, City *city);

    vector<Tour *> findSecondBest();

};


#endif //ASSIGNMENT2_POPULATION_HPP
