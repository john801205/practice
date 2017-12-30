#include <climits>

#include <iostream>
#include <unordered_set>
#include <vector>

int main(void)
{
  int N;

  while (std::cin >> N) {
    int M;
    std::vector<int> books (N);

    for (int i = 0; i < N; i++)
      std::cin >> books[i];
    std::cin >> M;

    std::unordered_set<int> sets;
    int book_i = 0, book_j = INT_MAX;
    for (const auto& book: books) {
      auto book2 = M - book;

      if (sets.find(book2) != sets.end()) {
        if (book2 > book) {
          if (book2 - book < book_j - book_i) {
            book_i = book;
            book_j = book2;
          }
        } else {
          if (book - book2 < book_j - book_i) {
            book_i = book2;
            book_j = book;
          }
        }
      }

      sets.insert(book);
    }

    std::cout << "Peter should buy books whose prices are "
              << book_i << " and " << book_j << ".\n\n";
  }

  return 0;
}
