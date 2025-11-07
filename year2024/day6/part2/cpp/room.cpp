//
// Created by adwaha9 on 03.11.2025.
//
#include "room.h"
#include <fstream>
#include <iostream>

#include "trim_functions.h"

std::unique_ptr<Room> Room::Create(std::ifstream & input_data) {

    std::string text_line;

    std::unique_ptr<Room> new_room = std::make_unique<Room>();

    while (std::getline(input_data, text_line)) {
        string_trimmer::trim(text_line);
        if (text_line.empty()) {
            break;
        }
        new_room->SetWidth(text_line.size());
        new_room->IncreaseLength();

        for (int x = 0; x < new_room->GetWidth(); ++x) {
            if (text_line[x] == '#') {
                if (!new_room->PlaceObstruction(Position{x, new_room->GetLength()-1})) {
                    std::cerr << "cannot insert " << x << std::endl;
                    return nullptr;
                }
            }
            else if (text_line[x] == '^') {
                new_room->PlaceGuard(Position{x, new_room->GetLength()-1});
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

bool Room::IsOutOfBound(const Position &position) const {
    return (position.X() >= _width || position.Y() >= _length || position.X() < 0 || position.Y() < 0);
}

bool Room::PlaceObstruction(const Position &position) {
    auto result = _obstructions.insert(Position{position.X(), position.Y()});
    return result.second;
}

void Room::RemoveObstruction(const Position& position)
{
	_obstructions.erase(position);
}

bool Room::IsGuardInLoop()
{
	std::set<Guard> guard_positions;

    guard_positions.insert(_guard);
	auto next_position = do_next_step(room, obstacles, guard_position, virt_direction);
	while (next_position.has_value()) {
		if (next_position.value() == start_postion) {
			return true;
		}
		next_position = do_next_step(room, obstacles, next_position.value(), virt_direction);
	}
	guard is out of bounds
return false;
}

void Room::PlaceGuard(Position position) {
    _guard.SetPosition(position);
}

std::optional<Guard> Room::MoveGuard() {

    auto guard_next = _guard.GetNextPosition();
    if (IsOutOfBound(guard_next.GetPosition()) ) {
        //out of room border
        return {};
    }

    if (  _obstructions.contains(guard_next.GetPosition()))
    {
        //turn the guard to the right
        _guard.TurnRight();
        return MoveGuard();
    }
    _guard = guard_next;
    return guard_next;
}


std::optional<Position> Room::GetNextPossibleObstructionPosition() const {
    return GetNextPossibleObstructionPosition(_guard.GetDirection());
}

std::optional<Position> Room::GetNextPossibleObstructionPosition(const Direction& direction) const {
    Position next_position {_guard.GetPositionX() + direction.X(),
        _guard.GetPositionY() + direction.Y()};

    if (IsOutOfBound(next_position)) {
        return std::nullopt;
    }

    if (_obstructions.contains(next_position))
    {
        //turn the guard to the right
        Direction new_direction = direction.GetRight();
        return GetNextPossibleObstructionPosition(new_direction);
    }
    return next_position;
}
