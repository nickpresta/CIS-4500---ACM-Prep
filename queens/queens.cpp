#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <vector>

void printBoard(std::vector<int> board, unsigned int N) {
  std::cout << std::string(N, '=') << "\n";
  for (int position : board) {
    for (int i = 0; i < position; ++i) {
      (void)i;
      std::cout << ".";
    }
    std::cout << "Q";
    for (int i = 0; i < (N - position - 1); ++i) {
      (void)i;
      std::cout << ".";
    }
    std::cout << "\n";
  }
  std::cout << std::string(N, '=') << "\n\n";
}

int main(int argc, char *argv[]) {
  unsigned int N = 8;
  if (argc > 1) {
    std::stringstream(argv[1]) >> N;
  }

  std::vector<int> numbers;
  for (unsigned int i = 0; i < N; ++i) {
    numbers.push_back(i);
  }

  unsigned int numSolutions = 0;
  do {
    // To check for diagonals, you add or subtract the column number from each
    // entry, so any two entries on the same diagonal will have the same value.
    // (In order words, the sum or difference is unique for each diagonal).
    // To make sure the diagonals for the queens are distinct, put them in a
    // set and check that the length is equal to N (nothing was removed).
    std::set<int> diagonalUp;
    std::set<int> diagonalDown;
    for (unsigned int i = 0; i < N; ++i) {
      diagonalUp.insert(numbers[i] + i);
      diagonalDown.insert(numbers[i] - i);
    }
    if (N == diagonalUp.size() && N == diagonalDown.size()) {
      ++numSolutions;
#ifdef DEBUG
      std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
      std::cout << "\n";
      printBoard(numbers, N);
#endif
    }
  } while (std::next_permutation(numbers.begin(), numbers.end()));

  std::cout << numSolutions << " solutions!\n";

  return 0;
}
