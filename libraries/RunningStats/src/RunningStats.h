#ifndef RunningStats_h
#define RunningStats_h

#include <Arduino.h>

class RunningStats {
  private:
    float m2; // Running sum of squared difference from mean
    float mean_x; // Running sum of x values
    int n; // Number of data points seen so far

  public:
    // Constructor to initialize running sums and count
    RunningStats();
    
    // Update running sums and count with a new data point x
    void update(float x);
    
    // Calculate and return the mean of the data seen so far
    float mean();
    
    // Calculate and return the standard deviation of the data seen so far
    float std();
    
    // Calculate and return the variance of the data seen so far
    float variance();

    // Reset all the values to zero
    void reset();
};

#endif