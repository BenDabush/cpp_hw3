#include "card.hpp"

namespace ariel {

    Card::Card(int value, Shape shape) {
        m_value = value;
        m_shape = shape;
    }

    void Card::print() {
        std::string shapeStr = Card::getShapeString();

        std::cout << "Value: " << m_value << ", Shape: " << shapeStr << std::endl;
    }

    int Card::getValue() {
        return m_value;
    }

    Shape Card::getShape() {
        return m_shape;
    }

    std::string Card::getShapeString() {
        std::string shapeStr;

        switch (m_shape) {
            case Shape::CLUBS:
                shapeStr = "Clubs";
                break;
            case Shape::DIAMONDS:
                shapeStr = "Diamonds";
                break;
            case Shape::HEARTS:
                shapeStr = "Hearts";
                break;
            case Shape::SPADES:
                shapeStr = "Spades";
                break;
        }
        return shapeStr;
    }

    bool Card::operator<(const Card& other) const {
        if (m_value == 1 && other.m_value == 2) {
            return true;
        }
        else if (m_value == 2 && other.m_value == 1) {
            return false;
        }
        else {
            return m_value < other.m_value;
        }
    }

    bool Card::operator==(const Card& other) const {
        if (m_value != other.m_value) {
            return false;
        }
        else {
            return true;
        }
    }

    bool Card::operator!=(const Card& other) const {
        if (m_value == other.m_value) {
            return false;
        }
        else {
            return true;
        }
    }
}
