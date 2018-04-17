#include <cassert>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<int> diffWaysToCompute(const std::string input)
    {
      std::vector<int> result;
      bool opt = false;
      int num = 0;

      for (std::vector<int>::size_type i = 0; i < input.size(); i++)
      {
        if (std::isdigit(input[i]))
        {
          num = num * 10 + input[i] - '0';
        }
        else
        {
          std::vector<int> lft = diffWaysToCompute(input.substr(0, i));
          std::vector<int> rht = diffWaysToCompute(input.substr(i+1));

          for (const auto &l: lft)
          {
            for (const auto &r: rht)
            {
              if (input[i] == '+')
                result.emplace_back(l+r);
              else if (input[i] == '-')
                result.emplace_back(l-r);
              else
                result.emplace_back(l*r);
            }
          }

          opt = true;
        }
      }

      if (!opt)
        result.emplace_back(num);

      std::sort(result.begin(), result.end());
      return result;
    }
};

int main(void)
{
  Solution s;
  assert(s.diffWaysToCompute("2-1-1") == std::vector<int> ({0, 2}));
  assert(s.diffWaysToCompute("2*3-4*5") == std::vector<int> ({-34, -14, -10, -10, 10}));
  assert(s.diffWaysToCompute("2*3-4*5-6*7*8") == std::vector<int> ({-2576,-2576,-2576,-2576,-2576,-2240,-2240,-1562,-1562,-1520,-1520,-1232,-1232,-1232,-1232,-1232,-1232,-1232,-1232,-1232,-1232,-1120,-1120,-944,-944,-896,-896,-896,-896,-778,-778,-752,-752,-736,-706,-706,-682,-682,-662,-662,-608,-592,-592,-448,-448,-448,-416,-416,-370,-370,-350,-350,-346,-346,-346,-346,-326,-326,-256,-112,-112,-112,-112,-112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,182,224,224,224,230,230,230,230,230,272,272,322,322,358,400,400,454,454,454,454,454,496,496,496,496,560,560,592,592,592,592,592,638,638,662,662,662,662,784,784,784,784,784,1190,1190,1232,1330,1330,2374,2374,2416,2416,2654,2654}));
  return 0;
}
