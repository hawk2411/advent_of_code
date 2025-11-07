//
// Created by adwaha9 on 03.11.2025.
//

#ifndef ADVENT_OF_CODE_GUARD_H
#define ADVENT_OF_CODE_GUARD_H

class Position {
    int _x {0};
    int _y {0};

public:
    Position(int x, int y) : _x(x), _y(y) {}
    void SetX(int x) {_x = x;};
    void SetY(int y) {_y = y;};
    [[nodiscard]] int X() const {
        return _x;
    }

    [[nodiscard]] int Y() const {
        return _y;
    }

};

class Direction {
public:
    Direction(int x, int y) : _x(x), _y(y) {}
    void SetX(int x) {
        _x = x;
    }

    void SetY(int y) {
        _y = y;
    }

    [[nodiscard]] int X() const {
        return _x;
    }

    [[nodiscard]] int Y() const {
        return _y;
    }

    void TurnRight() {
        const auto direction = GetRight();
        _x = direction.X();
        _y = direction.Y();
    }

    Direction GetRight() const {
        const Direction new_direction (_y * -1, _x * 1);
        return new_direction;
    }


private:
    int _x {0};
    int _y {-1};

};

class Guard {

public:

    Guard(const Position &position, const Direction &direction)
        : _position(position),
          _direction(direction) {
    }

    [[nodiscard]] int GetPositionX() const {return _position.X();}
    [[nodiscard]] int GetPositionY() const {return _position.Y();}

    [[nodiscard]] int GetDirectionX() const {return _direction.X();}
    [[nodiscard]] int GetDirectionY() const {return _direction.Y();}
    void TurnRight() {_direction.TurnRight();}
    Direction GetRight() const {return _direction.GetRight();}

    Direction GetDirection()const {return _direction;}

    void SetPosition(Position position){_position = position;}
    Guard GetNextPosition() const;

    Position  GetPosition() const;

private:
    Position _position;
    Direction _direction;

};

#endif //ADVENT_OF_CODE_GUARD_H