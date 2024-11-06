#include "randomProcedures.h"
#include <random>

std::random_device randomDevice;
std::mt19937 rng(randomDevice());

int randInt(int lowerBound, int upperBound) {
    std::uniform_int_distribution<std::mt19937::result_type> dist(lowerBound, upperBound);

    return dist(rng);
}

bool randBool() {
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 2);

    return dist(rng) == 1;
}

unsigned int randChoice(int upperBound) {
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, upperBound);

    return dist(rng);
}

unsigned int randPercent() {
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

    return dist(rng);
}