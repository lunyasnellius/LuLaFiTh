#include "include.hpp"


int main() {

	u1_field gauge;
	u1_field gauge_backup;
	u1_field momenta;

	double beta_dynamics = 4.62;
	double beta_sample = 4.6;

	std::random_device rd{};
	int seed1 = rd();
	int seed2 = rd();
	int seed3 = rd();

	double time = 1.0;
	int N_time = 16;

	int N_steps = 100;

	gauge_backup.randomize(seed1);
	momenta.randomize(seed2);

	double ham_start;
	double ham_end;
	double ac_prob;

	gauge_backup.print_file("u1_g_field", "seed =" + std::to_string(seed1));

	int num_acc = 0;

	for (int i=0; i<N_steps; ++i) {
		gauge = gauge_backup;
		//std::cout << "Step " << i+1 << " of " << N_steps;
		seed2 = rd();
		momenta.randomize(seed2);
		ham_start = u1_hamilton(beta_sample, gauge, momenta);
		//std::cout << ";\tH_start = " << ham_start;

		leapfrog(time, N_time, beta_dynamics, momenta, gauge);

		ham_end = u1_hamilton(beta_sample, gauge, momenta);

		//std::cout << ";\tH_end = " << ham_end;

		ac_prob = acc_rate(ham_start, ham_end);

		if (acc_ensemble(ac_prob, seed3)) {
			gauge_backup = gauge;
			gauge_backup.print_file("u1_g_field", "seed = " + std::to_string(seed1) + ", accept/reject seed = " + std::to_string(seed3) + " acceptance rate = " + std::to_string(ac_prob));
			//std::cout << ";\taccepted;\tac_rate = " << ac_prob << std::endl;
			++num_acc;
		} else {
			//std::cout << ";\trejected;\tac_rate = " << ac_prob << std::endl;
		}
		printf("%.3e\t", ac_prob);
		if (i%10 == 9) std::cout << "\n";
	}

	std::cout << "\nnumber of accepted ensembles: " << num_acc << std::endl;


	return 0;

}


