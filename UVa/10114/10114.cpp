#include <climits>

#include <iostream>
#include <vector>
#include <utility>

int main(void)
{
  int months_of_duration, number_of_depreciation_records;
  double down_payment, loan;

  while (std::cin >> months_of_duration
                  >> down_payment
                  >> loan
                  >> number_of_depreciation_records) {
    if (months_of_duration < 0)
      break;

    std::vector<std::pair<int, double>> depreciation_records;
    double value_of_loan, value_of_car, month_payment;
    int current_month;

    value_of_loan = loan;
    value_of_car = loan + down_payment;
    month_payment = loan / months_of_duration;

    for (int i = 0; i < number_of_depreciation_records; i++) {
      std::pair<int, double> record;
      std::cin >> record.first >> record.second;
      depreciation_records.push_back(record);
    }

    current_month = 0;
    for (int i = 0; i < number_of_depreciation_records; i++) {
      int next_depreciation_month = i+1 < number_of_depreciation_records
                                    ? depreciation_records[i+1].first : INT_MAX;
      double depreciation_percentage = depreciation_records[i].second;

      while (current_month < next_depreciation_month) {
        value_of_car -= value_of_car*depreciation_percentage;
        if (current_month != 0)
          value_of_loan -= month_payment;

        if (value_of_loan < value_of_car)
          break;

        current_month++;
      }

      if (value_of_loan < value_of_car)
        break;
    }

    if (current_month != 1)
      std::cout << current_month << " months" << std::endl;
    else
      std::cout << current_month << " month" << std::endl;
  }
  return 0;
}
