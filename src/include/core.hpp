#pragma once
#include <numbers>


double pi_val = std::numbers::pi_v<double>;

enum dir {
	T_DIR = 0,
	X_DIR = 1
};


double constrain(double angle) {
	double tmp = angle;
	if (angle >= 1.0) {
		while (tmp >= 1.0) tmp -= 2.0;
		return tmp;
	} else if (angle < -1.0) {
		while (tmp < -1.0) tmp += 2.0;
		return tmp;
	} else {
		return tmp;
	}
}

int periodic(int index) {
	if (index < 0) {
		return 8 + index;
	} else if (index > 7) {
		return index - 8;
	} else {
		return index;
	}
}


