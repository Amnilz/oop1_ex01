#include "IsoscelesTriangle.h"

IsoscelesTriangle::IsoscelesTriangle(const Vertex vertices[3]) : m_triangle(vertices)
{
    initializeTriangle(vertices[0], vertices[1], vertices[2]);
}

IsoscelesTriangle::IsoscelesTriangle(Vertex left, Vertex right, double height) :
    m_triangle(left, right, Vertex((left.m_col + right.m_col) / 2, left.m_row + height))
{
    initializeTriangle(left, right, Vertex((left.m_col + right.m_col) / 2, left.m_row + height));
}

void IsoscelesTriangle::initializeTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
    if (!isValidTriangle(v0, v1, v2))
    {
		Vertex v[] = {Vertex(20, 20), Vertex(30, 20), Vertex(25, 20 + sqrt(75))};
        m_triangle = Triangle(v);
        return;
    }
	m_triangle = Triangle(v0,v1,v2);
}

bool IsoscelesTriangle::isValidTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2) const 
{
    return v0.isValid() && v1.isValid() && v2.isValid() && doubleEqual(v0.m_row, v1.m_row) &&
        !doubleEqual(v0.m_row, v2.m_row) && doubleEqual(getLength(1), getLength(2)) && 
        !((!sameRow(v0, v1) && !sameCol(v0, v1)) ||
        (!sameRow(v1, v2) && !sameCol(v1, v2)) || (!sameRow(v2, v0) && !sameCol(v2, v0)));
}

bool IsoscelesTriangle::scale(double factor) { return m_triangle.scale(factor); }

double IsoscelesTriangle::getLength(int index) const{return m_triangle.getLength(index);}

Vertex IsoscelesTriangle::getVertex(int index) const{return m_triangle.getVertex(index);}

void IsoscelesTriangle::draw(Board& board) const{m_triangle.draw(board);}

Rectangle IsoscelesTriangle::getBoundingRectangle() const{return m_triangle.getBoundingRectangle();}

double IsoscelesTriangle::getHeight() const {return abs(m_triangle.getVertex(2).m_row - m_triangle.getVertex(1).m_row); }

double IsoscelesTriangle::getArea() const {return m_triangle.getArea();}

double IsoscelesTriangle::getPerimeter() const {return m_triangle.getPerimeter();}

Vertex IsoscelesTriangle::getCenter() const{return m_triangle.getCenter();}