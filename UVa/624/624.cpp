#include <iostream>
#include <vector>

void print_tracks(const std::vector<int>& tracks,
                  const std::vector<std::vector<bool>>& added,
                  int number_of_tracks,
                  int N)
{
  for (int i = number_of_tracks - 1, j = N; i >= 0; i--) {
    if (added[i][j]) {
      print_tracks(tracks, added, i, j - tracks[i]);
      std::cout << tracks[i] << ' ';
      return;
    }
  }
}

int main(void)
{
  int N;

  while (std::cin >> N) {
    int number_of_tracks;
    std::cin >> number_of_tracks;

    std::vector<int> tracks (number_of_tracks);
    for (int i = 0; i < number_of_tracks; i++)
      std::cin >> tracks[i];

    std::vector<int> tables (N + 1);
    std::vector<std::vector<bool>> added (number_of_tracks, std::vector<bool> (N+1));

    for (int i = 0; i < number_of_tracks; i++) {
      for (int j = N; j >= tracks[i]; j--) {
        if (tables[j - tracks[i]] + tracks[i] >= tables[j]) {
          tables[j] = tables[j - tracks[i]] + tracks[i];
          added[i][j] = true;
        }
      }
    }

    print_tracks(tracks, added, number_of_tracks, N);
    std::cout << "sum:" << tables[N] << std::endl;
  }

  return 0;
}
