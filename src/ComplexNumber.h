#pragma once

#include <glm/glm.hpp>

class ComplexNumber {
private:
    glm::vec2 value;

public:
    ComplexNumber(float real, float imag);

    float getReal() const;
    float getImag() const;

    ComplexNumber operator+ (const ComplexNumber& other) const;
    ComplexNumber operator- (const ComplexNumber& other) const;
    ComplexNumber operator* (const ComplexNumber& other) const;
    ComplexNumber operator^ (int power) const;
    bool operator== (const ComplexNumber& other) const;

    ComplexNumber getConjugate() const;
    float getMagnitude() const;
};

