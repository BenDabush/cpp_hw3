#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "card.hpp"

namespace ariel {
    class Player {
        private:
            std::string name;
            int win_count;
            std::vector<Card> player_deck;  // Player's deck of cards
            std::vector<Card> won_cards;  // A deck of cards that a player has won
            std::vector<Card> use_cards;
        
        public:
            Player(std::string playerName);
            Player();
            void addCardToDeck(Card &card);
            void addCardToWinDeck(Card &card);
            std::string getName() const;
            int getwin_count() const;
            void addWinTowin_count();
            std::vector<Card> getWon_cards();
            std::vector<Card> getuse_cards() const;
            void setuse_cards(Card &card);
            Card playCard();
            int stacksize() const; // prints the amount of cards left.
            int cardesTaken() const; // prints the amount of cards this player has won. 
    };
}

#endif

