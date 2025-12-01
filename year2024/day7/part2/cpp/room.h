//
// Created by adwaha9 on 03.11.2025.
//

#ifndef ADVENT_OF_CODE_ROOM_H
#define ADVENT_OF_CODE_ROOM_H

#include <optional>
#include <set>
#include <memory>

#include "guard.h"

class Room {
public:

    Room() = default;
    void SetWidth(int size);

    void IncreaseLength();

    [[nodiscard]] int GetWidth() const;

    [[nodiscard]] int GetLength() const;

    [[nodiscard]] bool IsOutOfBound(const Position& position) const;

    [[nodiscard]] std::optional<Guard> GetNextPossibleGuardPosition(Guard guard) const;

    [[nodiscard]] Direction GetGuardDirection()const {return _guard.GetDirection();}

    [[nodiscard]]bool PlaceObstruction(const Position& position);

    void PlaceGuard(const Position& position, const Direction& direction);
    void PlaceGuard(const Guard& guard);

    [[nodiscard]]std::optional<Guard> MoveGuard();

    void RemoveObstruction(const Position& position );

    [[nodiscard]]bool IsGuardInLoop();
    [[nodiscard]] Guard GetGuard()const;

    static std::unique_ptr<Room> Create(std::ifstream & input_data);
private:
    int _width {0};
    int _length {0};
    std::set<Position> _obstructions;
    Guard _guard;

};

#endif //ADVENT_OF_CODE_ROOM_H