#include <cstdio>

#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

int main(void)
{
  unsigned number_of_cases;

  while (scanf("%u", &number_of_cases) != EOF) {
    for (unsigned case_ = 0; case_ < number_of_cases; case_++) {
      if (case_ != 0)
        printf("\n");

      unsigned number_of_battlefields,
               number_of_green_lemmings,
               number_of_blue_lemmings;

      scanf("%u%u%u", &number_of_battlefields,
                      &number_of_green_lemmings,
                      &number_of_blue_lemmings);

      std::priority_queue<unsigned> green_lemmings, blue_lemmings;

      for (unsigned i = 0, lemming; i < number_of_green_lemmings; i++) {
        scanf("%u", &lemming);
        green_lemmings.push(lemming);
      }

      for (unsigned i = 0, lemming; i < number_of_blue_lemmings; i++) {
        scanf("%u", &lemming);
        blue_lemmings.push(lemming);
      }

      while (!green_lemmings.empty() && !blue_lemmings.empty()) {
        std::vector<unsigned> green_winners, blue_winners;

        for (unsigned battle = 0; battle < number_of_battlefields; battle++) {
          if (green_lemmings.empty() || blue_lemmings.empty())
            break;

          auto green = green_lemmings.top(),
               blue = blue_lemmings.top();

          if (green > blue)
            green_winners.push_back(green - blue);
          else if (blue > green)
            blue_winners.push_back(blue - green);

          green_lemmings.pop();
          blue_lemmings.pop();
        }

        for (auto &lemming: green_winners)
            green_lemmings.push(lemming);
        for (auto &lemming: blue_winners)
            blue_lemmings.push(lemming);
      }

      if (green_lemmings.empty() && blue_lemmings.empty()) {
        printf("green and blue died\n");
      } else if (!green_lemmings.empty()) {
        printf("green wins\n");

        while (!green_lemmings.empty()) {
          printf("%u\n", green_lemmings.top());
          green_lemmings.pop();
        }
      } else {
        printf("blue wins\n");

        while (!blue_lemmings.empty()) {
          printf("%u\n", blue_lemmings.top());
          blue_lemmings.pop();
        }
      }
    }
  }

  return 0;
}
