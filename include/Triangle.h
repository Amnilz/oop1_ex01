#pragma once

#include "macros.h"
#include "Vertex.h"
#include "Board.h"
#include "Utilities.h"
#include <cmath>
#include "Rectangle.h"



class Triangle
{
public:
	

	Triangle(const Vertex vertices[3]);
	Triangle(Vertex v0, Vertex v1, Vertex v2);

	Vertex getVertex(int index) const;
	Vertex getCenter() const;
	Rectangle getBoundingRectangle() const;
	double getLength(int index) const;
	double getPerimeter() const;
	double getArea() const;
	bool scale(double factor);
	void draw(Board& board) const;



private:

	Vertex checkChange(const Vertex& center, const Vertex& vertex, const double factor) const;
	bool isValidTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
	void initializeTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
	
	Vertex m_left;
	Vertex m_right;
	Vertex m_top;

};






