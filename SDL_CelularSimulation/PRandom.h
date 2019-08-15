#pragma once
#include <random>
//randomizer
class PRandom {
public:
	static int RandomInt(int min, int max) {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> randomInt(min, max);
		return randomInt(rng);
	}
private:
	PRandom(){}
};