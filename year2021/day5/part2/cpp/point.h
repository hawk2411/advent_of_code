//
// Created by hawk on 18.06.22.
//

#ifndef ADVENT_OF_CODE_POINT_H
#define ADVENT_OF_CODE_POINT_H


#include <complex>

class point {
    unsigned int _x;
    unsigned int _y;

public:
    point(unsigned int x, unsigned int y) : _x(x), _y(y){}

    bool operator==(const point& pt) const{
        return (pt._x == _x) && (pt._y == _y);
    }
    virtual bool operator!=(const point& pt) const{
        return !operator==(pt);
    }

    [[nodiscard]] double get_length() const {
        return std::sqrt(_x*_x + _y*_y);
    }

    bool operator<(const point& pt)const{

        double length_this = get_length();
        double length_pt = pt.get_length();

        if( length_this < length_pt)
            return true;

        if(length_this == length_pt) {

            if(operator==(pt)) {
                return false;
            }
            else {
                return (_x < pt._x);
            }
        }

        return false;
    }

    [[nodiscard]] unsigned int getX() const {
        return _x;
    }

    [[nodiscard]] unsigned int getY() const {
        return _y;
    }

    void setX(unsigned int x) { _x = x; }

    void setY(unsigned int y) { _y = y; }
};


#endif //ADVENT_OF_CODE_POINT_H
