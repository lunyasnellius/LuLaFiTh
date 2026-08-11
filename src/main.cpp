#include "include.hpp"


int main() {

	u1_field gauge(0.9, -0.7);
	u1_field momenta(0.9, -0.7);

	double beta = 9.5;

	double out = u1_action(beta, gauge);
	double ham = u1_hamilton(beta, gauge, momenta);

	std::cout << "the action is \t\t" << out << std::endl;
	std::cout << "the hamiltonian is\t" << ham << std::endl;

	gauge.randomize(42);
	momenta.randomize(13);
	out = u1_action(beta, gauge);
	ham = u1_hamilton(beta, gauge, momenta);

	std::cout << "\nafter randomization:\nthe action is \t\t" << out << std::endl;
	std::cout << "the hamiltonian is\t" << ham << std::endl;

	std::cout << "sample link:\t\t" << gauge(1,1,0).val << std::endl;
	std::cout << "sample mom:\t\t" << momenta(1,1,0).val << std::endl;

	double time = 95.0;
	int N = 1000;

	//leapfrog(time, N, beta, momenta, gauge);
	update_links(time, momenta, gauge);
	update_momentum(time, beta, momenta, gauge);

	out = u1_action(beta, gauge);
	ham = u1_hamilton(beta, gauge, momenta);

	std::cout << "\nafter leapfrog with (time, N_steps) = (" << time << ", " << N << "):" << std::endl;
	std::cout << "the action is \t\t" << out << std::endl;
	std::cout << "the hamiltonian is\t" << ham << std::endl;

	std::cout << "sample link:\t\t" << gauge(1,1,0).val << std::endl;
	std::cout << "sample mom:\t\t" << momenta(1,1,0).val << std::endl;


	return 0;

}


