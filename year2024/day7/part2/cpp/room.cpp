//
// Created by adwaha9 on 03.11.2025.
//
#include "room.h"

#include <format>
#include <fstream>
#include <iostream>

#include "trim_functions.h"

std::unique_ptr<Room> Room::Create(std::ifstream& input_data) {
    std::string text_line;

    auto new_room = std::make_unique<Room>();

    while (std::getline(input_data, text_line)) {
        string_trimmer::trim(text_line);
        if (text_line.empty()) {
            break;
        }
        new_room->SetWidth(text_line.size());
        new_room->IncreaseLength();

        for (int x = 0; x < new_room->GetWidth(); ++x) {
            if (text_line[x] == '#') {
                if (!new_room->PlaceObstruction(Position{x, new_room->GetLength() - 1})) {
                    std::cerr << "cannot insert " << x << std::endl;
                    return nullptr;
                }
            }
            else if (text_line[x] == '^') {
                new_room->PlaceGuard(Position{x, new_room->GetLength() - 1}, Direction{0,-1});
            }
        }
    }
    return new_room;
}

void Room::SetWidth(int size) {
    _width = size;
}

void Room::IncreaseLength() {
    _length++;
}

int Room::GetWidth() const {
    return _width;
}

int Room::GetLength() const {
    return _length;
}

bool Room::IsOutOfBound(const Position& position) const {
    return (position.X() >= _width || position.Y() >= _length || position.X() < 0 || position.Y() < 0);
}

bool Room::PlaceObstruction(const Position& position) {
    auto result = _obstructions.insert(position);
    return result.second;
}

void Room::RemoveObstruction(const Position& position) {
    _obstructions.erase(position);
}

bool Room::IsGuardInLoop() {
    std::set<Guard> guard_positions;

    guard_positions.insert(_guard); //start position
    auto save_guard = _guard;

    auto next_position = MoveGuard();
    while (next_position.has_value()) {

        auto insert_result = guard_positions.insert(next_position.value());
        if (!insert_result.second ){
            std::cout << std::format("Found loop after {0} steps. ", guard_positions.size());
            std::cout << std::format("Guard found own foot print at {0} {1} {2} {3}\n", insert_result.first->GetPositionX(), insert_result.first->GetPositionY(), insert_result.first->GetDirectionX(), insert_result.first->GetDirectionY());

            return true;
        }
        next_position = MoveGuard();
    }
    return false;
}

Guard Room::GetGuard() const {
    return _guard;
}

void Room::PlaceGuard(const Position& position, const Direction& direction) {
    _guard.SetPosition(position);
    _guard.SetDirection(direction);
}

void Room::PlaceGuard(const Guard& guard) {
    _guard = guard;
}

std::optional<Guard> Room::MoveGuard() {
    auto guard_next = _guard.GetNextPosition();
    if (IsOutOfBound(guard_next.GetPosition())) {
        //out of room border
        return {};
    }

    if (_obstructions.contains(guard_next.GetPosition())) {
        //turn the guard to the right
        _guard.TurnRight();
        return MoveGuard();
    }
    _guard = guard_next;
    return guard_next;
}


std::optional<Guard> Room::GetNextPossibleGuardPosition(Guard guard) const {
    auto next_position = guard.GetNextPosition();

    if (IsOutOfBound(next_position.GetPosition())) {
        return std::nullopt;
    }

    if (_obstructions.contains(next_position.GetPosition())) {
        //turn the guard to the right
        guard.TurnRight();
        return GetNextPossibleGuardPosition(guard);
    }
    return next_position;

}
