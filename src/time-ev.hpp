#pragma once

#include "u1-hamilton.hpp"

momentum staple(int t, int x, int dir, u1_field & gauge) {
	momentum tmp_mom(0.0);
	if (dir == T_DIR) {
		theta tmp1 = gauge(t, x, X_DIR) * gauge(t, x+1, T_DIR) * dag(gauge(t+1, x, X_DIR));
		theta tmp1 = dag(gauge(t, x, X_DIR)) * gauge(t, x-1, T_DIR) * gauge(t+1, x, X_DIR);
		tmp_mom.val = tmp1.val + tmp2.val;
	} else {
		theta tmp1 = gauge(t, x, T_DIR) * gauge(t+1, x, X_DIR) * dag(gauge(t, x+1, T_DIR));
		theta tmp1 = dag(gauge(t, x, T_DIR)) * gauge(t-1, x, X_DIR) * gauge(t, x+1, T_DIR);
		tmp_mom.val = tmp1.val + tmp2.val;
	}
	return tmp_mom;
}

void update_momentum(double del_tau, p_field & momenta, u1_field & gauge) {
	for (int t=0; t<8; ++t) {
		for (int x=0; x<8; ++x) {
			momenta(t, x, T_DIR) -= del_tau * staple(t, x, T_DIR, gauge);
			momenta(t, x, X_DIR) -= del_tau * staple(t, x, X_DIR, gauge);
		}
	}
}

void update_links(double del_tau, p_field & momenta, u1_field & gauge) {
}





