#include "macros.h"
#include "Vertex.h"
#include "Board.h"
#include "Rectangle.h"
#include "Utilities.h"

Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight)
{
		
	if (!is_valid(bottomLeft, topRight))
	{

		setDefault();
		return;
	}
	m_bottomLeft = bottomLeft;
	m_topRight = topRight;
}
Rectangle::Rectangle(const Vertex vertices[2])
{
	if (!is_valid(vertices[0], vertices[1]))
	{
		setDefault();
		return;
	}
	m_bottomLeft = vertices[0];
	m_topRight = vertices[1];
}

Rectangle::Rectangle(const Vertex& topRight, double width, double height)
{
	Vertex vert;
	vert.m_col = topRight.m_col - width;
	vert.m_row = topRight.m_row - height;
	if (!is_valid(vert, topRight))
	{

		setDefault();
		return;
	}
	m_bottomLeft = vert;
	m_topRight = topRight;
}



Rectangle::Rectangle(double x, double y, double width, double height)
{
	Vertex vert1, vert2;

	vert1.m_col = x;
	vert1.m_row = y;
	vert2.m_col = x + width;
	vert2.m_row = y + height;
	if (!is_valid(vert1, vert2))
	{

		setDefault();
		return;
	}
	m_bottomLeft = vert1;
	m_topRight = vert2;
}
Vertex Rectangle::getBottomLeft() const
{
	return m_bottomLeft;
}
Vertex Rectangle::getTopRight() const
{
	return m_topRight;
}
double Rectangle::getWidth() const
{
	return m_topRight.m_col - m_bottomLeft.m_col;
}
double Rectangle::getHeight() const
{
	return m_topRight.m_row - m_bottomLeft.m_row;
}
bool Rectangle::is_valid(const Vertex& bottomLeft, const Vertex& topRight) const
{
	
	return !(!bottomLeft.isValid() || !topRight.isValid() || !topRight.isHigherThan(bottomLeft) || !topRight.isToTheRightOf(bottomLeft));

	
}
void Rectangle::draw(Board& board) const
{
	Vertex bottomRight, topLeft;
	bottomRight.m_col = m_topRight.m_col;
	bottomRight.m_row = m_bottomLeft.m_row;
	topLeft.m_col = m_bottomLeft.m_col;
	topLeft.m_row = m_topRight.m_row;
	board.drawLine(m_bottomLeft, bottomRight);
	board.drawLine(m_bottomLeft, topLeft);
	board.drawLine(topLeft, m_topRight);
	board.drawLine(m_topRight, bottomRight);
}
Rectangle Rectangle::getBoundingRectangle() const
{
	return Rectangle(m_bottomLeft,m_topRight);
}
double Rectangle::getPerimeter() const
{

	return ((m_topRight.m_col - m_bottomLeft.m_col) * 2 + (m_topRight.m_row - m_bottomLeft.m_row) * 2);
}
double Rectangle::getArea() const
{
	return (m_topRight.m_col - m_bottomLeft.m_col)*(m_topRight.m_row - m_bottomLeft.m_row);
}
Vertex Rectangle::getCenter() const
{
	
	return Vertex((m_bottomLeft.m_col + (m_topRight.m_col - m_bottomLeft.m_col) / 2),
		(m_bottomLeft.m_row + (m_topRight.m_row - m_bottomLeft.m_row) / 2));
}
bool Rectangle::scale(double factor) 
{
	if (factor <= 0) return false;
	Vertex center = getCenter();
	Vertex checkRight = checkChange(center, m_topRight, factor);
	Vertex checkLeft = checkChange(center, m_bottomLeft, factor);
	if (!is_valid(checkLeft, checkRight)) return false;
	m_bottomLeft = checkLeft;
	m_topRight = checkRight;
	return true;
	
}

Vertex Rectangle::checkChange(Vertex& center, const Vertex& v1, const double factor) const
{
	Vertex toCheck;
	double xDistance = (center.m_col - v1.m_col) * factor;
	double yDistance = (center.m_row - v1.m_row) * factor;
	toCheck.m_col = (center.m_col - xDistance);
	toCheck.m_row = (center.m_row - yDistance);
	
	return toCheck;
}

void Rectangle::setDefault()
{
	m_bottomLeft.m_col = 20;
	m_bottomLeft.m_row = 10;
	m_topRight.m_col = 30;
	m_topRight.m_row = 20;
}