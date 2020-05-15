//
// Created by perci on 2020/5/15.
//

#ifndef CELLGAME_RAND_INT_H
#define CELLGAME_RAND_INT_H
#include <random>
class Rand_int {
public:
    Rand_int(int low, int high) :dist{low,high} { }
    int operator()() { return dist(re); } // draw an int
private:
    std::default_random_engine re;
    std::uniform_int_distribution<> dist;
};
#endif //CELLGAME_RAND_INT_H
