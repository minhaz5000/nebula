#include "ComplexNumber.h"

ComplexNumber::ComplexNumber(float real, float imag) : value(real, imag) {}

float ComplexNumber::getReal() const { return value.x; }
float ComplexNumber::getImag() const { return value.y; }

ComplexNumber ComplexNumber::operator+ (const ComplexNumber& other) const
{
    return ComplexNumber(value.x + other.value.x, value.y + other.value.y);
}

ComplexNumber ComplexNumber::operator- (const ComplexNumber& other) const 
{
    return ComplexNumber(value.x - other.value.x, value.y - other.value.y);
}

ComplexNumber ComplexNumber::operator* (const ComplexNumber& other) const 
{
    return ComplexNumber(value.x * other.value.x - value.y * other.value.y, value.x * other.value.y + value.y * other.value.x);
}

ComplexNumber ComplexNumber::operator^ (int power) const 
{
    ComplexNumber result(1.0f, 0.0f);
    for (int i = 0; i < power; ++i) {
        result = result * (*this);
    }
    return result;
}

bool ComplexNumber::operator== (const ComplexNumber& other) const
{
    return value == other.value;
}

ComplexNumber ComplexNumber::getConjugate() const
{
    return ComplexNumber(value.x, -value.y);
}

float ComplexNumber::getMagnitude() const
{
    return glm::length(value);
}

ComplexNumber ComplexNumber::abso() const {
    double r = (getReal() < 0) ? -getReal() : getReal();
    double i = (getImag() < 0) ? -getImag() : getImag();
    return ComplexNumber(r, i);
}

ComplexNumber ComplexNumber::getCopy() const {
    return ComplexNumber(getReal(), getImag());
}

// negative, (a+bi) becomes (-a-bi)
ComplexNumber ComplexNumber::neg() const {
    return ComplexNumber(-(getReal()), -(getImag()));
}

// inverse, (a+bi) becomes (b+ai)
ComplexNumber ComplexNumber::inv() const {
    return ComplexNumber(getImag(), getReal());
}


