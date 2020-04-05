#pragma once

#include "Pixel.h"

#include "puzzle.h"

#include <vector>
#include <list>

class Grid
{
public:
    Grid(void);
    virtual ~Grid(void);

    void init(const Puzzle::Config& p_config);

protected:
    virtual void initMap(const Puzzle::Config& p_config);
    virtual void initRowHelper(void);
    virtual void initColHelper(void);

    static std::list<uint8_t> initLineHelper(const std::vector<Pixel>& p_line);

protected:
    std::vector<std::vector<Pixel>> m_map; //! row<col<Pixel>>
    std::vector<std::vector<Pixel>> m_rMap; //! reverse map col<row<Pixel>>
    std::list<std::list<uint8_t>> m_rowHelper; //! number of black by rows
    std::list<std::list<uint8_t>> m_colHelper; //! number of black by columns

private:
    // disable copy and assignment
    Grid(const Grid&) = delete;
    Grid& operator=(const Grid&) = delete;
};
