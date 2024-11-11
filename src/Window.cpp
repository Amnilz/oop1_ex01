#include "macros.h"
#include "Vertex.h"
#include "Board.h"
#include "Rectangle.h"
#include "Utilities.h"
#include "Window.h"


Window::Window(const Rectangle& rectangle, const Vertex& point)
	: m_rectangle(rectangle), m_windowPoint(point)
{
	if (!isPointInsideRectangle(m_windowPoint))
	{
		setDefault();
	}
}

Window::Window(const Vertex& topRight, double width, double height, const Vertex& point)
	: m_rectangle(topRight, width, height), m_windowPoint(point)
{
	if (!isPointInsideRectangle(m_windowPoint))
	{
		setDefault();
	}
}

bool Window::isPointInsideRectangle(const Vertex& point) const
{
	return point.isHigherThan(m_rectangle.getBottomLeft()) && point.isToTheRightOf(m_rectangle.getBottomLeft()) &&
		!point.isHigherThan(m_rectangle.getTopRight()) && !point.isToTheRightOf(m_rectangle.getTopRight());
	
}

void Window::draw(Board& board) const
{
	m_rectangle.draw(board);
	board.drawLine(Vertex(m_rectangle.getBottomLeft().m_col, m_windowPoint.m_row),
		Vertex(m_rectangle.getTopRight().m_col, m_windowPoint.m_row));
	board.drawLine(Vertex(m_windowPoint.m_col, m_rectangle.getTopRight().m_row),
		Vertex(m_windowPoint.m_col, m_rectangle.getBottomLeft().m_row));

}

void Window::setDefault()
{
	m_rectangle.getBottomLeft() = Vertex(20, 10);
	m_rectangle.getTopRight() = Vertex(30, 20);
	m_windowPoint = Vertex(25, 15);
}

bool Window::scale(double factor) { return m_rectangle.scale(factor);}

Vertex Window::getBottomLeft() const { return m_rectangle.getBottomLeft();}

Vertex Window::getTopRight() const { return m_rectangle.getTopRight();}

Vertex Window::getPoint() const { return m_windowPoint;}

Rectangle Window::getBoundingRectangle() const { return m_rectangle.getBoundingRectangle();}

double Window::getPerimeter() const { return m_rectangle.getPerimeter() * 2;}

double Window::getArea() const { return m_rectangle.getArea();}

Vertex Window::getCenter() const { return m_windowPoint;}


