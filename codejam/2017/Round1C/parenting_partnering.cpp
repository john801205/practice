#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

enum Owner
{
  None, Cameron, Jamie
};

struct Slot
{
  int start, end, index;
  Owner owner;

  Slot(): start(-1), end(-1), index(-1), owner(None) {}
  Slot(int start, int end, int index, Owner owner): start(start), end(end), index(index), owner(owner) {}
};

bool comp(const Slot &lft, const Slot &rht)
{
  return lft.end <= rht.start;
}

int distance(const Slot &slt)
{
  return (slt.end + 1440 - slt.start) % 1440;
}

bool comp_length(const Slot &lft, const Slot &rht)
{
  return distance(lft) > distance(rht);
}

int main(void)
{
  std::ios::sync_with_stdio(false);

  int number_of_tests;
  std::cin >> number_of_tests;

  for (int test = 1; test <= number_of_tests; test++)
  {
    int number_of_cameron_activities, number_of_jamie_activities;
    std::cin >> number_of_cameron_activities >> number_of_jamie_activities;

    std::vector<Slot> times (number_of_cameron_activities + number_of_jamie_activities);
    int time_of_cameron = 0, time_of_jamie = 0;

    for (int i = 0; i < number_of_cameron_activities; ++i)
    {
      times[i].owner = Jamie;
      times[i].index = i;
      std::cin >> times[i].start >> times[i].end;
      time_of_jamie += distance(times[i]);
    }

    for (int i = 0, j = number_of_cameron_activities; i < number_of_jamie_activities; ++j, ++i)
    {
      times[j].owner = Cameron;
      times[j].index = j;
      std::cin >> times[j].start >> times[j].end;
      time_of_cameron += distance(times[j]);
    }

    std::sort(std::begin(times), std::end(times), comp);

    std::vector<Slot> all_times;
    std::priority_queue<Slot, std::vector<Slot>, std::function<bool(Slot, Slot)>> queues (comp_length);

    all_times.emplace_back(times.back().end, times.front().start, 0, None);
    queues.emplace(times.back().end, times.front().start, 0, None);

    all_times.emplace_back(times[0].start, times[0].end, 1, times[0].owner);

    for (int i = 1; i < times.size(); i++)
    {
      queues.emplace(times[i-1].end, times[i].start, all_times.size(), None);
      all_times.emplace_back(times[i-1].end, times[i].start, all_times.size(), None);
      all_times.emplace_back(times[i].start, times[i].end, all_times.size(), times[i].owner);
    }

    for (const auto &time: all_times)
    {
      std::cerr << time.start << '\t' << time.end << '\t' << distance(time) << '\t';
      if (time.owner == Cameron)
        std::cerr << "Cameron\n";
      else if (time.owner == Jamie)
        std::cerr << "Jamie\n";
      else
        std::cerr << "None\n";
    }

    while (!queues.empty())
    {
      int current = queues.top().index;
      queues.pop();

      int prev = (current+all_times.size()-1) % all_times.size();
      int next = (current+1) % all_times.size();

      std::cerr << current << ' ' << prev << ' ' << next << '\n';

      if (all_times[prev].owner != all_times[next].owner)
      {
        all_times[current].owner = all_times[next].owner;
      }
      else
      {
        if (all_times[prev].owner == Jamie)
        {
          if (time_of_jamie + distance(all_times[current]) <= 720)
          {
            all_times[current].owner = Jamie;
            time_of_jamie += distance(all_times[current]);
          }
          else
          {
            all_times[current].owner = Cameron;
          }
        }
        else
        {
          if (time_of_cameron + distance(all_times[current]) <= 720)
          {
            all_times[current].owner = Cameron;
            time_of_cameron += distance(all_times[current]);
          }
          else
          {
            all_times[current].owner = Jamie;
          }
        }
      }
    }

    for (const auto &time: all_times)
    {
      std::cerr << time.start << '\t' << time.end << '\t';
      if (time.owner == Cameron)
        std::cerr << "Cameron\n";
      else if (time.owner == Jamie)
        std::cerr << "Jamie\n";
      else
        std::cerr << "None\n";
    }

    std::cerr << "=======\n";

    int count = 0;
    if (all_times.front().owner != all_times.back().owner)
      count++;

    for (std::vector<int>::size_type i = 1; i < all_times.size(); i++)
      if (all_times[i-1].owner != all_times[i].owner)
        count++;

    std::cout << "Case #" << test << ": " << count << '\n';
  }

  return 0;
}
