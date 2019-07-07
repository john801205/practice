#include <map>
#include <string>
#include <unordered_map>

class TimeMap
{
  private:
    std::unordered_map<std::string, std::map<int, std::string>> map;
  public:
    /** Initialize your data structure here. */
    TimeMap(): map{} {

    }

    void set(const std::string &key, const std::string &value, int timestamp) {
      map[key][timestamp] = value;
    }

    std::string get(const std::string &key, int timestamp) {
      const auto itr1 = map.find(key);
      if (itr1 == map.end())
        return "";

      const auto &data = itr1->second;
      const auto itr2 = data.upper_bound(timestamp);
      if (itr2 == data.begin())
        return "";

      return std::prev(itr2)->second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
int main()
{
  return 0;
}
