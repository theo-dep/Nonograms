#pragma once

class Pixel
{
public:
    Pixel(const bool& p_isBlack = false);
    virtual ~Pixel(void);

    Pixel(const Pixel& p_other);
    Pixel& operator=(const Pixel& p_other);

    const bool& isBlack(void) const { return m_isBlack; }

protected:
    bool m_isBlack;
};
