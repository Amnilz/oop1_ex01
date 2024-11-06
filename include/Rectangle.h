#pragma once
#include "Vertex.h"


class Rectangle 
{
public:
	Rectangle(const Vertex& bottomLeft, const Vertex& topRight);
	Rectangle(const Vertex vertices[2]);
	Rectangle(const Vertex& topRight, double width, double height);
	Rectangle(double x, double y, double width, double height);
	void setDefault();
	Vertex getBottomLeft() const;
	Vertex getTopRight() const;
	double getWidth() const;
	double getHeight()const;
	bool is_valid(const Vertex& bottomLeft, const Vertex& topRight) const;
	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;
	double getPerimeter() const;
	double getArea() const;
	Vertex getCenter() const;
	bool scale(double factor);
	Vertex checkChange(Vertex& center, const Vertex& v1, const double factor) const;
private:
	Vertex m_bottomLeft;
	Vertex m_topRight;
};