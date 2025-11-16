//
// Created by adwaha9 on 03.11.2025.
//
#include "guard.h"

Guard Guard::GetNextPosition() const {
    return Guard (Position(_position.X() + _direction.X(), _position.Y() + _direction.Y()), _direction);
}

Position Guard::GetPosition() const {
    return _position;
}
