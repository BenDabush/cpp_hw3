#include "player.hpp"

using namespace ariel;

// Constructor that takes the player's name
Player::Player(std::string playerName) : name(playerName), win_count(0), player_deck(std::vector<Card>()), won_cards(std::vector<Card>()), use_cards(std::vector<Card>()) {
}


// Default constructor
Player::Player() {
    name = "moshe";
}

std::string Player::getName() const{
    return name;
}

void Player::addWinTowin_count(){
    win_count++;
}

int Player::getwin_count() const{
    return win_count;
}

std::vector<Card> Player::getWon_cards(){
    return won_cards;
}

std::vector<Card> Player::getuse_cards() const{
    return use_cards;
}

void Player::setuse_cards(Card &card){
    use_cards.emplace_back(card);
}

void Player::addCardToDeck(Card &card){
    player_deck.emplace_back(card);
}

void Player::addCardToWinDeck(Card &card){
    won_cards.emplace_back(card);
}

Card Player::playCard(){
    Card player_card = player_deck[player_deck.size()-1];
    player_deck.pop_back();
    return player_card;
}

// Print the number of cards left in the player's deck
int Player::stacksize() const {
    return player_deck.size();
}

// Print the number of cards the player has won
int Player::cardesTaken() const {
    return won_cards.size();
}
