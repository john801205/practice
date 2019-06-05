#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#define MODULUS (1000000007)

class QuadNode
{
  public:
    bool value;
    QuadNode *children[4];

    QuadNode(): value{false}, children{}
    {
      for (int i = 0; i < 4; i++)
        children[i] = nullptr;
    }

    ~QuadNode()
    {
      for (int i = 0; i < 4; i++)
        if (children[i] != nullptr)
          delete children[i];
    }
};

class QuadTree
{
  public:
    QuadNode *root;
    std::vector<int> axisX, axisY;

    QuadTree(const std::vector<std::vector<int>> &rectangles)
      :root{nullptr}, axisX{}, axisY{}
    {
      root = new QuadNode();

      std::set<int> setX, setY;
      for (const auto &rect: rectangles)
      {
        const auto x1 = rect[0], y1 = rect[1], x2 = rect[2], y2 = rect[3];
        setX.emplace(x1);
        setX.emplace(x2);
        setY.emplace(y1);
        setY.emplace(y2);
      }

      axisX.insert(axisX.end(), setX.begin(), setX.end());
      axisY.insert(axisY.end(), setY.begin(), setY.end());
    }

    ~QuadTree()
    {
      delete root;
    }

    void update(const std::vector<int> &rect)
    {
      if (axisX.size() == 0 || axisY.size() == 0)
        return;

      update(root, 0, 0, axisX.size()-1, axisY.size()-1, rect);
    }

    unsigned int query()
    {
      if (axisX.size() == 0 || axisY.size() == 0)
        return 0;

      return query(root, 0, 0, axisX.size()-1, axisY.size()-1);
    }

    void update(QuadNode *root,
                const std::vector<int>::size_type indexX1,
                const std::vector<int>::size_type indexY1,
                const std::vector<int>::size_type indexX2,
                const std::vector<int>::size_type indexY2,
                const std::vector<int> &query)
    {
      if (root->value)
        return;

      const auto x1 = axisX[indexX1], y1 = axisY[indexY1];
      const auto x2 = axisX[indexX2], y2 = axisY[indexY2];
      const std::vector<int> rect({x1, y1, x2, y2});

      if (!intersect(rect, query))
        return;

      if (contains(query, rect))
      {
        root->value = true;
        for (int i = 0; i < 4; i++)
        {
          if (root->children[i] == nullptr)
          {
            delete root->children[i];
            root->children[i] = nullptr;
          }
        }

        return;
      }

      for (int i = 0; i < 4; i++)
        if (root->children[i] == nullptr)
          root->children[i] = new QuadNode();

      const auto midX = indexX1 + (indexX2 - indexX1) / 2;
      const auto midY = indexY1 + (indexY2 - indexY1) / 2;

      update(root->children[0], indexX1, indexY1, midX, midY, query);
      update(root->children[1], midX, indexY1, indexX2, midY, query);
      update(root->children[2], indexX1, midY, midX, indexY2, query);
      update(root->children[3], midX, midY, indexX2, indexY2, query);
    }

    unsigned int query(QuadNode *root,
                       const std::vector<int>::size_type indexX1,
                       const std::vector<int>::size_type indexY1,
                       const std::vector<int>::size_type indexX2,
                       const std::vector<int>::size_type indexY2)
    {
      if (root == nullptr)
        return 0;

      const auto x1 = axisX[indexX1], y1 = axisY[indexY1];
      const auto x2 = axisX[indexX2], y2 = axisY[indexY2];
      const std::vector<int> rect({x1, y1, x2, y2});

      if (root->value)
        return area(rect);

      const auto midX = indexX1 + (indexX2 - indexX1) / 2;
      const auto midY = indexY1 + (indexY2 - indexY1) / 2;

      const auto q1 = query(root->children[0], indexX1, indexY1, midX, midY);
      const auto q2 = query(root->children[1], midX, indexY1, indexX2, midY);
      const auto q3 = query(root->children[2], indexX1, midY, midX, indexY2);
      const auto q4 = query(root->children[3], midX, midY, indexX2, indexY2);

      return ((q1 + q2) % MODULUS + (q3 + q4) % MODULUS) % MODULUS;
    }

    bool intersect(const std::vector<int> &A,
                   const std::vector<int> &B)
    {
      const auto Ax1 = A[0], Ay1 = A[1], Ax2 = A[2], Ay2 = A[3];
      const auto Bx1 = B[0], By1 = B[1], Bx2 = B[2], By2 = B[3];

      if (Ax1 >= Bx2 || Ax2 <= Bx1)
        return false;

      if (Ay1 >= By2 || Ay2 <= By1)
        return false;

      return true;
    }

    bool contains(const std::vector<int> &A,
                  const std::vector<int> &B)
    {
      const auto Ax1 = A[0], Ay1 = A[1], Ax2 = A[2], Ay2 = A[3];
      const auto Bx1 = B[0], By1 = B[1], Bx2 = B[2], By2 = B[3];

      return Ax1 <= Bx1 && Ax2 >= Bx2 && Ay1 <= By1 && Ay2 >= By2;
    }

    unsigned int area(const std::vector<int> &A)
    {
      const auto Ax1 = A[0], Ay1 = A[1], Ax2 = A[2], Ay2 = A[3];
      return (1ULL * (Ax2 - Ax1) * (Ay2 - Ay1)) % MODULUS;
    }
};

class Solution
{
  public:
    int rectangleArea(const std::vector<std::vector<int>>& rectangles)
    {
      QuadTree tree(rectangles);
      for (const auto &rect: rectangles)
        tree.update(rect);
      return tree.query();
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
