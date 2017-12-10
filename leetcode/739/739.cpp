#include <iostream>
#include <vector>
#include <stack>
#include <utility>
using namespace std;

class Solution {
  public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
      int N = temperatures.size();
      vector<int> solution(N, 0);
      stack<pair<int, int>> future_days;

      for (int i = N - 1; i >= 0; --i) {
        while (!future_days.empty()) {
          if (future_days.top().first > temperatures[i])
            break;

          future_days.pop();
        }

        if (!future_days.empty())
          solution[i] = future_days.top().second - i;

        future_days.push(make_pair(temperatures[i], i));
      }

      return solution;
    }
};

int main(void)
{
  int array[] = {73, 74, 75, 71, 69, 72, 76, 73};
  vector<int> temperatures(array, array + sizeof(array) / sizeof(int));

  Solution s;
  vector<int> ss = s.dailyTemperatures(temperatures);

  for (auto it = ss.begin(); it != ss.end(); ++it)
    cout << *it << endl;

  return 0;
}
