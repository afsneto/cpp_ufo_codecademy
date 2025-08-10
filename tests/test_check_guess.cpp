#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../ufo_functions.hpp"

TEST_CASE(check_guess_reveals_all_occurrences) {
    std::string codeword = "letter";
    std::string answer(codeword.size(), '_');
    bool result = check_guess(codeword, answer, 't');
    REQUIRE(result == true);
    REQUIRE(answer == "__tt__");
}

TEST_CASE(check_guess_returns_false_when_letter_absent) {
    std::string codeword = "letter";
    std::string answer(codeword.size(), '_');
    bool result = check_guess(codeword, answer, 'x');
    REQUIRE(result == false);
    REQUIRE(answer == "______");
}

TEST_CASE(check_guess_is_case_sensitive) {
    std::string codeword = "Apple";
    std::string answer(codeword.size(), '_');

    // lowercase guess should not match uppercase codeword
    bool lower_result = check_guess(codeword, answer, 'a');
    REQUIRE(lower_result == false);
    REQUIRE(answer == "_____");

    // uppercase guess should match and reveal the letter
    bool upper_result = check_guess(codeword, answer, 'A');
    REQUIRE(upper_result == true);
    REQUIRE(answer == "A____");
}
