#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <set>

class direction_t {
    int _x{0};
    int _y{0};

public:
    static direction_t create_direction(const std::string& movement) {

        direction_t result;
        auto direction = movement[0];

        switch (direction) {
            case 'R':
                result.setX(1);
                result.setY(0);
                break;
            case 'L':
                result.setX(-1);
                result.setY(0);
                break;
            case 'U':
                result.setY(1);
                result.setX(0);
                break;
            case 'D':
                result.setY(-1);
                result.setX(0);
                break;
            default:
                result.setY(0);
                result.setX(0);
        }
        return result;
    }

    bool operator==(const direction_t& direction) const {
        return ((direction._x == _x) && (direction._y == _y));
    }

    bool operator!=(const direction_t& direction) const {
        return !((direction._x == _x) && (direction._y == _y));
    }

    void setX(int x) {
        _x = x;
    }

    void setY(int y) {
        _y = y;
    }

    [[nodiscard]] int getX() const {
        return _x;
    }

    [[nodiscard]] int getY() const {
        return _y;
    }
};

struct coordinate_t {
    int x{0};
    int y{0};

    bool operator<(const coordinate_t& coord) const {
        if(x < coord.x) return true;
        if(x > coord.x) return false;
        //x == coord.x
        if(y < coord.y) return true;
        if(y > coord.y) return false;
        //*this == coord
        return false;
    }

    bool operator==(const coordinate_t& left) const {
        return (x == left.x && y == left.y);
    }
};

struct rope_item {
    coordinate_t _position;
    direction_t _direction;

    virtual void make_a_step(const rope_item& predecessor) {
        const auto diff_x = predecessor._position.x - _position.x;
        const auto diff_y = predecessor._position.y - _position.y;
        if((abs(diff_x) > 1) || abs(diff_y) > 1) {
            if(diff_x != 0) {
                _position.x = _position.x + ((diff_x < 0) ? -1 : 1);
            }
            if(diff_y != 0 ) {
                _position.y = _position.y + ((diff_y < 0) ? -1 : 1);
            }
        }
//        if((abs(diff_y) > 1)) {
//            _position.y = predecessor._position.y + -1 * predecessor._direction.getY();
//            _position.x = _position.x + _direction.getX();
//        }
//        _direction.setX( predecessor._position.x - _position.x);
//        _direction.setY( predecessor._position.y - _position.y);
    }

    void print_debug() const
    {
        std::cout << "Direction: " << _direction.getX() << " : " << _direction.getY() << std::endl;
        std::cout << "Position: " << _position.x << " : " << _position.y << std::endl;

    }

};

struct head_t : public rope_item {
    void make_a_step(const direction_t& direction) {
        _direction = direction;
        _position.x += _direction.getX();
        _position.y += _direction.getY();
    }
};

struct tail_t : public rope_item {
    std::vector<coordinate_t> _positions;

    void make_a_step(const rope_item& predecessor) override{
        rope_item::make_a_step(predecessor);

        bool found = false;
        for( const auto& pos : _positions) {
            if(pos == _position) {
                found = true;
                break;
            }
        }
        if( ! found ) {
            _positions.push_back(_position);
        }
    }

};

struct rope_t {

    head_t head;
    tail_t tail;
    constexpr static int max_knots = 8;
    std::array<rope_item, max_knots> knots;

    void move(const std::string& move_command) {
        std::cout << "Command: " << move_command << "\n";
        auto new_direction = direction_t::create_direction(move_command);
        auto is_direction_changed = (new_direction != head._direction);

        auto steps = static_cast<int>(std::strtol( move_command.substr(2).c_str(), nullptr, 10 ));
        for(int i = 0; i < steps; i++) {
            std::cout << "Step: " << i << std::endl;
            head.make_a_step(new_direction);

            std::cout << " head: \n";
            head.print_debug();

            knots[0].make_a_step(head);
            std::cout << " node 0: \n";
            knots[0].print_debug();
            for(int n=1; n < max_knots; n++) {
                knots[n].make_a_step(knots[n-1]);
                std::cout << " node " << n << ": \n";
                knots[n].print_debug();
            }
            tail.make_a_step(*knots.rbegin());
            std::cout << " tail: \n";
            tail.print_debug();
        }

    }

    [[nodiscard]] std::size_t tail_positions_count()const {
        return tail._positions.size();
        }

    void tail_positions()const {
        std::cout << "--\n";
        for(const auto& pos:  tail._positions) {
            std::cout << "x: " << pos.x << " | y: " << pos.y << "\n";
        }
    }

    void print_debug()const {
        for(const auto& ri : knots) {
            ri.print_debug();
        }
    }
};
int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }

    rope_t rope;
    std::string text_line;
    while(std::getline(input_data, text_line)) {
        rope.move(text_line);
    }
    input_data.close();


    std::cout << "Solution: " << rope.tail_positions_count() << std::endl;

    rope.print_debug();
    rope.tail_positions();

    return 0;
}


