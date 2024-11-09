#pragma once
#include "Vertex.h"
#include "Board.h" 


class Rectangle
{
public:
  
    Rectangle(const Vertex& bottomLeft, const Vertex& topRight);
    Rectangle(const Vertex vertices[2]);
    Rectangle(const Vertex& topRight, double width, double height);
    Rectangle(double x, double y, double width, double height);

    
    Vertex getBottomLeft() const; 
    Vertex getTopRight() const; 
    double getWidth() const; 
    double getHeight() const; 
    void draw(Board& board) const; 
    Rectangle getBoundingRectangle() const; 
    double getPerimeter() const; 
    double getArea() const; 
    Vertex getCenter() const; 
    bool scale(double factor);
    void setDefault(); 
    bool isValidRectangle(const Vertex& bottomLeft, const Vertex& topRight) const; 
    Vertex checkChange(const Vertex& center, const Vertex& v1, double factor) const; 
    void initializeRectangle(const Vertex& bottomLeft, const Vertex& topRight); 

private:
    Vertex m_bottomLeft;
    Vertex m_topRight;
};
