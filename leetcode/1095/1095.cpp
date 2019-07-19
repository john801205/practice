class MountainArray
{
  public:
    int get(int index) {}
    int length() {}
};

class Solution 
{
  public:
    int findInMountainArray(int target, MountainArray &mountainArr)
    {
      const auto length = mountainArr.length();

      int l = 0, r = length-1;
      while (l < r)
      {
        int m = l + (r - l) / 2;
        if (mountainArr.get(m) < mountainArr.get(m+1))
          l = m+1;
        else
          r = m;
      }
      const int peak = l;

      l = 0;
      r = peak;
      while (l <= r)
      {
        const int m = l + (r - l) / 2;
        const int val = mountainArr.get(m);
        if (val == target)
          return m;
        else if (val > target)
          r = m-1;
        else
          l = m+1;
      }

      l = peak+1;
      r = length-1;
      while (l <= r)
      {
        const int m = l + (r - l) / 2;
        const int val = mountainArr.get(m);
        if (val == target)
          return m;
        else if (val > target)
          l = m+1;
        else
          r = m-1;
      }

      return -1;
    }
};

int main()
{
  return 0;
}
