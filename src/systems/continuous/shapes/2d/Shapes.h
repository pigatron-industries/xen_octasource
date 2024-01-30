#ifndef Shapes_h
#define Shapes_h

#include "../Shape2D.h"

class Square2D : public Shape2D {
    public:
        Square2D() {
            this->addSegment(&path1);
            this->addSegment(&path2);
            this->addSegment(&path3);
            this->addSegment(&path4);
        }

    private:
        Vector<2> point1 = { 1,  1};
        Vector<2> point2 = {-1,  1};
        Vector<2> point3 = {-1, -1};
        Vector<2> point4 = { 1, -1};

        PathLine<2> path1 = PathLine<2>(point1, point2);
        PathLine<2> path2 = PathLine<2>(point2, point3);
        PathLine<2> path3 = PathLine<2>(point3, point4);
        PathLine<2> path4 = PathLine<2>(point4, point1);
};

class Triangle2D : public Shape2D {
    public:
        Triangle2D() {
            this->addSegment(&path1);
            this->addSegment(&path2);
            this->addSegment(&path3);
        }

    private:
        Vector<2> point1 = {-1, -1};
        Vector<2> point2 = { 1, -1};
        Vector<2> point3 = { 0,  1};

        PathLine<2> path1 = PathLine<2>(point1, point2);
        PathLine<2> path2 = PathLine<2>(point2, point3);
        PathLine<2> path3 = PathLine<2>(point3, point1);
};

class Pentagon2D : public Shape2D {
    public:
        Pentagon2D() {
            this->addSegment(&path1);
            this->addSegment(&path2);
            this->addSegment(&path3);
            this->addSegment(&path4);
            this->addSegment(&path5);
        }

    private:
        Vector<2> point1 = { 0,  1};
        Vector<2> point2 = { 1,  0};
        Vector<2> point3 = { 0, -1};
        Vector<2> point4 = {-1, -1};
        Vector<2> point5 = {-1,  0};

        PathLine<2> path1 = PathLine<2>(point1, point2);
        PathLine<2> path2 = PathLine<2>(point2, point3);
        PathLine<2> path3 = PathLine<2>(point3, point4);
        PathLine<2> path4 = PathLine<2>(point4, point5);
        PathLine<2> path5 = PathLine<2>(point5, point1);
};

#endif



