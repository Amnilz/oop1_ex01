#include "macros.h"
#include "Vertex.h"
#include "Board.h"
#include "Rectangle.h"
#include "Utilities.h"

Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight)
{
    initializeRectangle(bottomLeft, topRight);
}

Rectangle::Rectangle(const Vertex vertices[2])
{
    initializeRectangle(vertices[0], vertices[1]);
}

Rectangle::Rectangle(const Vertex& topRight, double width, double height)
{
    initializeRectangle(Vertex(topRight.m_col - width,topRight.m_row - height), topRight);
}

Rectangle::Rectangle(double x, double y, double width, double height)
{
    initializeRectangle(Vertex(x, y),Vertex(x + width, y + height));
}

void Rectangle::initializeRectangle(const Vertex& bottomLeft, const Vertex& topRight)
{
    if (!isValidRectangle(bottomLeft, topRight)) 
    {
        m_bottomLeft = Vertex(20, 10);
        m_topRight = Vertex(30, 20);
        return;
        
    }
    m_bottomLeft = bottomLeft;
    m_topRight = topRight;
}

Vertex Rectangle::getBottomLeft() const{return m_bottomLeft;}

Vertex Rectangle::getTopRight() const{return m_topRight;}

double Rectangle::getWidth() const{return m_topRight.m_col - m_bottomLeft.m_col;}

double Rectangle::getHeight() const{return m_topRight.m_row - m_bottomLeft.m_row;}

bool Rectangle::isValidRectangle(const Vertex& bottomLeft, const Vertex& topRight) const
{
    return bottomLeft.isValid() && topRight.isValid() &&
        topRight.isHigherThan(bottomLeft) && topRight.isToTheRightOf(bottomLeft);
}

void Rectangle::draw(Board& board) const
{
    Vertex vertices[] = { m_bottomLeft,
                          { m_topRight.m_col, m_bottomLeft.m_row },
                          m_topRight,
                          { m_bottomLeft.m_col, m_topRight.m_row }};

    for (int i = 0; i < 4; ++i) 
    {
        board.drawLine(vertices[i], vertices[(i + 1) % 4]);
    }
}

Rectangle Rectangle::getBoundingRectangle() const{return Rectangle(m_bottomLeft, m_topRight);}

double Rectangle::getPerimeter() const{return 2 * (getWidth() + getHeight());}

double Rectangle::getArea() const{return getWidth() * getHeight();}

Vertex Rectangle::getCenter() const
{
    return Vertex(m_bottomLeft.m_col + getWidth() / 2,
        m_bottomLeft.m_row + getHeight() / 2);
}

bool Rectangle::scale(double factor)
{
    if (factor <= 0) return false;
    Vertex center = getCenter();
    Vertex scaledBottomLeft = checkChange(center, m_bottomLeft, factor);
    Vertex scaledTopRight = checkChange(center, m_topRight, factor);
    if (!isValidRectangle(scaledBottomLeft, scaledTopRight)) return false;
    m_bottomLeft = scaledBottomLeft;
    m_topRight = scaledTopRight;
    return true;
}

Vertex Rectangle::checkChange(const Vertex& center, const Vertex& v, double factor) const
{
    double xDistance = abs(center.m_col - v.m_col) * factor;
    double yDistance = abs(center.m_row - v.m_row) * factor;
    double xPos = v.isToTheRightOf(center) ? center.m_col + xDistance : center.m_col - xDistance;
    double yPos = v.isHigherThan(center) ? center.m_row + yDistance : center.m_row - yDistance;
	return Vertex(xPos, yPos);
   
}
