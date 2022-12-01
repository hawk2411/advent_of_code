//
// Created by hawk on 15.07.21.
//

#ifndef DAY8_COMPUTER_H
#define DAY8_COMPUTER_H


#include <vector>
#include <memory>
#include "CodeLine.h"

class Computer {
private:
    int accumulator_;
    std::vector<std::unique_ptr<CodeLine>> program_;

public:
    Computer();
    void insertCodeLine(CodeLine* line);

    int getAccumulator() const;

    void executeProgram();
};


#endif //DAY8_COMPUTER_H
