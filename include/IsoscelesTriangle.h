#pragma once
#include "macros.h"
#include "Vertex.h"
#include "Board.h"
#include "Utilities.h"
#include "Rectangle.h"
#include "Triangle.h"

class IsoscelesTriangle
{
public:
	IsoscelesTriangle(const Vertex vertices[3]);
	IsoscelesTriangle(Vertex left, Vertex right, double height);

	double getLength(int index) const;
	Vertex getVertex(int index) const;
	double getHeight() const;
	void draw(Board& board) const;
	double getPerimeter() const;
	double getArea() const;
	Vertex getCenter() const;
	bool scale(double factor);
	Rectangle getBoundingRectangle() const;

private:
	bool isValidTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2) const;
	void initializeTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	
	Triangle m_triangle;
};