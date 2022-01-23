#include "Population.hpp"

Population::Population(vector<Tour *> pop) : population(std::move(pop)) {
    baseDistance = population.at(0)->getDistance();
    elite        = population.at(0);
    // Finds the baseDistance.
    for (unsigned long i = 1; i < population.size(); i++) {
        if (population.at(i)->getDistance() < baseDistance) {
            baseDistance = population.at(i)->getDistance();
            elite = population.at(i);
        }
    }
}

vector<Tour *>& Population::getPopulation() {
    return population;
}

Tour *Population::getEliteTour() {
    return elite;
}

vector<Tour*> Population::findSecondBest() {
    //copy population vector into new vector but exclude elite
    vector<Tour*> result;
    for (unsigned long i = 1; i < (population.size() -1) ; i++) {
        result.push_back(population.at(i));
    }
    return result;
}

void Population::eliteToFront() {
    for (unsigned long i = 1; i < population.size() - 1; i++) {
        if (population.at(i)->getFitness() >= elite->getFitness()) {
            iter_swap(population.begin(), population.begin() + i);
            elite = population.at(i);
        }
    }
}

Tour *Population::selectRandomTour() {
    random_device os_seed;
    const uint_least32_t seed = os_seed();
    engine generator(seed);
    uniform_int_distribution<uint_least32_t> distributeCoordinates(1, CITIES_IN_TOUR - 1);

    int randomNumber = (int) distributeCoordinates(generator);
    return population.at(randomNumber);
}

Tour *findTheFittest(vector<Tour *> &list) {
    Tour *result = list.at(0);

    for (Tour *t: list) {
        if (t->getFitness() > result->getFitness()) {
            result = t;
        }
    }
    return result;
}

bool checkDuplicateCity(vector<City *> &list, City *city) {
    bool result = false;
    for (City *one: list) {
        if (*one == city) {
            result = true;
        }
    }
    return result;
}

Tour *crossingParent_helper(Tour *parent1, Tour *parent2) {
    Tour *childTour;
    int sizeOfParent = (int) parent1->getTour().size();

    random_device os_seed;
    const uint_least32_t seed = os_seed();
    engine generator(seed);
    uniform_int_distribution<uint_least32_t> randomIndex(0, sizeOfParent - 1);

    int index = (int) randomIndex(generator);
    vector<City *> listOfCities;

    for (int i = 0; i <= index; i++) {
        listOfCities.push_back(parent1->getTour().at(i));
    }

    for (int i = 0; i < sizeOfParent; i++) {
        if (!checkDuplicateCity(listOfCities, parent2->getTour().at(i))) {
            listOfCities.push_back(parent2->getTour().at(i));
        }
    }

    childTour = new Tour(listOfCities);
    return childTour;
}

void Population::setPopulation(vector<Tour *> &newMergePopulation) {
    int index = 0;
    for (Tour *newOnes: newMergePopulation) {
        population.at(index) = newOnes;
        index++;
    }
}

void Population::mutate() {
    // randomly select 30 percent of tours to mutate except elite.
    random_device os_seed;
    const uint_least32_t seed = os_seed();
    engine generator(seed);
    int index;
    for (int j = 0; j < POPULATION_SIZE * PERCENTAGE; j++) {
        uniform_int_distribution<uint_least32_t> randIndex(1, POPULATION_SIZE - 1);
        index = (int) randIndex(generator);

        //for these random cities, we are going to roll the dice
        //if the the roll the dice is 15% mutation MUTATION_RATE, then swap with the next.
        for (int i = 0; i < CITIES_IN_TOUR; i++) {
            // Randomize number from 0 to 100
            uniform_int_distribution<uint_least32_t> mutationValue(0, 100);
            if (mutationValue(generator) < MUTATION_RATE) {
                vector<City *> &tour = population.at(index)->getTour();
                if (i == (CITIES_IN_TOUR - 1)) {
                    iter_swap(tour.begin(),
                              tour.begin() + (CITIES_IN_TOUR - 1));
                } else {
                    iter_swap(tour.begin() + i,
                              tour.begin() + i + 1);
                }
            }
        }
    }
}

Tour *Population::crossesParents() {
    //randomly select 5 tours from the pop.
    Tour*          parent1;
    Tour*          parent2;
    vector<Tour *> set1;
    vector<Tour *> set2;

    for (int i = 0; i < PARENT_POOL_SIZE; i++) {
        set1.push_back(selectRandomTour());
        set2.push_back(selectRandomTour());
    }

    //find the fittest.
    parent1 = findTheFittest(set1);
    parent2 = findTheFittest(set2);

    //crossing the parents with random index.
    return crossingParent_helper(parent1, parent2);
}




