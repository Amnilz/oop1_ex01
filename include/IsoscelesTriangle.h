#pragma once
#include "Vertex.h"
#include "Rectangle.h"
#include "Triangle.h"

class IsoscelesTriangle
{
public:

	IsoscelesTriangle(const Vertex vertices[3]);
	IsoscelesTriangle(Vertex left, Vertex right, double height);
	
	
	void setDefault();
	double getLength(int index) const;
	Vertex getVertex(int index) const;
	double getHeight() const;
	void initializeTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	bool isValidIsosceles(const Vertex& v0, const Vertex& v1, const Vertex& v2) const;
	bool isBaseParallelToX(const Vertex& v1, const Vertex& v2) const;
	bool isValidTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2) const;
	void draw(Board& board) const;
	double getPerimeter() const;
	double getArea() const;
	Vertex getCenter() const;
	bool scale(double factor);
	Vertex checkChange(const Vertex& center, const Vertex& vertex, double factor) const;
	Rectangle getBoundingRectangle() const;


private:

	Vertex m_v0;
	Vertex m_v1;
	Vertex m_v2;


};