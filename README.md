To run the app, clone the repository and reload CMake Project to generate cmake-build-debug folder.

All options related to the formula and condition of the algorithm can be changed in "Population.hpp"



Default values for the conditions:

| Value | Data Type | Default Value | Description
|-----------|:-----------:|:-----------:| -----------:|    
| PARENT_POOL_SIZE | Integer | 5 | Number of candidates to be selected as parent for mutation |
| MUTATION_RATE | Integer | 30 | Mutation rate |
| CITIES_IN_TOUR | Integer | 0 | the number of cities we are using in each simulation |
| POPULATION_SIZE | Integer | 32 | the number of candidate tours in our population |
| MAP_BOUNDARY | Integer | 1000 | Random integer generator, size of map |
| improvement_factor | Double | 0.75 | Improvement factor, indicate desired improvement, 0.75 indicates an expectation of 25% improvement our total Tour distance |
| ITERATIONS | Integer | 1000 | Number of iterations to run genetic algorithm |
| PERCENTAGE | Double | 0.30 | Percentage to take from population to mutate |
| SCALAR_VALUE | Unsigned Integer | 100000 | Scalar value |


Example of the result:
![image](Summary.png)