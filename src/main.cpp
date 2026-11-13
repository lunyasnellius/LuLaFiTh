#include "include.hpp"


int main(int argc, char* argv[]) {
	Kokkos::initialize(argc, argv);

	u1_field gauge;
	u1_field gauge_backup;
	u1_field momenta;
	Kokkos::View<double **[2], Kokkos::DefaultHostExecutionSpace> force("force", N_DIM, N_DIM);

	double beta_dynamics = 4.62;
	double beta_sample = 4.6;

	std::random_device rd{};
	int seed1 = rd();
	int seed2 = rd();
	int seed3 = rd();

	double time = 1.0;
	int N_time = 16;

	int N_steps = 1000;

	gauge_backup.randomize(seed1);
	momenta.randomize(seed2);

	double ham_start;
	double ham_end;
	double ac_prob;
	double loop_av;

	gauge_backup.print_file("u1_g_field", "seed = " + std::to_string(seed1));

	int num_acc = 0;
	int i = 0;

	std::string csv_file_name = std::to_string(N_DIM) + "_loop_val.csv";
	std::fstream file(csv_file_name, std::fstream::out | std::fstream::app);
	file << "N_it,loop_av\n";
	//for (int i=0; i<N_steps; ++i) {
	while (num_acc < 50) {
		gauge = gauge_backup;
		//std::cout << "Step " << i+1 << " of " << N_steps;
		seed2 = rd();
		momenta.randomize(seed2);
		ham_start = u1_hamilton(beta_sample, gauge, momenta);
		//std::cout << ";\tH_start = " << ham_start;

		calculate_u1_force(force, beta_dynamics, gauge);
		leapfrog(time, N_time, force, momenta, gauge);

		ham_end = u1_hamilton(beta_sample, gauge, momenta);

		//std::cout << ";\tH_end = " << ham_end;

		ac_prob = acc_rate(ham_start, ham_end);

		if (acc_ensemble(ac_prob, seed3)) {
			gauge_backup = gauge;
			//gauge_backup.print_file("u1_g_field", "seed = " + std::to_string(seed1) + ", accept/reject seed = " + std::to_string(seed3) + " acceptance rate = " + std::to_string(ac_prob));
			//std::cout << ";\taccepted;\tac_rate = " << ac_prob << std::endl;
			++num_acc;
			printf("%.3e (!)\t", ac_prob);
			if (num_acc%10 == 0) printf("\n");//std::cout << "\n";
			loop_av = u1_loop(gauge_backup);
			file << num_acc << "," << std::scientific << loop_av << "\n";
		} //else {
			//std::cout << ";\trejected;\tac_rate = " << ac_prob << std::endl;
			//printf("%.3e\t", ac_prob);
		//}

		++i;
	}
	file.close();

	std::cout << "\nnumber of accepted ensembles: " << num_acc << std::endl;


	//gauge_backup.load_file("ensembles/u1_g_field_00.csv");


	Kokkos::finalize();

	return 0;

}


