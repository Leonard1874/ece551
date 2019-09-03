#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;
//calculate year
int cal_year(int n) {
  int y = n / 12;
  return y;
}
//calculate month
int cal_month(int n) {
  int m = n % 12;
  return m;
}
// calculate balance work
double balance_work(double N, double x, double y) {
  N = N + N * x;
  N += y;
  return N;
}
//calculate balance retire
double balance_retire(double N, double x, double y) {
  N = N + N * x;
  N -= y;
  return N;
}
void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  int wm = working.months;
  int rm = retired.months;
  int year = 0;
  int month = 0;
  double balance = initial;
  double wr = working.rate_of_return;
  double rr = retired.rate_of_return;
  double wc = working.contribution;
  double rc = retired.contribution;
  int s = startAge;
  for (int i = 0; i < wm; i++) {
    year = cal_year(s + i);
    month = cal_month(s + i);
    printf("Age %3d month %2d you have $%.2f \n", year, month, balance);
    balance = balance_work(balance, wr, wc);
  }
  for (int j = 0; j < rm; j++) {
    year = cal_year(s + wm + j);
    month = cal_month(s + wm + j);
    printf("Age %3d month %2d you have $%.2f \n", year, month, balance);
    balance = balance_retire(balance, rr, rc);
  }
  return;
}

int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000.0;
  double wr = 0.045 / 12;
  working.rate_of_return = wr;
  retire_info retired;
  retired.months = 384;
  retired.contribution = 4000.0;
  double rr = 0.01 / 12;
  retired.rate_of_return = rr;
  retirement(327, 21345.0, working, retired);
  return 0;
}
