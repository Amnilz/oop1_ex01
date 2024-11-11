#include "Vertex.h"
#include "Rectangle.h"
#include "Board.h"



class Window 
{
public:
    Window(const Rectangle& rectangle, const Vertex& point);
    Window(const Vertex& topRight, double width, double height, const Vertex& point);

    
    Vertex getBottomLeft() const; 
    Vertex getTopRight() const; 
    Vertex getPoint() const; 
    Vertex getCenter() const; 
    Rectangle getBoundingRectangle() const;
    bool scale(double factor);
    void draw(Board& board) const; 
    double getArea() const;
    double getPerimeter() const;

private:
    void setDefault();
    bool isPointInsideRectangle(const Vertex& point) const;
    Rectangle m_rectangle;
    Vertex m_windowPoint;
};
