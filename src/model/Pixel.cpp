#include "Pixel.h"

Pixel::Pixel(const bool& p_isBlack)
    : m_isBlack(p_isBlack)
{
    ;
}

Pixel::~Pixel(void)
{
    ;
}

Pixel::Pixel(const Pixel& p_other)
{
    *this = p_other;
}

Pixel& Pixel::operator=(const Pixel& p_other)
{
    this->m_isBlack = p_other.m_isBlack;
    return *this;
}
