#pragma once
#include <cmath>
#include <array>
#include <numbers>
#include <iostream>

#include "include/core.hpp"
#include "include/functions.hpp"
#include "u1-field.hpp"


double u1_action(double beta, u1_field & gauge) {
	double sum = 0.0;
	for (int x=0; x<8; ++x) {
		for (int t=0; t<8; ++t) {
			sum -= real( gauge(t, x, T_DIR) * gauge(t+1, x, X_DIR) * dag(gauge(t, x+1, T_DIR) * gauge(t, x, X_DIR)) );
		}
		//printf("(t,x)=(%i,%i) plaq=e^(i*%.3e) sum=%.6e \n",7,x,plaq.val,sum); 
		//printf("U_T(n)~%.1e U_X(n+t)~%.1e U+_T(n+x)~%.1e U+_X(n)~%.1e\n",gauge(7, x, T_DIR).val,gauge(7+1, x, X_DIR).val,dag(gauge(7, x+1, T_DIR)).val,dag(gauge(7, x, X_DIR)).val);
	}
	//std::cout << "beta = " << beta << " sum = " << sum << std::endl;
	return beta * sum / 2.0;
}

