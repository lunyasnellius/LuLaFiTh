#pragma once



void update_momentum(double del_tau, double beta, u1_field & momenta, u1_field & gauge) {
	for (int t=0; t<N_DIM; ++t) {
		for (int x=0; x<N_DIM; ++x) {
			momenta(t, x, T_DIR) = momenta(t, x, T_DIR).val - del_tau * u1_force(beta, gauge, t, x, T_DIR);
			momenta(t, x, X_DIR) = momenta(t, x, X_DIR).val - del_tau * u1_force(beta, gauge, t, x, X_DIR);
		}
	}
}

void update_links(double del_tau, u1_field & momenta, u1_field & gauge) {
	for (int t=0; t<N_DIM; ++t) {
		for (int x=0; x<N_DIM; ++x) {
			gauge(t, x, T_DIR) = del_tau * momenta(t, x, T_DIR).val + gauge(t, x, T_DIR).val;
			gauge(t, x, X_DIR) = del_tau * momenta(t, x, X_DIR).val + gauge(t, x, X_DIR).val;
		}
	}
}

void leapfrog(double t_step, int num_steps, double beta, u1_field & momenta, u1_field & gauge) {
	double del_tau = t_step/((double) num_steps);

	// initial half step of the momentum
	update_momentum((del_tau/2.0), beta, momenta, gauge);

	// intermediate steps, alternatingly updating links and momenta
	for (int t=0; t<num_steps-1; ++t) {
		update_links(del_tau, momenta, gauge);
		update_momentum(del_tau, beta, momenta, gauge);
	}

	// final full step update to links
	update_links(del_tau, momenta, gauge);
	// final half step update to momenta
	update_momentum((del_tau/2.0), beta, momenta, gauge);
}





