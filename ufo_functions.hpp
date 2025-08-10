#include <vector>
#include <string>

void display_misses(int misses);

// Declare functions
void greet();
void end_game(std::string answer, std::string codeword);
void display_status(std::vector<char> incorrect, std::string answer);
bool check_guess(const std::string& codeword, std::string& answer, char letter);