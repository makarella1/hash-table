#include "jedi.h"
#include <string>
#include <random>

const int JEDIS_COUNT = 10;
const int LIGHTSABER_COLORS_COUNT = 9;
const int MAX_PADAWANS = 2;

const std::string jedis[JEDIS_COUNT] = {
    "Yoda",
    "Mace Windu",
    "Plo Koon",
    "Kit Fisto",
    "Count Dooku",
    "Obi-Wan Kenobi",
    "Anakin Skywalker",
    "Luke Skywalker",
    "Ben Solo",
    "Grogu",
};

const std::string lightsaberColors[LIGHTSABER_COLORS_COUNT] = {
    "Black",
    "Blue",
    "Light Blue",
    "Green",
    "Yellow-Green",
    "Purple",
    "Red",
    "White",
    "Yellow"};

Jedi::Jedi()
{
  std::random_device rd;
  std::mt19937 generator(rd());

  name = jedis[generator() % JEDIS_COUNT];
  lightsaberColor = lightsaberColors[generator() % LIGHTSABER_COLORS_COUNT];
  numOfPadawans = (generator() % MAX_PADAWANS) + 1;
}