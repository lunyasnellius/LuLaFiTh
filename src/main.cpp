#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>

#include "include.hpp"


int main() {

	u1_field gauge;
	u1_field momenta;

	double beta_dynamics = 2.5;
	double beta_sample = 1.5;

	gauge.randomize(42);
	momenta.randomize(13);

	gauge.print();

	double out = u1_action(beta_dynamics, gauge);
	double ham_start = u1_hamilton(beta_sample, gauge, momenta);

	std::cout << "\nafter randomization:\nthe action is \t\t" << out << std::endl;
	std::cout << "the hamiltonian is\t" << ham_start << std::endl;


	double time = 0.95;
	int N = 100;

	leapfrog(time, N, beta_dynamics, momenta, gauge);

	out = u1_action(beta_dynamics, gauge);
	double ham_end = u1_hamilton(beta_sample, gauge, momenta);

	double ac_prob = acc_rate(ham_start, ham_end);

	std::cout << "\nafter leapfrog with (time, N_steps) = (" << time << ", " << N << "):" << std::endl;
	std::cout << "the action is \t\t" << out << std::endl;
	std::cout << "the hamiltonian is\t" << ham_end << std::endl;



	return 0;

}


