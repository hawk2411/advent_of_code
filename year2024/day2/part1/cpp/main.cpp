#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <trim_functions.h>

std::vector<int> CreateReport(const std::string& report_string) {
    std::vector<int> report;

    auto working_string = report_string;
    try  {
        while (!working_string.empty()) {
            std::size_t pos{0};
            const auto level =  std::stoi(working_string, &pos);
            report.push_back(level);
            working_string = working_string.substr(pos);
        }
    }
    catch (const std::invalid_argument& ex) {
        std::cout << ex.what() << std::endl;
    }

    return report;
}

bool IsReportSave(const std::vector<int>& report) {
    bool increase = ( report[1] > report[0] );
    for (std::size_t i = 0; i < report.size() - 1; i++)
    {
        int diff = 0;
        if(increase)
        {
            if(report[i] > report[i + 1])
            {
                return false;
            }
            diff = report[i + 1] - report[i];
        }
        else
        {
            if(report[i] < report[i + 1])
            {
                return false;
            }
            diff = report[i] - report[i + 1];
        }
        if(diff < 1 || diff > 3)
        {
            return false;
        }
    }
    return true;
}

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    long sum  = 0;

    std::string text_line;
    while(std::getline(input_data, text_line)) {
        string_trimmer::trim(text_line);
        if(text_line.empty()) {
            break;
        }
        const auto report = CreateReport(text_line);

        if(IsReportSave(report)) {
            sum ++;
        }

    }

    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


