#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <numeric>

class file_node_t {
    std::string _name;
    std::size_t _size = 0;
public:
    file_node_t() = default;
    file_node_t(const std::string& name, std::size_t size): _name(name), _size(size) {

    }
    virtual ~file_node_t() = default;

    [[nodiscard]] virtual const std::string &getName() const {
        return _name;
    }

    virtual void setName(const std::string &name) {
        _name = name;
    }

    [[nodiscard]] virtual size_t getSize() const {
        return _size;
    }

    virtual void setSize(size_t size) {
        _size = size;
    }
};

using file_node_container_t = std::vector<std::unique_ptr<file_node_t>>;

class directory_t : public file_node_t {
    file_node_container_t _includes;
    directory_t* _parent = nullptr;
public:
    explicit directory_t()  = default;
    directory_t(const std::string& name, std::size_t size, directory_t* parent): file_node_t(name, size), _parent(parent) {}

    [[nodiscard]] directory_t * getParent() {
        return _parent;
    }

    void setParent(directory_t* parent) {
        _parent = parent;
    }

    [[nodiscard]] std::size_t getSize() const override  {
        auto sum_func = [](std::size_t count, const auto& b) {
            return count + b->getSize();
        };

        auto result = std::accumulate(_includes.cbegin(), _includes.cend(), 0, sum_func);

        return result;
    }

    directory_t* getDirectoryByName(const std::string& dir_name) {
        if(_includes.empty()) {return nullptr;}
        for( auto& file_node : _includes ) {
            auto dir = dynamic_cast<directory_t*>(file_node.get());
            if(dir == nullptr) { continue;}

            if( dir->getName() == dir_name ) {
                return dir;
            }
        }

        return nullptr;
    }

    void add_directory(const std::string &dir_name, std::size_t size) {
        _includes.push_back(std::make_unique<directory_t>(dir_name, size, this));
    }
    void add_file(const std::string &dir_name, std::size_t size) {
        _includes.push_back(std::make_unique<file_node_t>(dir_name, size));
    }

    void get_all_directories(std::vector<const directory_t *>& directories ) const {
        for(const auto& item :  _includes) {
            const directory_t* sub_dir = dynamic_cast<directory_t*>(item.get());
            if( sub_dir) {
                directories.push_back(sub_dir);
                sub_dir->get_all_directories(directories);
            }
        }
    }
};

class file_system_t {
    std::unique_ptr<directory_t> _root_directory;

public:
    file_system_t() {
        _root_directory = std::make_unique<directory_t>("/", 0, nullptr);
    }
    [[nodiscard]] directory_t* getRootDir()const{ return _root_directory.get(); }
};

class device {
    const std::string::size_type command_name_start_pos = 3;
    const std::string::size_type command_start_pos = 2;

    file_system_t _file_system;
    directory_t* _current_dir ;
public:
    device() {
        _current_dir = _file_system.getRootDir();
    }

    void execute(const std::vector<std::string> &programm) {
        std::size_t current_line_nr = 0;
        while(current_line_nr < programm.size()) {
            execute_command(current_line_nr, programm);
            current_line_nr++;
        }
    }

     [[nodiscard]] std::size_t get_solution(const std::size_t at_most) const {

        std::vector<const directory_t*> directories;
        directories.push_back(_file_system.getRootDir());

         _file_system.getRootDir()->get_all_directories(directories);
        std::size_t result = 0;
        for(const auto& dir : directories) {
            const auto dir_size = dir->getSize();
            if( dir_size <= at_most) {
                result += dir_size;
            }
        }

        return result;
    }

private:
    void execute_change_dir_command(const std::string& cd_command) {
        auto change_to_dir_name = cd_command.substr(command_name_start_pos);
        if(change_to_dir_name == "/") {
            _current_dir = _file_system.getRootDir();
            return;
        }
        if(change_to_dir_name == "..") {
            const auto parent_dir = _current_dir->getParent();
            _current_dir = parent_dir;
            return;
        }
        const auto current_dir = _current_dir->getDirectoryByName(change_to_dir_name);
        _current_dir = current_dir;

    }

    [[nodiscard]] static bool is_command(const std::string& line) {
        return (line[0] == '$');
    }

    static bool is_dir(const std::basic_string<char>& line) {
        if(is_command(line))
            return false;
        if(line[0] == 'd' && line[1] == 'i' && line[2] == 'r') {
            return true;
        }
        return false;
    }

    void execute_list_command(std::size_t& line_number, const std::vector<std::string>& programm) {

        std::string line = programm[line_number];

        while( ! is_command(line)) {

            if (is_dir(line)) {
                auto dir_name = line.substr(4);
                _current_dir->add_directory(dir_name, 0);
            } else {
                char* end_pointer;
                auto file_size = std::strtoul(line.c_str(), &end_pointer, 10);
                auto file_name = line.substr(end_pointer - line.c_str()+1);
                _current_dir->add_file(file_name, file_size);
            }
            line_number++;
            if( line_number >= programm.size()) {
                break;
            }

            line = programm[line_number];
        }
        if(line_number < programm.size()) {
            line_number--;
        }
    }

    void execute_command(std::size_t& line_number, const std::vector<std::string>& programm) {
        if(programm.empty()) {
            return;
        }
        if( line_number >= programm.size()) {
            return;
        }
        const std::string& line = programm[line_number];

        if(! is_command(line)) {
            return;
        }

        const std::string command = line.substr(command_start_pos);
        if(command.find("cd") != std::string::npos) {
            execute_change_dir_command(command);
            return;
        }

        execute_list_command(++line_number, programm);
    }

};
int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }

    std::string text_line;
    std::vector<std::string> programm;

    while(std::getline(input_data, text_line)) {
        programm.push_back(text_line);
    }
    input_data.close();

    device dev;
    dev.execute(programm);
    std::size_t result = dev.get_solution(100000);

    std::cout << "Solution: " << result << std::endl;
    return 0;
}


