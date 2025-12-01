//
// Created by adwaha9 on 03.11.2025.
//

#ifndef ADVENT_OF_CODE_GUARD_H
#define ADVENT_OF_CODE_GUARD_H

class Position {

public:
    Position() = default;
    Position(int x, int y) : _x(x), _y(y) {}
    void SetX(int x) {_x = x;};
    void SetY(int y) {_y = y;};
    [[nodiscard]] int X() const {
        return _x;
    }

    [[nodiscard]] int Y() const {
        return _y;
    }
    bool operator==(const Position &other) const {
        return _x == other._x && _y == other._y;
    }
    bool operator<(const Position &other) const {
        if( _x < other._x ) {
            return true;
        }
        if( _x == other._x && _y < other._y ) {
            return true;
        }
        return false;
    }
private:
    int _x {0};
    int _y {0};
};

class Direction {
public:
    Direction() = default;
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

    [[nodiscard]] Direction GetRight() const {
        const Direction new_direction (_y * -1, _x * 1);
        return new_direction;
    }

    bool operator==(const Direction &other) const {
        return _x == other._x && _y == other._y;
    }

    bool operator<(const Direction &other) const {
        if( _x < other._x ) {
            return true;
        }
        if( _x == other._x && _y < other._y ) {
            return true;
        }
        return false;
    }
private:
    int _x {0};
    int _y {-1};

};

class Guard {

public:

    Guard() = default;
    Guard(const Position &position, const Direction &direction)
        : _position(position),
          _direction(direction) {
    }

    [[nodiscard]] int GetPositionX() const {return _position.X();}
    [[nodiscard]] int GetPositionY() const {return _position.Y();}

    [[nodiscard]] int GetDirectionX() const {return _direction.X();}
    [[nodiscard]] int GetDirectionY() const {return _direction.Y();}
    void TurnRight() {_direction.TurnRight();}
    [[nodiscard]] Direction GetTurnRightDirection() const {return _direction.GetRight();}

    [[nodiscard]] Direction GetDirection()const {return _direction;}
    void SetDirection(const Direction& direction) {_direction = direction;}

    [[nodiscard]] Position  GetPosition() const;
    void SetPosition(Position position){_position = position;}
    [[nodiscard]] Guard GetNextPosition() const;

    bool operator<(const Guard &other) const {
        if( _position < other._position ) {
            return true;
        }
        if( _position == other._position ) {
            return _direction < other._direction;
        }
        return false;
    }

    bool operator==(const Guard &other) const {
        return (_position == other._position && _direction == other._direction);
    }


private:
    Position _position;
    Direction _direction;

};

#endif //ADVENT_OF_CODE_GUARD_H