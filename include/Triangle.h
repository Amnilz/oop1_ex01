#pragma once
#include "Vertex.h"
#include "Rectangle.h"





class Triangle
{
public:
	Triangle(const Vertex vertices[3]);
	Triangle(Vertex v0, Vertex v1, Vertex v2);

	Vertex getVertex(int index) const;
	bool isValidTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
	void initializeTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
	bool isBaseParallelToX(const Vertex& v1, const Vertex& v2) const;
	double getLength(int index) const;
	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;
	double getPerimeter() const;
	double getArea() const;
	Vertex getCenter() const;
	bool scale(double factor);
	Vertex checkChange(const Vertex& center, const Vertex& vertex, double factor) const;
	void setDefault();



private:

	Vertex m_v0;
	Vertex m_v1;
	Vertex m_v2;

};






