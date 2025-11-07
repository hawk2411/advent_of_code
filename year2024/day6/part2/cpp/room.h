//
// Created by adwaha9 on 03.11.2025.
//

#ifndef ADVENT_OF_CODE_ROOM_H
#define ADVENT_OF_CODE_ROOM_H

#include <optional>
#include <set>
#include <memory>

#include "guard.h"

struct Room {
    int _width {0};
    int _length {0};
    std::set<Position> _obstructions;
    Guard _guard;

    void SetWidth(int size);

    void IncreaseLength();

    int GetWidth() const;

    int GetLength() const;

    bool IsOutOfBound(const Position& position) const;

    std::optional<Position> GetNextPossibleObstructionPosition() const;

    Direction GetGuardDirection()const {return _guard.GetDirection();}

    bool PlaceObstruction(const Position& position);

    void PlaceGuard(Position position);

    std::optional<Guard> MoveGuard();

    void RemoveObstruction(const Position& position );

    bool IsGuardInLoop();

    static std::unique_ptr<Room> Create(std::ifstream & input_data);
private:
    std::optional<Position> GetNextPossibleObstructionPosition(const Direction& direction)const;

};

#endif //ADVENT_OF_CODE_ROOM_H