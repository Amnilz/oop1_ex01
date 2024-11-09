#include "macros.h"
#include "Vertex.h"
#include "Board.h"
#include "Triangle.h"
#include "Utilities.h"
#include <cmath>



Triangle::Triangle(const Vertex vertices[3])
{
    initializeTriangle(vertices[0],vertices[1],vertices[2]);
}

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2)
{
    initializeTriangle(v0,v1,v2);
}

Vertex Triangle::getVertex(int index) const
{
    switch (index) 
    {
    case 0: return m_v0;
    case 1: return m_v1;
    case 2: return m_v2;
    default: return Vertex(); 
    }  
}

bool Triangle::isValidTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2) const {
    if (!v0.isValid() || !v1.isValid() || !v2.isValid()) return false;

    if (isBaseParallelToX(v0, v1) && (std::abs(v2.m_row - v0.m_row) >= 0.1))
    {
        return true;
    }
    return false; 
}
void Triangle::initializeTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
    if (isValidTriangle(v0,v1,v2))
    {
        m_v0 = v0;
        m_v1 = v1;
        m_v2 = v2;
    }
    else 
    {
        setDefault();
    }
}

bool Triangle::isBaseParallelToX(const Vertex& v1, const Vertex& v2) const 
{
    return doubleEqual(v1.m_row, v2.m_row);
}

double Triangle::getLength(int index) const 
{
    switch (index) 
    {
    case 0:
        return m_v0.distanceTo(m_v1);  
    case 1:
        return m_v1.distanceTo(m_v2);  
    case 2:
        return m_v2.distanceTo(m_v0);  
    default:
        return 0.0; 
    }
}

Rectangle Triangle::getBoundingRectangle() const 
{
    
    double minX = std::min({ m_v0.m_col, m_v1.m_col, m_v2.m_col });
    double maxX = std::max({ m_v0.m_col, m_v1.m_col, m_v2.m_col });
    double minY = std::min({ m_v0.m_row, m_v1.m_row, m_v2.m_row });
    double maxY = std::max({ m_v0.m_row, m_v1.m_row, m_v2.m_row });

    Vertex bottomLeft(minX, minY);
    Vertex topRight(maxX, maxY);

    return Rectangle(bottomLeft, topRight);
}


double Triangle::getPerimeter() const
{
    return getLength(0) + getLength(1) + getLength(2);
    
}

double Triangle::getArea() const
{
    double a = getLength(0);
    double b = getLength(1);
    double c = getLength(2);
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
    
}

Vertex Triangle::getCenter() const 
{
    double x_c = (m_v0.m_col + m_v1.m_col + m_v2.m_col) / 3;
    double y_c = (m_v0.m_row + m_v1.m_row + m_v2.m_row) / 3;
    return Vertex(x_c, y_c);
}

bool Triangle::scale(double factor)
{
    if (factor <= 0) return false;
    Vertex center = getCenter();
    Vertex scaledV0 = checkChange(center, m_v0, factor);
    Vertex scaledV1 = checkChange(center, m_v1, factor);
    Vertex scaledV2 = checkChange(center, m_v2, factor);
    if (!isValidTriangle(scaledV0, scaledV1, scaledV2)) return false;
    m_v0 = scaledV0;
    m_v1 = scaledV1;
    m_v2 = scaledV2;
    return true;
}
Vertex Triangle::checkChange(const Vertex& center ,const Vertex& vertex,double factor) const
{
    double xDistance = (center.m_col - vertex.m_col) * factor;
    double yDistance = (center.m_row - vertex.m_row) * factor;
    return Vertex(center.m_col - xDistance, center.m_row - yDistance);
}
void Triangle::setDefault()
{
    m_v0 = Vertex(20, 20);
    m_v1 = Vertex(30, 20);
    m_v2 = Vertex(25, 20 + sqrt(75));
}

void Triangle::draw(Board& board) const
{
    Vertex vertices[] = { m_v0,m_v1,m_v2};

    for (int i = 0; i < 3; ++i) 
    {
        board.drawLine(vertices[i], vertices[(i + 1) % 3]);
    }
}