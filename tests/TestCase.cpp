// Let DocTest provide main():
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "SFML/Graphics.hpp"
#include "AffichageDonnees.hh"
#include "bonus.hh"
#include "elementDeJeu.hh"
#include "FeuDepart.hh"
#include "jeu.hpp"
#include "obstacle.hh"
#include "tilemap.hh"
#include "voiture.hpp"

#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <map>
#include <string>

int level[] =
{
    2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
    2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
    2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
    2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
    2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
    2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
    2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
    2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
    2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
    2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
    2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
    2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
    2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
    2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
    2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
};

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

  v1 += 5.0;
  CHECK(v1.getSpeed() == 5);

  v1.speedUp();
  v1.useFuel();
  CHECK(v1.getSpeed() > 5);
  CHECK(v1.getfuel() < v1.getMaxFuel());

  float lastMaxSpeed = v1.getMaxSpeed();
  float lastMaxFuel = v1.getMaxFuel();

  v1.BonusMaxFuel_MaxSpeed();
  CHECK(lastMaxSpeed < v1.getMaxSpeed());
  CHECK(lastMaxFuel < v1.getMaxFuel());
}

TEST_CASE("Test de la classe Voiture") {
    SUBCASE("Test des accesseurs") {
        Voiture maVoiture(100.0, 200.0, 5.0, 10.0, 100.0, 100.0, 3, 3, true);

        CHECK_EQ(maVoiture.getX(), 100.0);
        CHECK_EQ(maVoiture.getY(), 200.0);
        CHECK_EQ(maVoiture.getSpeed(), 5.0);
        CHECK_EQ(maVoiture.getMaxSpeed(), 10.0);
        CHECK_EQ(maVoiture.getfuel(), 100.0);
        CHECK_EQ(maVoiture.getMaxFuel(), 100.0);
        CHECK_EQ(maVoiture.getHp(), 3);
        CHECK_EQ(maVoiture.getMaxHp(), 3);

        maVoiture.BonusMaxFuel_MaxSpeed();
        CHECK_EQ(maVoiture.getMaxSpeed(),11.0);
        CHECK_EQ(maVoiture.getMaxFuel(),120.0);
    }

    SUBCASE("Test de la fonction speedUp et UseFuel") {
        Voiture maVoiture(100.0, 200.0, 0, 10.0, 100.0, 100.0, 3, 3, true);
        maVoiture += 5;

        // On vérifie que la vitesse a augmenté conformément à la logique de la fonction speedUp
        CHECK(maVoiture.getSpeed() == 5.0);

        maVoiture.speedUp();
        CHECK(maVoiture.getSpeed() < 5.0);
        maVoiture.useFuel();
        CHECK(maVoiture.getfuel() < maVoiture.getMaxFuel());
    }
}

TEST_CASE("Jeu"){
  Jeu jeu(level);
  Voiture v1(320, 600, 0, 50, 20, 20, 3, 3,true);
  v1 += 5.0;

  float init_Y = jeu.getPositionMap1();
  jeu.move(v1.getSpeed());
  float new_Y = jeu.getPositionMap1();
  jeu.spawn_bonus();
  jeu.spawn_obstacle();
  CHECK(init_Y < new_Y);
}

TEST_CASE("Test de la classe Jeu") {
    int level[] =
    {
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
    };
    Jeu jeu(level);

    SUBCASE("Test de la fonction de défilement") {
        float initialPositionMap1 = jeu.getPositionMap1();
        float offsetY = 10.0f;
        jeu.move(offsetY);
        CHECK(jeu.getPositionMap1() == (initialPositionMap1 + offsetY));
    }

    SUBCASE("Test de la fonction d'apparition des obstacles") {
        int initialObstaclesCount = jeu.getObstaclesCount();
        jeu.spawn_obstacle();
        CHECK(jeu.getObstaclesCount() <= (initialObstaclesCount + 1));
        CHECK_FALSE(jeu.getObstaclesCount() < initialObstaclesCount);
        CHECK_FALSE(jeu.getObstaclesCount() > (initialObstaclesCount + 1));
    }

    SUBCASE("Test de la fonction d'apparition des bonus") {
        int initialBonusesCount = jeu.getBonusesCount();
        jeu.spawn_bonus();
        CHECK(jeu.getBonusesCount() == (initialBonusesCount + 1));
    }

    SUBCASE("Test de la fonction d'apparition des voitures") {
        int initialCarsCount = jeu.getVoituresObsCount();
        jeu.spawn_obstacle();
        CHECK(jeu.getVoituresObsCount() <= (initialCarsCount + 1));
        CHECK_FALSE(jeu.getVoituresObsCount() < initialCarsCount);
        CHECK_FALSE(jeu.getVoituresObsCount() > (initialCarsCount + 1));
    }
}

TEST_CASE("Test de la classe Bonus") {
    Bonus bonus;

    SUBCASE("Test des valeurs initiales") {
        CHECK(bonus.getTypeBonus() >= 0);
        CHECK(bonus.getTypeBonus() <= 2);
        if(bonus.getTypeBonus() == 0)
          CHECK(bonus.getValue() == 1);
        else
          CHECK(bonus.getValue() == 5);
        CHECK_FALSE(bonus.isUsed());
    }

    SUBCASE("Test de l'utilisation du bonus") {
        bonus.getUsed();
        CHECK(bonus.isUsed());
        CHECK(bonus.getTextureRect() == sf::IntRect(192, 0, 64, 64));
    }
}

TEST_CASE("Test de la classe Obstacle") {
    Obstacle obstacle;

    SUBCASE("Test de la valeur initiale") {
        CHECK(obstacle.getValue() == 1);
    }
}

TEST_CASE("Test de la classe FeuDepart") {
    // Création d'un objet FeuDepart pour les tests
    FeuDepart feuTest;

    SUBCASE("Test de la fonction updateFeuDepart") {
        feuTest.updateFeuDepart();
        CHECK(feuTest.getCurrentState() >= 0);
        CHECK(feuTest.getCurrentState() <= 5);
    }

    SUBCASE("Test de la fonction isReady") {
        CHECK(feuTest.isReady() == false); // initial state
    }

    SUBCASE("Test de la fonction reinitialiserFeu") {
        feuTest.reinitialiserFeu();
        CHECK(feuTest.isReady() == false);
        CHECK(feuTest.getCurrentState() == 0);
    }

    SUBCASE("Test de la fonction getValue") {
        CHECK(feuTest.getValue() == 0);
    }
}