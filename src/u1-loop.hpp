#pragma once


double u1_loop(u1_field & gauge) {
	double sum = 0.0;
	Kokkos::parallel_reduce("u1_action", Kokkos::MDRangePolicy<Kokkos::DefaultHostExecutionSpace,Kokkos::Rank<2>> ({0,0}, {N_DIM, N_DIM}), KOKKOS_LAMBDA(const int t, const int x, double & local_sum) {
		local_sum += real(plaquette(gauge(t,x,T_DIR), gauge(t+1,x,X_DIR), gauge(t,x+1,T_DIR), gauge(t,x,X_DIR)));
	}, sum);
	//for (int x=0; x<N_DIM; ++x) {
	//	for (int t=0; t<N_DIM; ++t) {
	//		sum += real(plaquette(t, x, gauge));
	//	}
	//}
	Kokkos::fence();
	return sum/((double) (N_DIM*N_DIM));
}
