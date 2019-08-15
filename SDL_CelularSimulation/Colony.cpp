#include "Colony.h"
#include <stdio.h>
#include "PRandom.h"
#include <math.h>
#include "Person.h"
#include "World.h"
#include <algorithm>

Colony::Colony(int population, int spawnPositionX, int spawnPositionY, int ID, World* world)
	: mColor(SDL_Color())
	, mPopulation(population)
	, mStartingPosX(spawnPositionX)
	, mStartingPoxY(spawnPositionY)
	, mID(ID)
	, mWorld(world)
{	
	//std::fill(mPeople.begin(), mPeople.end(), nullptr);

	//Set a random color to the colony
	mColor.a = 255;
	mColor.b = PRandom::RandomInt(0, 255);
	mColor.g = PRandom::RandomInt(0, 0);
	mColor.r = PRandom::RandomInt(0, 255);
	printf("Colony color: r:%i g:%i b:%i.\n", mColor.r, mColor.g, mColor.b);


	InitialSpawn();
}

Colony::~Colony()
{
	for (auto pers : mPeople) {
		delete pers;
		pers = nullptr;
	}
}

void Colony::update(double deltaTime)
{
	for (auto pers : mPeople) {
		pers->update(deltaTime);
	}
}

void Colony::render(SDL_Renderer* renderer)
{
	for (auto pers : mPeople) {
		pers->render(renderer);
	}
}

void Colony::addPerson(Person* pers)
{
	printf("Person added with nr.%i spawned at colony with ID %i!\n", (int)mPeople.size(), mID);
	mPeople.push_back(pers);
	mWorld->addPersonToGrid(pers, pers->getPosX(), pers->getPosY());
}

void Colony::InitialSpawn()
{
	int pplToSpawn = mPopulation;

	// x*x rectangle + 2 offset
	int spawnSize = (int)sqrt(pplToSpawn);
	while (pplToSpawn > 0) {
		for (int x = mStartingPosX; x < mStartingPosX + spawnSize; x++) {
			for (int y = mStartingPoxY; y < mStartingPoxY + spawnSize; y++) {

				//Check if there is anyone already at that location
				if (mWorld->getPersonAt(x, y) == nullptr) {
					//Calculate strenghts with random and a multiplier
					int str = std::clamp(PRandom::RandomInt(0, 100) * 1, 0, 100);
					//Every person has a 25% chance to be born with a disease
					bool disease = PRandom::RandomInt(0, 100) > 25 ? false : true;

					Person* person = new Person(x, y, this, str, disease, mWorld);
					addPerson(person);
					pplToSpawn--;
				}
				if (pplToSpawn < 1)
					break;

			}
			if (pplToSpawn < 1)
				break;
		}

		//After every loop increase the spawn location
		spawnSize += 2;
	}

}
