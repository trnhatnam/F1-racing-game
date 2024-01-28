// Let DocTest provide main():
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "SFML/Graphics.hpp"
#include "bonus.hh"
#include "elementDeJeu.hh"
#include "obstacle.hh"
#include "voiture.hpp"

#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <map>
#include <string>


TEST_CASE("Construct a car"){
  Voiture v1(320, 600, 0, 50, 20, 20, 3, 3,true);
  Voiture v2(320 + 2*64.f, -64, 0, 50, 20, 20, 3, 3, false);

  const float minX = 256.f;
  const float maxX = 640.f;

  CHECK(v1.getUser() == true);
  CHECK(v2.getUser() == false);
  CHECK(v1.getHp() == 3);
  CHECK(v1.getMaxHp() == 3);
  CHECK(v1.getfuel() == 20);
  CHECK(v1.getMaxFuel() == 20);
  CHECK(v1.getSpeed() == 0);
  CHECK(v1.getMaxSpeed() == 50);
  CHECK(v1.getX() < maxX);
  CHECK(v1.getX() > minX);
  CHECK(v2.getX() < maxX);
  CHECK(v2.getX() > minX);
  CHECK(v1.getY() == 600);
}
