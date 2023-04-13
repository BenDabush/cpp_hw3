/***
 * https://www.geeksforgeeks.org/shuffle-a-deck-of-cards-3/
*/

#include "game.hpp"
#include <ctime>

namespace ariel {

    Game::Game(Player &p1, Player &p2): p1(p1), p2(p2), num_turns(0)
    {   
        buildDeck();
        shuffleDeck();
        DealingCards();
    }

    void Game::buildDeck()
    {
        for (int i = 1; i <= 13; ++i) {
            game_deck.emplace_back(i, Shape::CLUBS);
            game_deck.emplace_back(i, Shape::DIAMONDS);
            game_deck.emplace_back(i, Shape::HEARTS);
            game_deck.emplace_back(i, Shape::SPADES);
        }
    }

    void Game::shuffleDeck() {
        std::srand(std::time(0));
        for (unsigned long i = game_deck.size() - 1; i > 0; i--) {
            unsigned long j = (unsigned long)std::rand() % (i + 1);
            std::swap(game_deck[i], game_deck[j]);
        }
    }

    void Game::DealingCards()
    {
        unsigned long n = game_deck.size() / 2;
        for (unsigned long i = 0; i < n; i++) {
            p1.addCardToDeck(game_deck[i]);
            p2.addCardToDeck(game_deck[i+n]);
        }
    }
    
    Card Game::playTurnTakeCard(Player &p) {
        Card p_card = p.playCard(); // player 1 plays a card
        card_at_stake.push_back(p_card); // the played cards are added to the game's deck
        return p_card;
    }

    void Game::onePlayerWin(Player &p) {
        while (card_at_stake.size() > 0) {
            p.addCardToWinDeck(card_at_stake[card_at_stake.size() - 1]); // the played cards are added to the game's deck
            card_at_stake.pop_back();
        }
    }

    void Game::twePlayerWin(Player &p1, Player &p2) {
        while (card_at_stake.size() > 1) {
            p1.addCardToWinDeck(card_at_stake[card_at_stake.size() - 1]); // the played cards are added to the game's deck
            card_at_stake.pop_back();
            p2.addCardToWinDeck(card_at_stake[card_at_stake.size() - 1]); // the played cards are added to the game's deck
            card_at_stake.pop_back();
        }
    }

    void Game::playTurn() {
        if (p1.stacksize() == 0) {
            throw std::logic_error("Game is already over");
        }
        if (&p1 == &p2) {
            throw std::invalid_argument("Both players cannot be the same.");
        }

        num_turns++;

        Card p1_card = playTurnTakeCard(p1);
        p1.setuse_cards(p1_card);
        Card p2_card = playTurnTakeCard(p2);
        p2.setuse_cards(p2_card);

        while ((p1_card == p2_card) && (p1.stacksize() >= 2))
        {
            playTurnTakeCard(p1);  // player 1 puts one cards face down
            playTurnTakeCard(p2);  // player 2 puts one cards face down
 
            p1_card = playTurnTakeCard(p1);  // player 1 plays a card
            p1.setuse_cards(p1_card);
            p2_card = playTurnTakeCard(p2);  // player 2 plays a card
            p2.setuse_cards(p2_card);
        }

        if (p1_card == p2_card) {
            if (p1.stacksize() == 1) {
                playTurnTakeCard(p1);  // player 1 puts one cards face down
                playTurnTakeCard(p2);  // player 2 puts one cards face down
            }
            twePlayerWin(p1, p2);           
        } else if (p2_card < p1_card) {
            onePlayerWin(p1);
            p1.addWinTowin_count();
        } else {
            onePlayerWin(p2);
            p2.addWinTowin_count();
        }
    }
    
    void Game::playAll()
    {
        if (p1.stacksize() == 0) {
            throw std::logic_error("Game is already over");
        }
        while (p1.stacksize() > 0) {
            playTurn();
        }
    }
    
    void Game::printWiner()
    {
        if (p1.getWon_cards().size() > p2.getWon_cards().size()) {
            std::cout << p1.getName() << " wins!" << std::endl;
        } else if (p1.getWon_cards().size() < p2.getWon_cards().size()) {
            std::cout << p2.getName() << " wins!" << std::endl;
        } else {
            std::cout << "It's a draw!" << std::endl;
        }
    }
    
