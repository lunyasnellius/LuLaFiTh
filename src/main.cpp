#include "include.hpp"


int main() {

	u1_field gauge(0.9, -0.7);


	double beta = 9.5;

	double out = u1_action(beta, gauge);

	std::cout << "the output val is " << out << std::endl;

	gauge.randomize(42);
	out = u1_action(beta, gauge);

	std::cout << "the output val after randomization is " << out << std::endl;

	return 0;

}


