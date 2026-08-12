#include "time-ev.hpp"


double acc_rate(double H_start, double H_end) {
	double tmp = H_end - H_start;
	if (tmp <= 0.0) {
		return 1.0;
	} else {
		return std::exp(-1.0 * tmp);
	}
}



