#include "doctest.h"
#include <stdexcept>

#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
using namespace ariel;

TEST_CASE("Player constructor test") {
    SUBCASE("Create player with name") {
        Player p1("Alice");
        CHECK(p1.stacksize() == 0);
        CHECK(p1.cardesTaken() == 0);
    }

    SUBCASE("Create default player") {
        Player p2;
        CHECK(p2.stacksize() == 0);
        CHECK(p2.cardesTaken() == 0);
    }
}

TEST_CASE("Testing game playAll and playTurn functions") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);

    SUBCASE("playAll function") {
        CHECK_NOTHROW(game.playAll());
    }

    SUBCASE("playTurn function") {
        CHECK_NOTHROW(game.playTurn());
    }
}

// Checking that all the functions of the game do not throw an error
TEST_CASE("Testing game functions after playAll function") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);


    SUBCASE("Print winner") {
        game.playAll();
        CHECK_NOTHROW(game.printWiner());
    }

    SUBCASE("Print log") {
        game.playAll();
        CHECK_NOTHROW(game.printLog());
    }

    SUBCASE("Print stats") {
        game.playAll();
        CHECK_NOTHROW(game.printStats());
    }

    SUBCASE("Print last turn") {
        game.playAll();
        CHECK_NOTHROW(game.printLastTurn());
    }
}

TEST_CASE("Testing game functions after playTurn function") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);

    SUBCASE("Print log") {
        game.playTurn();
        CHECK_NOTHROW(game.printLog());
    }

    SUBCASE("Print stats") {
        game.playTurn();
        CHECK_NOTHROW(game.printStats());
    }

    SUBCASE("Print last turn") {
        game.playTurn();
        CHECK_NOTHROW(game.printLastTurn());
    }
}

TEST_CASE("Testing Player cardesTaken") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);

    SUBCASE("Testing the sum of cardes taken by the two players after playing all turns") {
        game.playAll();
        CHECK(p1.cardesTaken() + p2.cardesTaken() >= 26);
        CHECK(p1.cardesTaken() + p2.cardesTaken() <= 52);
    }

    SUBCASE("Testing Players stacksize after playing some turns") {
        // Playing 7 turns should reduce the stacksize of each player by 7
        for (int i = 0; i < 7; i++) {
            game.playTurn();
        }
        CHECK(p1.stacksize() <= 26 - 7);
        CHECK(p2.stacksize() <= 26 - 7);
    }

    SUBCASE("Testing Players cardesTaken after playing some turns") {
        // Playing 7 turns should reduce the stacksize of each player by 7
        for (int i = 0; i < 7; i++) {
            game.playTurn();
        }
        CHECK(p1.cardesTaken() + p2.cardesTaken() >= 7);
        CHECK(p1.cardesTaken() >= 0);
        CHECK(p1.cardesTaken() <= 26);        
        CHECK(p2.cardesTaken() >= 0);
        CHECK(p2.cardesTaken() <= 26);
    }
}
