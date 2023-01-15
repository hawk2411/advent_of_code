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
};

struct knot_t {
    coordinate_t _position;
    direction_t _direction;
};

struct head_t : public knot_t {
    void make_a_step(const direction_t& direction) {
        _direction = direction;
        _position.x += _direction.getX();
        _position.y += _direction.getY();
    }
};

struct tail_t : public knot_t {

    std::set<coordinate_t> _positions;

    tail_t() {
        _positions.insert(_position);
    }

    void make_a_step(const knot_t& knot) {
        const auto diff_x = abs(knot._position.x - _position.x);
        const auto diff_y = abs(knot._position.y - _position.y);
        if((diff_x > 1) || diff_y > 1 ) {
            direction_t move_dir;
            move_dir.setX(  knot._direction.getX() == 0 ? _direction.getX() : knot._direction.getX() );
            move_dir.setY(  knot._direction.getY() == 0 ? _direction.getY() : knot._direction.getY() );

            _position.x = _position.x + 1 * move_dir.getX();
            _position.y = _position.y + 1 * move_dir.getY();
            _direction = knot._direction;
        }

        if(!_positions.contains(_position)) {
            _positions.insert(_position);
        }
    }
};

struct rope_t {

    head_t head;
    std::array<tail_t, 1> tails;

    void move(const std::string& move_command) {

        auto new_direction = direction_t::create_direction(move_command);
        auto is_direction_changed = (new_direction != head._direction);

        auto steps = static_cast<int>(std::strtol( move_command.substr(2).c_str(), nullptr, 10 ));
        for(int i = 0; i < steps; i++) {
            head.make_a_step(new_direction);
            tails[0].make_a_step(head);
            for( int t = 1; t < tails.size(); t++) {
                tails[t].make_a_step(tails[t-1]);
            }
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


    std::cout << "Solution: " << rope.tails[rope.tails.size()-1]._positions.size() << std::endl;
    return 0;
}


