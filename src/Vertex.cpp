#include "Vertex.h"
#include "macros.h"
#include <cmath>
#include <iostream>

bool Vertex::isHigherThan(const Vertex& other) const
{
    return m_row > other.m_row;
}

bool Vertex::isToTheRightOf(const Vertex& other) const
{
    return m_col > other.m_col;
}

bool Vertex::isValid() const
{
    return m_col >= 0 && m_col <= MAX_COL && m_row >= 0 && m_row <= MAX_ROW;
}
double Vertex::distanceTo(const Vertex& other) const
{
    return std::sqrt(std::pow(other.m_col - m_col, 2) + std::pow(other.m_row - m_row, 2));
}
std::istream& operator>>(std::istream& istr, Vertex& v)
{
    return istr >> v.m_col >> v.m_row;
}

std::ostream& operator<<(std::ostream& ostr, const Vertex& v)
{
    return ostr << "(" << v.m_col << ", " << v.m_row << ")";
}
