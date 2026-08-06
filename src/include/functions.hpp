#pragma once

#include "core.hpp"
#include "../u1-field.hpp"


double real(theta link) {
	return std::cos(pi_val * link.val);
}

double imag(theta link) {
	return std::sin(pi_val * link.val);
}

theta dag(theta link) {
	link.val *= -1.0;
	return link;
}


