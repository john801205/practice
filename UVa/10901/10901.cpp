#include <iostream>
#include <string>
#include <list>

class Car {
  public:
    int index, arrival_time;
    bool arrival_left;

    Car(int i, int t, bool p): index(i), arrival_time(t), arrival_left(p) { }
};

int main(void)
{
  int number_of_test_cases;

  while (std::cin >> number_of_test_cases) {
    for (int case_ = 0; case_ < number_of_test_cases; case_++) {
      if (case_ != 0)
        std::cout << std::endl;

      int max_loaded_cars, transport_time, max_waiting_cars;
      std::list<Car> waiting_cars;

      std::cin >> max_loaded_cars >> transport_time >> max_waiting_cars;
      for (int i = 0; i < max_waiting_cars; i++) {
        std::string pos;
        int time;

        std::cin >> time >> pos;
        if (pos.compare("left") == 0)
          waiting_cars.push_back(Car(i, time, true));
        else
          waiting_cars.push_back(Car(i, time, false));
      }

      int *result = new int[max_waiting_cars];
      bool current_pos_left = true;
      int current_time = 0;

      for (int i = 0; i < max_waiting_cars; i++)
        result[i] = 0;

      while (!waiting_cars.empty()) {
        // load as many cars as possible
        int count = 0;
        for (auto it = waiting_cars.begin(); it != waiting_cars.end(); ) {
          if (count >= max_loaded_cars)
            break;

          if (it->arrival_time > current_time)
            break;

          if (it->arrival_left == current_pos_left) {
            result[it->index] = current_time + transport_time;
            it = waiting_cars.erase(it);
            count++;
          } else {
            it++;
          }
        }

        if (count != 0) {
          // cross the river if any car is loaded
          current_time += transport_time;
          current_pos_left = !current_pos_left;
        } else {
          // wait for the next car
          Car first = waiting_cars.front();
          if (first.arrival_time > current_time)
            current_time = first.arrival_time;

          // if the next car is on the opposite side
          if (first.arrival_left != current_pos_left) {
            current_time += transport_time;
            current_pos_left = !current_pos_left;
          }
        }
      }

      for (int i = 0; i < max_waiting_cars; i++)
        std::cout << result[i] << std::endl;

      delete[] result;
    }
  }

  return 0;
}
