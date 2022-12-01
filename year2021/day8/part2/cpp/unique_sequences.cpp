//
// Created by hawk on 19.11.22.
//
#include <sstream>
#include <trim_functions.h>

#include "unique_sequences.h"

unique_sequences::unique_sequences(const std::string &input_line) {
    std::stringstream ss(input_line);

    std::string number;
    while (std::getline(ss, number, ' ')) {
        string_trimmer::trim(number);
        if (number.empty()) {
            continue;
        }
        auto seq_count = number.size();

        switch (seq_count) {
            case 2:
                _one = number;
                break;
            case 3:
                _seven = number;
                break;
            case 4:
                _four = number;
                break;
            case 7:
                _eight = number;
                break;
            default:
                break;
        }
    }
    if( _one.empty() || _four.empty() ||  _seven.empty() || _eight.empty() ) {
        throw std::runtime_error("parse error");
    }
}

const std::string &unique_sequences::getOne() const {
    return _one;
}

const std::string &unique_sequences::getFour() const {
    return _four;
}

const std::string &unique_sequences::getSeven() const {
    return _seven;
}

const std::string &unique_sequences::getEight() const {
    return _eight;
}

all_sequences::all_sequences(const std::string &input_line) : unique_sequences(input_line) {
    std::stringstream ss(input_line);

    std::string number;
    while (std::getline(ss, number, ' ')) {
        string_trimmer::trim(number);
        if (number.empty()) {
            continue;
        }
        auto seq_count = number.size();

        switch (seq_count) {
            case 5: {
                if(isThree(number)) {
                    _three = number;
                    continue;
                }
                if(isFive(number)) {
                    _five = number;
                    continue;
                }
                _two = number;
                break;
            }
            case 6:
                if(isSix(number)) {
                    _six = number;
                    continue;
                }
                if(isNine(number)) {
                    _nine = number;
                    continue;
                }
                _zero = number;
                break;
            default:
                break;
        }
    }
    if(_zero.empty() || _two.empty() || _three.empty() || _five.empty() || _six.empty() || _nine.empty()) {
        throw std::runtime_error("parse error");
    }
}

unsigned int all_sequences::getSegmentsDifference(const std::string &unknown_number, const std::string &known_number) {
    unsigned int count_not_findings = 0;

    for(const auto& c : known_number ) {
        auto pos = unknown_number.find(c);
        if(pos == std::string::npos) {
            ++count_not_findings;
        }
    }
    return count_not_findings;
}

bool all_sequences::isThree(const std::string &unknown_number) const {
    return (getSegmentsDifference(unknown_number, getOne()) == 0);
}

bool all_sequences::isFive(const std::string &unknown_number) const {
    return (getSegmentsDifference(unknown_number, getFour()) == 1);
}

bool all_sequences::isSix(const std::string &unknown_number) const {
    return (getSegmentsDifference(unknown_number, getOne() ) == 1);
}

bool all_sequences::isNine(const std::string &unknown_number) const {
    return (getSegmentsDifference(unknown_number, getFour()) == 0);
}

const std::string &all_sequences::getZero() const {
    return _zero;
}

const std::string &all_sequences::getTwo() const {
    return _two;
}

const std::string &all_sequences::getThree() const {
    return _three;
}

const std::string &all_sequences::getFive() const {
    return _five;
}

const std::string &all_sequences::getSix() const {
    return _six;
}

const std::string &all_sequences::getNine() const {
    return _nine;
}

unsigned int all_sequences::getNumber(const std::string &number) const {
    auto seq_count = number.size();

    switch (seq_count) {
        case 2:
            return 1;
        case 3:
            return 7;
        case 4:
            return 4;
        case 7:
            return 8;
        case 5:
            if(isThree(number))
                return 3;
            if(isFive(number) )
                return 5;
            return 2;
        case 6:
            if(isSix(number)) {
                return 6;
            }
            if(isNine(number)) {
                return 9;
            }
            return 0;
        default:
            throw std::runtime_error("parse error");
    }
}
