#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "player.hpp"
#include "card.hpp"

namespace ariel {

    class Game {
    private:
        Player &p1;
        Player &p2;
        int num_turns;
        std::vector<Card> game_deck;
        std::vector<Card> card_at_stake;

        void buildDeck();  // Building a deck of cards
        void shuffleDeck();  // shuffling a pack of cards
        void DealingCards(); // Dealing cards to players

    public:
        Game(Player &p1, Player &p2);
        void playTurn();  // played one turn in the game
        void playAll();  // playes the game untill the end
        void printWiner();  // prints the name of the winning player
        void printLog();  // prints all the turns played one line per turn (same format as game.printLastTurn())
        void printStats();  // for each player prints basic statistics: win rate, cards won, <other stats you want to print>. Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )
        void printLastTurn();  // print the last turn stats. For example:
                                                    // Alice played Queen of Hearts Bob played 5 of Spades. Alice wins.
                                                    // Alice played 6 of Hearts Bob played 6 of Spades. Draw. Alice played 10 of Clubs Bob played 10 of Diamonds. draw. Alice played Jack of Clubs Bob played King of Diamonds. Bob wins.
        Card playTurnTakeCard(Player &p);
        void onePlayerWin(Player &p);
        void twePlayerWin(Player &p1, Player &p2);

    };

}

#endif
