#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include "ufo_functions.hpp"

int main()
{
  // Load a random word from a file containing 10000 English words
  std::ifstream word_file("words.txt");
  std::vector<std::string> words;
  std::string word;
  while (std::getline(word_file, word)) {
    if (!word.empty()) {
      words.push_back(word);
    }
  }
  word_file.close();

  // Seed random and pick a random word
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  std::string codeword = words[std::rand() % words.size()];
  std::string answer = std::string(codeword.size(), '_');
  int misses = 0;
  std::vector<char> incorrect;
  bool guess = false;
  char letter;

  greet();

  while (answer != codeword && misses < 7)
  {

    display_misses(misses);
    display_status(incorrect, answer);

    std::cout << "\nPlease enter your guess: " << "\n";
    std::cin >> letter;
    guess = check_guess(codeword, answer, letter);

    if (guess == true)
    {
      std::cout << "Correct!" << "\n";
    }
    else
    {
      std::cout << "Incorrect! The tractor beam pulls the person in further." << "\n";
      if (std::find(incorrect.begin(), incorrect.end(), letter) == incorrect.end())
      {
        incorrect.push_back(letter);
        misses++;
      }
    }
    guess = false;
  }
  // Display the final status after the game ends
  display_status(incorrect, answer);
  end_game(answer, codeword);
  return 0;
}