    void Game::printLog()
    {
        std::vector<Card> p1_use_card = p1.getuse_cards();
        std::vector<Card> p2_use_card = p2.getuse_cards();
        Card p1_card;
        Card p2_card;
        for (unsigned long i = 0; i < p1_use_card.size(); i++)
        {
            p1_card = p1_use_card[i];
            p2_card = p2_use_card[i];

            std::cout << p1.getName() << " played " << p1_card.getValue() << " of " << p1_card.getShapeString() << ", ";
            std::cout << p2.getName() << " played " << p2_card.getValue() << " of " << p2_card.getShapeString() << ". "; 

            if (p2_card < p1_card) {
                std::cout << p1.getName() << " Wins." << std::endl; 
            }
            else if (p1_card < p2_card) {
                std::cout << p2.getName() << " Wins." << std::endl; 
            }
            else {
                std::cout << "Drow. "; 
            }
        }
        std::cout << std::endl;
        
    }
    
    void Game::printStats()
    {
        std::cout << "Player Stats:\n";
        for (const Player &player : {p1, p2}) {
        std::cout << "Player " << player.getName() << ":" << std::endl;
        std::cout << "\tNumber of wins: " << player.getwin_count() << std::endl;
        if (num_turns > 0){
            std::cout << "\tWin Rate: " << player.getwin_count()/(float)num_turns << std::endl;
        }
        std::cout << "\tCards face up: " << p1.getuse_cards().size() << std::endl;
        std::cout << "\tCards face down: " << p1.getuse_cards().size() - (unsigned long)num_turns << std::endl;
        std::cout << "\tCards Won: " << player.cardesTaken() << std::endl;
        }

        std::cout << std::endl;

        std::cout << "General statistics:" << std::endl;
        std::cout << "\tNumber of Turns: " << num_turns << std::endl;
        std::cout << "\tNumber of Drow: " << p1.getuse_cards().size() - (unsigned long)num_turns << std::endl;
        if (num_turns > 0)
        {
            std::cout << "\tDraw Rate: " << (p1.getuse_cards().size() - (unsigned long)num_turns)/(float)p1.getuse_cards().size() <<std::endl;
        }
        
        
    }
    
    void Game::printLastTurn()
    {
        if (num_turns > 0)
        {
            std::vector<Card> p1_use_card = p1.getuse_cards();
            std::vector<Card> p2_use_card = p2.getuse_cards();

            unsigned long last_tie = p2_use_card.size() - 1;

            Card p1_card = p1_use_card[last_tie];
            Card p2_card = p2_use_card[last_tie];

            if (last_tie == 0)
            {
                std::cout << p1.getName() << " played " << p1_card.getValue() << " of " << p1_card.getShapeString() << ", ";
                std::cout << p2.getName() << " played " << p2_card.getValue() << " of " << p2_card.getShapeString() << ". "; 

                if (p2_card < p1_card) {
                    std::cout << p1.getName() << " Wins." << std::endl; 
                }
                else if (p1_card < p2_card) {
                    std::cout << p2.getName() << " Wins." << std::endl; 
                }
            }
            else
            {
                if (p1_use_card[last_tie - 1] == p2_use_card[last_tie - 1])
                {
                    last_tie--;
                    Card p1_card = p1_use_card[last_tie];
                    Card p2_card = p2_use_card[last_tie];

                    while ((p1_card == p2_card) && (last_tie >= 0))
                    {
                        last_tie--;
                        Card p1_card = p1_use_card[last_tie];
                        Card p2_card = p2_use_card[last_tie];
                    }

                    for (unsigned long i = last_tie; last_tie < p1_use_card.size(); i++)
                    {
                        p1_card = p1_use_card[i];
                        p2_card = p2_use_card[i];

                        std::cout << p1.getName() << " played " << p1_card.getValue() << " of " << p1_card.getShapeString() << ", ";
                        std::cout << p2.getName() << " played " << p2_card.getValue() << " of " << p2_card.getShapeString() << ". "; 

                        if (p2_card < p1_card) {
                            std::cout << p1.getName() << " Wins." << std::endl; 
                        }
                        else if (p1_card < p2_card) {
                            std::cout << p2.getName() << " Wins." << std::endl; 
                        }
                        else {
                            std::cout << "Drow. "; 
                        }
                    }
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << p1.getName() << " played " << p1_card.getValue() << " of " << p1_card.getShapeString() << ", ";
                    std::cout << p2.getName() << " played " << p2_card.getValue() << " of " << p2_card.getShapeString() << ". "; 

                    if (p2_card < p1_card) {
                        std::cout << p1.getName() << " Wins." << std::endl; 
                    }
                    else if (p1_card < p2_card) {
                        std::cout << p2.getName() << " Wins." << std::endl; 
                    }
                }
            }
        }
        else{
            std::cout <<  "There was no turn yet" << std::endl;
        }
    }
}
