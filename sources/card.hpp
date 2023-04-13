#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

namespace ariel {

    enum class Shape { 
        CLUBS,
        DIAMONDS,
        HEARTS,
        SPADES
    };

    class Card {
    private:
        int m_value;
        Shape m_shape;

    public:
        Card(int value = 0, Shape shape = Shape::CLUBS);
        void print();
        int getValue();
        Shape getShape();
        std::string getShapeString();
        bool operator<(const Card& other) const;
        bool operator==(const Card& other) const;
        bool operator!=(const Card& other) const;
    };
}

#endif
