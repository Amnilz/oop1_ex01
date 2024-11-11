#include "Triangle.h"
#include <cmath>
#include <cstdlib>


Triangle::Triangle(const Vertex vertices[3])
{
    initializeTriangle(vertices[0],vertices[1],vertices[2]);
}

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2)
{
    initializeTriangle(v0,v1,v2);
}

bool Triangle::isValidTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2) const 
{
    return v0.isValid() && v1.isValid() && v2.isValid() && doubleEqual(v0.m_row, v1.m_row)&&
        !doubleEqual(v0.m_row, v2.m_row) && !((!sameRow(v0,v1) && !sameCol(v0,v1)) ||
            (!sameRow(v1, v2) && !sameCol(v1, v2)) || (!sameRow(v2, v0) && !sameCol(v2, v0)));
}

void Triangle::initializeTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
    if (!isValidTriangle(v0, v1, v2))
    {
        m_left = Vertex(20, 20);
        m_right = Vertex(30, 20);
        m_top = Vertex(25, 20 + sqrt(75));
        return;
    }
    m_left = v0;
    m_right = v1;
    m_top = v2;
}

double Triangle::getLength(int index) const 
{
    switch (index) 
    {
    case 0:
        return distance(m_left,m_right);  
    case 1:
        return distance(m_right,m_top);  
    case 2:
        return distance(m_top ,m_left);
    default: exit(EXIT_FAILURE);
       
    }
}

double Triangle::getArea() const
{
    double a = getLength(0);
    double b = getLength(1);
    double c = getLength(2);
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

bool Triangle::scale(double factor)
{
    if (factor <= 0) return false;
    Vertex center = getCenter();
    Vertex scaledV0 = checkChange(center, m_left, factor);
    Vertex scaledV1 = checkChange(center, m_right, factor);
    Vertex scaledV2 = checkChange(center, m_top, factor);
    if (!isValidTriangle(scaledV0, scaledV1, scaledV2)) return false;
    m_left = scaledV0;
    m_right = scaledV1;
    m_top = scaledV2;
    return true;
}

Vertex Triangle::checkChange(const Vertex& center ,const Vertex& vertex,const double factor) const
{
    double xDistance = abs(center.m_col - vertex.m_col) * factor;
    double yDistance = abs(center.m_row - vertex.m_row) * factor;
    double xPos = vertex.isToTheRightOf(center) ? center.m_col + xDistance : center.m_col - xDistance;
    double yPos = vertex.isHigherThan(center) ? center.m_row + yDistance : center.m_row - yDistance;
    return Vertex(xPos,yPos);
}

Vertex Triangle::getVertex(int index) const
{
    switch (index)
    {
    case 0: return m_left;
    case 1: return m_right;
    case 2: return m_top;
    default: exit(EXIT_FAILURE);
    }
}

void Triangle::draw(Board& board) const
{
    Vertex vertices[] = { m_left,m_right,m_top};
    for (int i = 0; i < 3; ++i) 
    {
        board.drawLine(vertices[i], vertices[(i + 1) % 3]);
    }
}

Vertex Triangle::getCenter() const { return Vertex((m_left.m_col + m_right.m_col + m_top.m_col) / 3, (m_left.m_row + m_right.m_row + m_top.m_row) / 3); }

Rectangle Triangle::getBoundingRectangle() const { return Rectangle(Vertex(m_left.m_col, m_left.m_row), Vertex(m_right.m_col, m_top.m_row));}

double Triangle::getPerimeter() const { return getLength(0) + getLength(1) + getLength(2);}
