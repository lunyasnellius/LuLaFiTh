#pragma once
#include <Kokkos_Core.hpp>


/* 
 * 2-dim plaquette computation at location (t,x) for u1 field gauge
 */
//KOKKOS_FUNCTION
//theta plaquette(int t, int x, u1_field & gauge) {
//	theta tmp(gauge(t, x, T_DIR).val + gauge(t+1, x, X_DIR).val - gauge(t, x+1, T_DIR).val - gauge(t, x, X_DIR).val);
//	return tmp;
//}

// see meaning above ...
KOKKOS_FUNCTION
theta plaquette(theta& U_000, theta& U_101, theta& U_010, theta& U_001) {
	theta tmp(U_000.val + U_101.val - U_010.val - U_001.val);
	return tmp;
}

/*
 * function calculating the u1-gauge action 
 * for coupling strength beta and u1 field gauge
 */
double u1_action(double beta, u1_field & gauge) {
	double sum = 0.0;
	Kokkos::parallel_reduce("u1_action", Kokkos::MDRangePolicy<Kokkos::DefaultHostExecutionSpace,Kokkos::Rank<2>> ({0,0}, {N_DIM, N_DIM}), KOKKOS_LAMBDA(const int t, const int x, double & local_sum) {
		local_sum += (1.0 - real(plaquette(gauge(t,x,T_DIR), gauge(t+1,x,X_DIR), gauge(t,x+1,T_DIR), gauge(t,x,X_DIR))));
	}, sum);
	Kokkos::fence();
	//for (int x=0; x<N_DIM; ++x) {
	//	for (int t=0; t<N_DIM; ++t) {
	//		sum += (1.0 - real(plaquette(t, x, gauge)));
	//	}
	//}
	return beta * sum;
}

/*
 * function calculating the force from the u1-gauge action
 * at lattice point (t,x) on link in direction mu
 * as a function of beta and the u1 field gauge
 */
//KOKKOS_FUNCTION
void calculate_u1_force(Kokkos::View<double **[2], Kokkos::DefaultHostExecutionSpace> & force, double beta, u1_field & gauge) { //, int t, int x, int mu) {
	Kokkos::parallel_for("u1_force", Kokkos::MDRangePolicy<Kokkos::DefaultHostExecutionSpace,Kokkos::Rank<2>> ({0,0}, {N_DIM, N_DIM}), KOKKOS_LAMBDA(const int t, const int x) {
		force(t,x,T_DIR) = beta * (imag(plaquette(gauge(t,x,T_DIR), gauge(t+1,x,X_DIR), gauge(t,x+1,T_DIR), gauge(t,x,X_DIR))) 
			+ imag(theta(-1.0*plaquette(gauge(t,x-1,T_DIR), gauge(t+1,x-1,X_DIR), gauge(t,x,T_DIR), gauge(t,x-1,X_DIR)).val)));
		force(t,x,X_DIR) = beta * (imag(plaquette(gauge(t,x,T_DIR), gauge(t+1,x,X_DIR), gauge(t,x+1,T_DIR), gauge(t,x,X_DIR))) 
			+ imag(theta(-1.0*plaquette(gauge(t-1,x,T_DIR), gauge(t,x,X_DIR), gauge(t-1,x+1,T_DIR), gauge(t-1,x,X_DIR)).val)));
	});
	// old site-by-site implementation
	//if (mu == T_DIR) {
	//	return beta * (imag(plaquette(gauge(t,x,T_DIR), gauge(t+1,x,X_DIR), gauge(t,x+1,T_DIR), gauge(t,x,X_DIR))) 
	//		+ imag(theta(-1.0*plaquette(gauge(t,x-1,T_DIR), gauge(t+1,x-1,X_DIR), gauge(t,x,T_DIR), gauge(t,x-1,X_DIR)).val)));
	//} else {
	//	return beta * (imag(plaquette(gauge(t,x,T_DIR), gauge(t+1,x,X_DIR), gauge(t,x+1,T_DIR), gauge(t,x,X_DIR))) 
	//		+ imag(theta(-1.0*plaquette(gauge(t-1,x,T_DIR), gauge(t,x,X_DIR), gauge(t-1,x+1,T_DIR), gauge(t-1,x,X_DIR)).val)));
	//}
	Kokkos::fence();
}




