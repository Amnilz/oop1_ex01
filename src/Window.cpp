#include "macros.h"
#include "Vertex.h"
#include "Board.h"
#include "Rectangle.h"
#include "Utilities.h"
#include "Window.h"


Window::Window(const Rectangle& rectangle, const Vertex& point)
	: m_rectangle(rectangle), m_windowPoint(point)
{
	initializeWindow();
}

Window::Window(const Vertex& topRight, double width, double height, const Vertex& point)
	: m_rectangle(topRight, width, height), m_windowPoint(point)
{
	initializeWindow();
}

void Window::initializeWindow()
{
	if (!m_rectangle.isValidRectangle(m_rectangle.getBottomLeft(), m_rectangle.getTopRight()) ||
		!isPointInsideRectangle(m_windowPoint) ||
		isPointOnEdge(m_windowPoint))
	{
		m_rectangle.setDefault();
		m_windowPoint = Vertex(25, 15);
	}
}

bool Window::isPointOnEdge(const Vertex& point) const
{
	return (point.m_row == m_rectangle.getBottomLeft().m_row || point.m_row == m_rectangle.getTopRight().m_row) &&
		(point.m_col >= m_rectangle.getBottomLeft().m_col && point.m_col <= m_rectangle.getTopRight().m_col) ||
		(point.m_col == m_rectangle.getBottomLeft().m_col || point.m_col == m_rectangle.getTopRight().m_col) &&
		(point.m_row >= m_rectangle.getBottomLeft().m_row && point.m_row <= m_rectangle.getTopRight().m_row);
}


bool Window::isPointInsideRectangle(const Vertex& point) const
{
	return point.m_col >= m_rectangle.getBottomLeft().m_col &&
		point.m_col <= m_rectangle.getTopRight().m_col &&
		point.m_row >= m_rectangle.getBottomLeft().m_row &&
		point.m_row <= m_rectangle.getTopRight().m_row;
}

Vertex Window::getBottomLeft() const
{
	return m_rectangle.getBottomLeft();
}

Vertex Window::getTopRight() const
{
	return m_rectangle.getTopRight();
}

Vertex Window::getPoint() const
{
	return m_windowPoint;
}

Rectangle Window::getBoundingRectangle() const
{
	return m_rectangle.getBoundingRectangle();
}


double Window::getPerimeter() const
{
	double widths[] = { m_windowPoint.m_col - m_rectangle.getBottomLeft().m_col,
						m_rectangle.getTopRight().m_col - m_windowPoint.m_col,
						m_windowPoint.m_col - m_rectangle.getBottomLeft().m_col,
						m_rectangle.getTopRight().m_col - m_windowPoint.m_col };

	double heights[] = { m_windowPoint.m_row - m_rectangle.getBottomLeft().m_row,
						 m_windowPoint.m_row - m_rectangle.getBottomLeft().m_row,
						 m_rectangle.getTopRight().m_row - m_windowPoint.m_row,
						 m_rectangle.getTopRight().m_row - m_windowPoint.m_row };

	double totalPerimeter = 0;

	
	for (int i = 0; i < 4; ++i)
	{
		totalPerimeter += 2 * (widths[i] + heights[i]);
	}

	return totalPerimeter;
}

double Window::getArea() const
{
	return m_rectangle.getArea();
}
Vertex Window::getCenter() const
{
	return m_rectangle.getCenter();
}
bool Window::scale(double factor)
{
	return m_rectangle.scale(factor);
}

void Window::draw(Board& board) const
{
	Vertex vertices[] = 
	{
		m_rectangle.getBottomLeft(),
		{ m_rectangle.getTopRight().m_col, m_rectangle.getBottomLeft().m_row },
		m_rectangle.getTopRight(),
		{ m_rectangle.getBottomLeft().m_col, m_rectangle.getTopRight().m_row }
	};

	for (int i = 0; i < 4; ++i)
	{
		Vertex start = vertices[i];
		Vertex end = vertices[(i + 1) % 4];
		board.drawLine(start, end); 
		Vertex edgePoint
		{
			(i % 2 == 0) ? m_windowPoint.m_col : start.m_col,
			(i % 2 == 0) ? start.m_row : m_windowPoint.m_row
		};
		board.drawLine(edgePoint, m_windowPoint); 
	}
}




