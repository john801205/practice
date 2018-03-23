#include <climits>

#include <iostream>
#include <vector>

class Solution
{
  public:
    double findMedianSortedArrays(const std::vector<int> &nums1,
                                  const std::vector<int> &nums2)
    {
      if (nums1.size() == 0)
      {
        return nums2.size() % 2 != 0 ? nums2[nums2.size()/2]: static_cast<double>(nums2[nums2.size()/2-1] + nums2[nums2.size()/2])/2;
      }
      else if (nums2.size() == 0)
      {
        return nums1.size() % 2 != 0 ? nums1[nums1.size()/2]: static_cast<double>(nums1[nums1.size()/2-1] + nums1[nums1.size()/2])/2;
      }

      std::vector<int>::size_type nums1_left  = 0,
                                  nums1_right = nums1.size()-1,
                                  nums2_left  = 0,
                                  nums2_right = nums2.size()-1;

      std::vector<int>::size_type middle_count = (nums1.size() + nums2.size()) / 2;

      while (nums1_left <= nums1_right && nums2_left <= nums2_right)
      {
        std::vector<int>::size_type nums1_middle = (nums1_left + nums1_right) / 2;
        std::vector<int>::size_type nums1_count = nums1_middle - nums1_left,
                                    nums2_count = lessThan(nums2, nums2_left, nums2_right, nums1[nums1_middle]);

        if (nums1_count + nums2_count > middle_count)
        {
          if (nums1_middle == 0)
          {
            nums1_left = nums1_right + 1;
            break;
          }

          nums1_right = nums1_middle - 1;
          nums2_right = nums2_left + nums2_count - 1;
        }
        else if (nums1_count + nums2_count < middle_count)
        {
          nums1_left = nums1_middle + 1;
          nums2_left = nums2_left + nums2_count;
          middle_count = middle_count - (nums1_count + 1) - nums2_count;
        }
        else
        {
          break;
        }
      }

      int median;

      if (nums1_left <= nums1_right && nums2_left <= nums2_right)
      {
        median = nums1[(nums1_left + nums1_right)/2];
      }
      else if (nums1_left > nums1_right)
      {
        median = nums2[nums2_left + middle_count];
      }
      else
      {
        median = nums1[nums1_left + middle_count];
      }

      if ((nums1.size() + nums2.size()) % 2 != 0)
      {
        return median;
      }
      else if (lessThan(nums1, 0, nums1.size()-1, median) + lessThan(nums2, 0, nums2.size()-1, median) < (nums1.size() + nums2.size()) / 2)
      {
        return median;
      }
      else
      {
        int median2 = std::max(nextSmallerNumber(nums1, median), nextSmallerNumber(nums2, median));
        return static_cast<double>(median2 + median) / 2;
      }
    }

    int nextSmallerNumber(const std::vector<int> &nums,
                          const int               value)
    {
      if (nums.size() == 0 || value <= nums.front())
        return INT_MIN;

      std::vector<int>::size_type left = 0, right = nums.size()-1;
      int last_smaller = 0;

      while (left < right)
      {
        std::vector<int>::size_type middle = (left + right) / 2;

        if (nums[middle] < value)
        {
          last_smaller = nums[middle];
          left = middle + 1;
        }
        else
        {
          right = middle - 1;
        }
      }

      if (nums[left] < value)
      {
        last_smaller = nums[left];
      }

      return last_smaller;
    }

    std::vector<int>::size_type lessThan(const std::vector<int>            &nums,
                                               std::vector<int>::size_type  left,
                                               std::vector<int>::size_type  right,
                                         const int                          value)
    {
      if (value > nums[right])
        return right - left + 1;

      if (value <= nums[left])
        return 0;

      std::vector<int>::size_type orig_left = left, last_left = left;

      while (left < right)
      {
        std::vector<int>::size_type middle = (left + right) / 2;

        if (nums[middle] < value)
        {
          last_left = middle;
          left = middle + 1;
        }
        else
        {
          right = middle - 1;
        }
      }

      if (nums[left] < value)
      {
        last_left = left;
      }

      return last_left - orig_left + 1;
    }
};

int main(void)
{
  Solution s;
  std::vector<int> nums1 = {1, 3};
  std::vector<int> nums2 = {2, 4};

  // std::cout << s.lessThan(nums2, 1, 3, 8) << '\n';
  std::cout << s.findMedianSortedArrays(nums1, nums2) << '\n';
  // std::cout << s.nextSmallerNumber(nums1, 5) << '\n';

  return 0;
}
