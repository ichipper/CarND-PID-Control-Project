#ifndef PIDOptimizer_H
#define PIDOptimizer_H
#include <vector>
#include "PID.h"

using std::vector;

class PIDOptimizer {
  public:
    PIDOptimizer(PID* pid);
    ~PIDOptimizer();
    void Initialize(double Kp, double Ki, double Kd, double Kp_d, double Ki_d, double Kd_d);
    void Twiddle(double cte);
    void ShowBestParameters();

  private:
    vector<double> p;
    vector<double> dp;
    vector<double> best_p;
    double total_error;
    double best_error;
    int i;
    int count;
    bool pos_search;
    PID* pid;

};

#endif
