#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <set>

auto get_value(const std::string& line){
    char* end_pointer;
    auto str = line.substr(5);
    auto value = std::strtol(str.c_str(), &end_pointer, 10);
    return value;
}

class cpu {
public:
    void increase_clock() {
        _current_clock++;
        calc_signal();
    }
    void increase_register(long value) {
        _register_x += value;
    }

    [[nodiscard]] long get_signal_strength()const {return _signal_strength;}
protected:
    void calc_signal() {
        switch(_current_clock) {
            case 20:
            case 60:
            case 100:
            case 140:
            case 180:
            case 220:
                _signal_strength += _current_clock * _register_x;
            default:
                _signal_strength += 0;
        }
    }

private:
    long  _register_x = 1;
    long _signal_strength = 0;
    long _current_clock = 0;

};

class command {
public:
    ~command() = default;

    virtual void set_clock(cpu& cp) = 0;
    virtual void do_command(cpu& cp) = 0;
};

class add_x_register : public command {
private:
    long _value;
public:
    add_x_register(long value)
        : _value(value)
    {}

    void set_clock(cpu& cp) override {
        cp.increase_clock();
        cp.increase_clock();
    }
    void do_command(cpu& cp) override {
        cp.increase_register(_value);
    }
};


class noop : public command {
public:
    noop() = default;

    void set_clock(cpu& cp) override {
        cp.increase_clock();
    }

    void do_command(cpu& cp) override {}
};

struct program
{
    cpu _cpu;

    void execute(std::ifstream& data)  {
        std::string line;
        while (std::getline(data, line)) {
            if( line.substr(0,4) == "noop") {
                noop cmd;
                cmd.set_clock(_cpu);
                cmd.do_command(_cpu);
            } else {
                add_x_register cmd (get_value(line));
                cmd.set_clock(_cpu);
                cmd.do_command(_cpu);
            }
        }

    }

    [[nodiscard]] long get_signal() const {
        return _cpu.get_signal_strength();
    }
};

int main() {


    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }

    program prg;
    prg.execute(input_data);
    input_data.close();


    std::cout << "Solution: " << prg.get_signal() << std::endl;
    return 0;
}


