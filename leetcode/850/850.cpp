#include <cassert>
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#define MODULUS (1000000007)

class SegmentNode
{
  public:
    int count, area;

    SegmentNode(): count{0}, area{0}
    {
    }
};

class SegmentTree
{
  public:
    std::vector<SegmentNode> tree;
    std::vector<int> axis;
    std::unordered_map<int, std::vector<int>::size_type> map;

    SegmentTree(const std::vector<std::vector<int>> &rectangles)
      :tree{}, axis{}, map{}
    {
      std::set<int> set;
      for (const auto &rect: rectangles)
      {
        const auto x1 = rect[0], x2 = rect[2];
        set.emplace(x1);
        set.emplace(x2);
      }
      axis.insert(axis.end(), set.begin(), set.end());

      for (std::vector<int>::size_type i = 0; i < axis.size(); i++)
        map[axis[i]] = i;

      tree.resize(4 * axis.size());
    }

    void update(int x1, int x2, int value)
    {
      if (axis.size() == 0)
        return;

      const auto index1 = map[x1], index2 = map[x2];
      update(0, 0, axis.size()-1, index1, index2-1, value);
    }

    unsigned int query()
    {
      if (axis.size() == 0)
        return 0;

      return tree[0].area;
    }

    void update(const std::vector<SegmentNode>::size_type i,
                const std::vector<SegmentNode>::size_type left,
                const std::vector<SegmentNode>::size_type right,
                const std::vector<SegmentNode>::size_type qleft,
                const std::vector<SegmentNode>::size_type qright,
                const int value)
    {
      if (left > qright || right < qleft)
        return;

      if (left >= qleft && right <= qright)
      {
        tree[i].count += value;

        if (tree[i].count != 0)
          tree[i].area = (axis[right+1] - axis[left]) % MODULUS;
        else if (left != right)
          tree[i].area = (tree[2*i+1].area + tree[2*i+2].area) % MODULUS;
        else
          tree[i].area = 0;

        return;
      }

      const auto mid = left + (right - left) / 2;
      update(2*i+1, left, mid, qleft, qright, value);
      update(2*i+2, mid+1, right, qleft, qright, value);

      if (tree[i].count != 0)
        tree[i].area = (axis[right+1] - axis[left]) % MODULUS;
      else
        tree[i].area = (tree[2*i+1].area + tree[2*i+2].area) % MODULUS;
    }
};

class Event
{
  public:
    int y, x1, x2, value;

    Event(int y, int x1, int x2, int value):
      y{y}, x1{x1}, x2{x2}, value{value}
    {
    }

    friend bool operator<(const Event &lft, const Event &rht)
    {
      return lft.y <= rht.y;
    }
};

class Solution
{
  public:
    int rectangleArea(const std::vector<std::vector<int>>& rectangles)
    {
      if (rectangles.size() == 0)
        return 0;

      std::vector<Event> events;
      for (const auto &rect: rectangles)
      {
        const auto x1 = rect[0], y1 = rect[1], x2 = rect[2], y2 = rect[3];
        events.emplace_back(y1, x1, x2, 1);
        events.emplace_back(y2, x1, x2, -1);
      }
      std::sort(std::begin(events), std::end(events));

      SegmentTree tree(rectangles);
      auto prev_y = events[0].y;
      int area = 0;
      for (const auto &event: events)
      {
        const auto current_area = (1ULL * (event.y - prev_y) * tree.query()) % MODULUS;
        area = (area + current_area) % MODULUS;
        tree.update(event.x1, event.x2, event.value);
        prev_y = event.y;
      }

      return area;
    }
};

int main()
{
  Solution s;
  assert(s.rectangleArea({{0,0,3,3},{2,0,5,3},{1,1,4,4}}) == 18);
  assert(s.rectangleArea({{0,0,2,2}}) == 4);
  assert(s.rectangleArea({{0,0,2,2},{1,0,2,3}}) == 5);
  assert(s.rectangleArea({{0,0,2,2},{1,0,2,3},{1,0,3,1}}) == 6);
  assert(s.rectangleArea({{0,0,1000*1000*1000,1000*1000*1000}}) == 49);
  assert(s.rectangleArea({{224386961,128668997,546647847,318900555},{852286866,238086790,992627088,949888275},{160239672,137108804,398130330,944807066},{431047948,462092719,870611028,856851714},{736895365,511285772,906155231,721626624},{289309389,607009433,558359552,883664714},{780746435,397872372,931219192,863727103},{573523994,124874359,889018012,471879750},{619886375,149607927,727026507,446976526},{51739879,716225241,115331335,785850603},{171077223,267051983,548436248,349498903},{314437215,169054168,950814572,481179241},{64126215,646689712,595562376,829164135},{926011655,481539702,982179297,832455610},{40370235,231510218,770233582,851797196},{292546319,45032676,413358795,783606009},{424366277,369838051,453541063,777456024},{211837048,142665527,217366958,952362711},{228416869,402115549,672143142,644930626},{755018294,194555696,846854520,939022548},{192890972,586071668,992336688,759060552},{127869582,392855032,338983665,954245205},{665603955,208757599,767586006,276627875},{260384651,10960359,736299693,761411808},{46440611,559601039,911666265,904518674},{54013763,90331595,332153447,106222561},{73093292,378586103,423488105,826750366},{327100855,516514806,676134763,653520887},{930781786,407609872,960671631,510621750},{35479655,449171431,931212840,617916927}}) == 862275791);
  return 0;
}
