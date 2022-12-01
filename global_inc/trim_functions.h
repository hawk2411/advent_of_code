//
// Created by hawk on 19.11.22.
//

#ifndef ADVENT_OF_CODE_TRIM_FUNCTIONS_H
#define ADVENT_OF_CODE_TRIM_FUNCTIONS_H
#include <string>

struct string_trimmer {
    static void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
    }

// trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

// trim from both ends (in place)
    static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

};
// trim from start (in place)

#endif //ADVENT_OF_CODE_TRIM_FUNCTIONS_H
