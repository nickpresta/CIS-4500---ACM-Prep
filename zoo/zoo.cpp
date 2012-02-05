#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

long findFreeSpaces(const long rows) {
  if (rows < 0) {
    return 0;
  }

  std::vector<long> last(1, 1);
  for (long i = 1; i < rows; ++i) {
    std::vector<long> thisRow;
    thisRow.reserve(i + 1);
    thisRow.push_back(last.front());
    std::transform(last.begin(), last.end() - 1, last.begin() + 1,
        std::back_inserter(thisRow), std::plus<long>());
    thisRow.push_back(last.back());
    last.swap(thisRow);
  }

  // This is the last row (our N row)
  // Take the first 5 values, if rows >= 5
  if (rows >= 5L) {
    return std::accumulate(last.begin(), last.begin() + 5L, 0);
  } else {
    return std::accumulate(last.begin(), last.end(), 0);
  }
}

int main(int argc, char *argv[]) {
  unsigned long N = 5;
  if (argc > 1L) {
    std::stringstream(argv[1]) >> N;
  }

  std::cout << "Number of posts:\t" << N << "\n";
  std::cout << "Number of free spaces:\t" << findFreeSpaces(N) << "\n";

  return 0;
}
