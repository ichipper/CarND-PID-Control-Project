#include "PIDOptimizer.h"
#include <iostream>


PIDOptimizer::PIDOptimizer(PID* pid) {
  this->pid = pid;
}
PIDOptimizer::~PIDOptimizer() {}

void PIDOptimizer::Initialize(double Kp, double Ki, double Kd, double Kp_d, double Ki_d, double Kd_d) {
  total_error = 0.0;
  best_error = 9999;
  p = {Kp, Ki, Kd};
  dp = {Kp_d, Ki_d, Kd_d};
  i = 0;
  count = 0;
  pos_search = true;
  p[i] += dp[i];
  std::cout << "==========p[" << i << "] += dp[" << i << "]" << std::endl;
  pid->Init(p[0], p[1], p[2]);
}
void PIDOptimizer::Twiddle(double cte) {
  //i, pos_search, count
  //Every time there is new data point coming in, update the total error
  total_error += cte*cte;
  //std::cout << "total_error=" << total_error << std::endl;
  if (count==799) { //End of an eval
    //Get average of the total error;
  std::cout << "===============i=" << i;
  if (pos_search) std::cout << " positive search" << std::endl;
  else std::cout << " negative search" << std::endl;
    total_error /= (count+1);
    if (total_error<best_error) {
      if (pos_search) {
        best_error = total_error;
        best_p = {p[0], p[1], p[2]};
        dp[i] *= 1.1;
      }
      else {
        best_error = total_error;
        best_p = {p[0], p[1], p[2]};
        dp[i] *= 1.1;
      }
      std::cout << "==========search succeeded, move to next parameter" << std::endl;
      i=(i+1)%3;//Proceed to next parameter
      pos_search = true;
      p[i] += dp[i];
    }
    else {
      if (pos_search) {
        std::cout << "==========search failed, move to negative search" << std::endl;
        pos_search = false;
        p[i] -= 2*dp[i];
      }
      else {
        std::cout << "==========search failed, restore dp[i]" << std::endl;
        p[i] += dp[i];
        dp[i] *= 0.9;
        i=(i+1)%3;//Proceed to next parameter
        pos_search = true;
      }
    }
    
    std::cout << "========================================" << std::endl;
    std::cout << "best error=" << best_error << " best Kp=" << best_p[0] 
      << " best Ki=" << best_p[1] << " best Kd=" << best_p[2] << std::endl;
    std::cout << "current error=" << total_error << " Kp=" << p[0] << " Ki=" << p[1]
      << " Kd=" << p[2] << " Kp_d=" << dp[0] << " Ki_d=" << dp[1] << " Kd_d=" << dp[2]
      << std::endl;
    std::cout << "========================================" << std::endl;
    //End of evaluation
    count = 0;
    total_error = 0.0;
    pid->Init(p[0], p[1], p[2]);
    
  }
  else {
    count++;
  }

}
void PIDOptimizer::ShowBestParameters() {
    std::cout << "best error=" << best_error << " best Kp=" << best_p[0] 
      << " best Ki=" << best_p[1] << " best Kd=" << best_p[2] << std::endl;
}
