#include "RunningStats.h"

// Constructor to initialize running sums and count
RunningStats::RunningStats() {
    reset();
}

// Update running sums and count with a new data point x
void RunningStats::update(float x) {

    // Check for invalid input
    // adding isnan(x)?
    if (!isfinite(x)) {
        // Handle the error
        return;
    }

    // Incremental update of running mean and variance using Welford's method
    // More numerically stable and more efficient
    n++;
    float delta = x - mean_x;
    mean_x += delta / n;
    m2 += delta * (x - mean_x);
}

// Calculate and return the mean of the data seen so far
float RunningStats::mean() {
    return mean_x;
}

// Calculate and return the standard deviation of the data seen so far
float RunningStats::std() {
    return sqrt(variance());
}

// Calculate and return the variance of the data seen so far
float RunningStats::variance() {
    if (n < 2) {
        return 0;
    } else {
        return m2 / (n - 1);
    }
}

// Reset runnign sums and count to zero
void RunningStats::reset() {
    m2 = 0;
    mean_x = 0;
    n = 0;
}