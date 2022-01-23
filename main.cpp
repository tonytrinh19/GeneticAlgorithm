//Name: Quang Tung Trinh & Giwoun Bae
//Student# : A01241898 & A01243484

#include <iostream>
#include "City.hpp"
#include "Tour.hpp"
#include "Population.hpp"
#include <random>

using namespace std;
using u32    = uint_least32_t;
using engine = mt19937;

void populateGroupOfCities(vector<City *> &cities);

Population *generateToursAndAddToPopulation(vector<City *> &cities);

void searchForEliteTour(Population* pop);

void printSummary(int index, Tour* baseTour, Tour* bestTour);


int main() {

    vector<City *> groupOfCities;
    Population *pop      = generateToursAndAddToPopulation(groupOfCities); //evaluate cities' fitness

    searchForEliteTour(pop);

    for (Tour *t: pop->getPopulation()) {
        delete t;
    }
    delete pop;
    for (City *c: groupOfCities) {
        delete c;
    }
    return 0;
}

void searchForEliteTour(Population* pop) {
    Tour* baseTour = pop->getEliteTour();
    Tour* bestTour = baseTour;
    double base_distance = pop->getbaseDistance();
    double best_distance = baseTour->getDistance();
    int index            = 0;

    Tour* previous;
    Population *tempPop;

    while (((best_distance / base_distance) >= improvement_factor) || (index < ITERATIONS)) {
        //crossing
        vector<Tour *> crosses;
        //find the fittest from each set and move elite tour to the front.
        pop->eliteToFront();
        crosses.push_back(pop->getEliteTour()); //this is the elite Tour.
        previous = pop->getEliteTour();
        for (int i = 1; i < POPULATION_SIZE; i++) {
            Tour *childTour = pop->crossesParents();
            crosses.push_back(childTour);
        }

        pop->setPopulation(crosses);
        pop->mutate();

        tempPop = new Population(pop->findSecondBest());

        cout << "****************************************************************************************" << endl;
        if (tempPop->getEliteTour()->getDistance() < previous->getDistance()) {
            cout << "NEW ELITE TOUR FOUND." << endl;
            cout << "Iteration number " << index << " Elite's total distance:"
                 << tempPop->getEliteTour()->getDistance() << endl;
            best_distance = tempPop->getEliteTour()->getDistance();
            cout << "Improvement: " << best_distance/base_distance << endl;
        } else {
            cout << "Iteration number " << index << ":" << endl
                 << "Elite's total distance:               "
                 << pop->getEliteTour()->getDistance() << endl;
            cout << "This iteration's best total distance: "
                 << tempPop->getEliteTour()->getDistance() << endl;
            best_distance = pop->getEliteTour()->getDistance();
            cout << "Improvement compare to base distance: " << best_distance/base_distance << endl;
        }

        index++;
        bestTour = pop->getEliteTour();
    }
    printSummary(index, baseTour, bestTour);
}

void printSummary(int index, Tour* baseTour, Tour* bestTour) {
    double best_distance = bestTour->getDistance();
    double base_distance = baseTour->getDistance();

    cout << ">>>>>>>>>>>>>>>>>> SUMMARY <<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    if ((best_distance / base_distance) < improvement_factor){
        cout << "We have achieved target improvement factor of "
             << (1 - improvement_factor) * 100 <<"%"<< endl;
    } else {
        cout << "We have NOT achieved target improvement factor of "
             << (1 - improvement_factor) * 100 <<"%"<< endl;
    }

        cout << "Best distance:            " << best_distance << endl;
        cout << "Base distance:            " << base_distance << endl;
        cout << "Our improvement:          " << (1 - best_distance/base_distance) * 100 << "%"<<endl;
        cout << "Number of iterations run: " << index << endl;
        //output of route taken
        cout << "Best tour route: " << endl;
        cout << *bestTour << endl;
        cout << "*******************************************************" << endl;
        //output of base route.
        cout << "Base tour route: " << endl;
        cout << *baseTour << endl;
        cout << "*******************************************************" << endl;

}

Population *generateToursAndAddToPopulation(vector<City *> &cities) {
    populateGroupOfCities(cities); //create master list of cities

    // Tour contains vector of pointers to cities
    vector<Tour *> listOfTours;
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        Tour *tour = new Tour(cities, true);
        listOfTours.push_back(tour);
    }

    return new Population(listOfTours);
}

void populateGroupOfCities(vector<City *> &cities) {
    random_device os_seed;
    const u32 seed = os_seed();
    engine generator(seed);
    // inclusive [0, 1000]
    uniform_int_distribution<u32> distributeCoordinates(0, MAP_BOUNDARY);

    for (int i = 0; i < CITIES_IN_TOUR; ++i) {
        City *city = new City(make_pair(distributeCoordinates(generator), distributeCoordinates(generator)));
        cities.push_back(city);
    }
}