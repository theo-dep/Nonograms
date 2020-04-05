#include "Grid.h"

Grid::Grid(void)
{
    ;
}

Grid::~Grid(void)
{
    ;
}

void Grid::init(const Puzzle::Config& p_config)
{
    initMap(p_config);
    initRowHelper();
    initColHelper();
}

void Grid::initMap(const Puzzle::Config& p_config)
{
    m_rMap.resize(p_config.m);
    for (std::vector<Pixel>& rows : m_rMap)
    {
        rows.resize(p_config.n);
    }
    for (int i = 0; i < p_config.n; i++)
    {
        std::vector<Pixel> col;
        for (int j = 0; j < p_config.m; j++)
        {
            Pixel pixel(p_config.row_masks[i][j] == 1);
            col.push_back(pixel);
            m_rMap[j][i] = pixel;
        }
        m_map.push_back(col);
    }
}

void Grid::initRowHelper(void)
{
    for (const std::vector<Pixel>& colums : m_map)
    {
        m_rowHelper.push_back(initLineHelper(colums));
    }
}

void Grid::initColHelper(void)
{
    for (const std::vector<Pixel>& rows : m_rMap)
    {
        m_colHelper.push_back(initLineHelper(rows));
    }
}

std::list<uint8_t> Grid::initLineHelper(const std::vector<Pixel>& p_line)
{
    std::list<uint8_t> line;
    uint8_t numberOfBlack = 0;
    for (const Pixel& pixel : p_line)
    {
        if (pixel.isBlack())
        {
            numberOfBlack++;
        }
        else if (numberOfBlack > 0)
        {
            line.push_back(numberOfBlack);
            numberOfBlack = 0;
        }
    }
    return line;
}
