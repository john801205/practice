#include <cstdio>
#include <climits>

#include <vector>
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

      std::vector<int> green_lemmings, blue_lemmings;
      green_lemmings.reserve(number_of_green_lemmings);
      blue_lemmings.reserve(number_of_blue_lemmings);

      // fprintf(stderr, "%u %u %u\n", number_of_battlefields, number_of_green_lemmings, number_of_blue_lemmings);

      for (unsigned i = 0; i < number_of_green_lemmings; i++) {
        int lemming;
        scanf("%d", &lemming);
        green_lemmings.push_back(lemming);
      }

      for (unsigned i = 0; i < number_of_blue_lemmings; i++) {
        int lemming;
        scanf("%d", &lemming);
        blue_lemmings.push_back(lemming);
      }

      while (!green_lemmings.empty() && !blue_lemmings.empty()) {
        // fprintf(stderr, "first: %lu %lu\n", green_lemmings.size(), blue_lemmings.size());
        std::sort(green_lemmings.begin(), green_lemmings.end(), std::greater<int>());
        std::sort(blue_lemmings.begin(), blue_lemmings.end(), std::greater<int>());

        while (!green_lemmings.empty() && green_lemmings.back() <= 0)
          green_lemmings.pop_back();

        while (!blue_lemmings.empty() && blue_lemmings.back() <= 0)
          blue_lemmings.pop_back();

        if (green_lemmings.empty() || blue_lemmings.empty())
          break;

        // fprintf(stderr, "%lu %lu\n", green_lemmings.size(), blue_lemmings.size());

        int survival_max = INT_MIN;
        unsigned battle_start = 0, battle_end = number_of_battlefields;

        while (true) {
          if (green_lemmings.size() < battle_end)
            battle_end = green_lemmings.size();
          if (blue_lemmings.size() < battle_end)
            battle_end = blue_lemmings.size();

          if (battle_start >= battle_end)
            break;

          if (green_lemmings[battle_end-1] < survival_max
              || blue_lemmings[battle_end-1] < survival_max)
            break;

          for (unsigned battle = battle_start; battle < battle_end; battle++) {
            int temp = green_lemmings[battle];
            green_lemmings[battle] -= blue_lemmings[battle];
            blue_lemmings[battle] -= temp;

            if (green_lemmings[battle] > survival_max)
              survival_max = green_lemmings[battle];
            if (blue_lemmings[battle] > survival_max)
              survival_max = blue_lemmings[battle];
          }

          battle_start = battle_end;
          battle_end += number_of_battlefields;
        }
      }

      if (green_lemmings.empty() && blue_lemmings.empty()) {
        printf("green and blue died\n");
      } else if (!green_lemmings.empty()) {
        printf("green wins\n");

        std::sort(green_lemmings.begin(), green_lemmings.end(), std::greater<int>());
        for (auto &lemming: green_lemmings)
          printf("%d\n", lemming);
      } else {
        printf("blue wins\n");

        std::sort(blue_lemmings.begin(), blue_lemmings.end(), std::greater<int>());
        for (auto &lemming: blue_lemmings)
          printf("%d\n", lemming);
      }
    }
  }

  return 0;
}
