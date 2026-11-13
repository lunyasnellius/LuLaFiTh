#pragma once 



/*
 * H = 1/2 * pi^2 + S_G
 */
double u1_hamilton(double beta, u1_field & gauge, u1_field & momenta) {
	double ham = 0.0;
	double tmp1(0.0);
	double tmp2(0.0);
	// calculate sum of all pi^2
	Kokkos::parallel_reduce("u1_hamilton", Kokkos::MDRangePolicy<Kokkos::DefaultHostExecutionSpace,Kokkos::Rank<2>> ({0,0}, {N_DIM, N_DIM}), KOKKOS_LAMBDA(const int t, const int x, double & local_sum) {
		local_sum += momenta(t,x,T_DIR).val * momenta(t,x,T_DIR).val + momenta(t,x,X_DIR).val * momenta(t,x,X_DIR).val;
	}, ham);
	Kokkos::fence();
	//for (int x=0; x<N_DIM; ++x) {
	//	for (int t=0; t<N_DIM; ++t) {
	//		tmp1 = momenta(t,x,T_DIR).val * momenta(t,x,T_DIR).val;
	//		tmp2 = momenta(t,x,X_DIR).val * momenta(t,x,X_DIR).val;
	//		ham += tmp1 + tmp2;
	//	}
	//}
	// factor 1/2 for kinetic part
	ham *= 0.5;
	// add gauge action
	ham += u1_action(beta, gauge);
	return ham;
}


