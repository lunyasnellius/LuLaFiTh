#pragma once



double real(theta link) {
	return std::cos(pi_val * link.val);
}

double imag(theta link) {
	return std::sin(pi_val * link.val);
}

std::complex<double> evaluate(theta link) {
	return std::complex<double>(real(link),imag(link));
}

//theta dag(theta link) {
//	link.val *= -1.0;
//	return link;
//}


