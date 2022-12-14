//
// Created by hawk on 19.11.22.
//

#ifndef ADVENT_OF_CODE_UNIQUE_SEQUENCES_H
#define ADVENT_OF_CODE_UNIQUE_SEQUENCES_H


#include <string>

class unique_sequences {

    std::string _one;
    std::string _four;
    std::string _seven;
    std::string _eight;

public:
    explicit unique_sequences(const std::string& input_line);

    [[nodiscard]] const std::string &getOne() const;

    [[nodiscard]] const std::string &getFour() const;

    [[nodiscard]] const std::string &getSeven() const;

    [[nodiscard]] const std::string &getEight() const;
};

class all_sequences : public unique_sequences {
    std::string _zero;
    std::string _two;
    std::string _three;
    std::string _five;
    std::string _six;
    std::string _nine;

public:
    explicit all_sequences(const std::string& input_line);

    [[nodiscard]] unsigned int getNumber(std::string const & number ) const;

    [[nodiscard]] const std::string &getZero() const;

    [[nodiscard]] const std::string &getTwo() const;

    [[nodiscard]] const std::string &getThree() const;

    [[nodiscard]] const std::string &getFive() const;

    [[nodiscard]] const std::string &getSix() const;

    [[nodiscard]] const std::string &getNine() const;

protected:
    static unsigned int getSegmentsDifference(const std::string &unknown_number, const std::string &known_number);

    [[nodiscard]] bool isThree(const std::string &unknown_number) const ;

    [[nodiscard]] bool isFive(const std::string &unknown_number) const;

    [[nodiscard]] bool isSix(const std::string &unknown_number) const;

    [[nodiscard]] bool isNine(const std::string &unknown_number) const;
};

#endif //ADVENT_OF_CODE_UNIQUE_SEQUENCES_H
