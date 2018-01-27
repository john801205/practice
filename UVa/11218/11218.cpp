#include <bitset>
#include <iostream>
#include <vector>

struct Group
{
  int a, b, c, s;

  Group(int a, int b, int c, int s): a(a), b(b), c(c), s(s) {}
};

int DFS(const std::vector<Group>            &groups,
        const std::vector<Group>::size_type  start,
              std::bitset<9>                &people,
        const int                            score)
{
  if (people.all())
    return score;

  int max_score = -1;

  for (auto i = start; i < groups.size(); i++)
  {
    if (people.test(groups[i].a)
        or people.test(groups[i].b)
        or people.test(groups[i].c))
      continue;

    people.set(groups[i].a);
    people.set(groups[i].b);
    people.set(groups[i].c);

    auto current_score = DFS(groups, i+1, people, score + groups[i].s);
    if (current_score > max_score)
      max_score = current_score;

    people.reset(groups[i].a);
    people.reset(groups[i].b);
    people.reset(groups[i].c);
  }

  return max_score;
}

int main(void)
{
  int cases = 1;
  int number_of_combinations;

  while (std::cin >> number_of_combinations
         and number_of_combinations != 0)
  {
    std::vector<Group> groups;

    for (int i = 0; i < number_of_combinations; i++)
    {
      int a, b, c, s;
      std::cin >> a >> b >> c >> s;

      // change index from 1-9 to 0-8
      a--;
      b--;
      c--;

      groups.emplace_back(a, b, c, s);
    }

    std::bitset<9> people;

    std::cout << "Case " << cases << ": " << DFS(groups, 0, people, 0) << '\n';
    cases++;
  }

  return 0;
}
