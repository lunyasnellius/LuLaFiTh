#pragma once
#include <Kokkos_Core.hpp>


struct theta {
	// theta values between -1 and 1
	double val;

	theta() {
		val = 0.0;
	}
	theta(double value) {
		val = constrain(value);
	}

	theta& operator=(theta other) {
		val = constrain(other.val);
		return *this;
	}

	theta& operator=(double other) {
		val = constrain(other);
		return *this;
	}


}; // end of theta


void fill_view(Kokkos::View<theta**[2], Kokkos::DefaultHostExecutionSpace> &field_view, double value) {
	Kokkos::parallel_for("fill_view", Kokkos::MDRangePolicy<Kokkos::DefaultHostExecutionSpace,Kokkos::Rank<2>> ({0,0}, {field_view.extent(0), field_view.extent(1)}), KOKKOS_LAMBDA(const int i, const int j) {
		field_view(i,j,0) = value;
		field_view(i,j,1) = value;
	});
	Kokkos::fence();
}

void fill_view_random(Kokkos::View<theta**[2], Kokkos::DefaultHostExecutionSpace> &field_view, const int seed) {
	Kokkos::parallel_for("fill_view_random", Kokkos::MDRangePolicy<Kokkos::DefaultHostExecutionSpace,Kokkos::Rank<2>> ({0,0}, {field_view.extent(0), field_view.extent(1)}), KOKKOS_LAMBDA(const int i, const int j) {
		random_theta random(seed + i*field_view.extent(1) + j);
		//double tmp = random();
		field_view(i,j,0) = random();//tmp;
		//tmp = random();
		field_view(i,j,1) = random();//tmp;
	});
	Kokkos::fence();
}

struct u1_field {
	// for an 8x8 lattice
	Kokkos::View<theta**[2],Kokkos::DefaultHostExecutionSpace> thetas;
	//std::vector<theta> thetat;
	//std::vector<theta> thetax;

	u1_field(std::string name = "u1_field") : 
	thetas(Kokkos::view_alloc(Kokkos::WithoutInitializing, name), N_DIM, N_DIM) {
		fill_view(thetas, 0.0);
	}
	//thetat(N_DIM*N_DIM,0.0), thetax(N_DIM*N_DIM,0.0) {}
	u1_field(double val, std::string name = "u1_field") : 
	thetas(Kokkos::view_alloc(Kokkos::WithoutInitializing, name), N_DIM, N_DIM) {
		fill_view(thetas, val);
	}
	//thetat(N_DIM*N_DIM,a_val), thetax(N_DIM*N_DIM,b_val) {}
	u1_field(int seed, std::string name = "u1_field") :
	thetas(Kokkos::view_alloc(Kokkos::WithoutInitializing, name), N_DIM, N_DIM) {
		fill_view_random(thetas, seed);
	}

	void randomize(int seed) {
		fill_view_random(thetas, seed);
	}


	KOKKOS_FORCEINLINE_FUNCTION
	theta & operator()(const int t, const int x, const int mu) const {
		return thetas(periodic(t),periodic(x),mu);
	}

	u1_field & operator=(u1_field & other) {
		Kokkos::deep_copy(thetas, other.thetas);
		Kokkos::fence();
		return *this;
	}

	KOKKOS_FUNCTION
	void print(int t, int x) {
		printf("(%f,%f);", thetas(t,x,0).val, thetas(t,x,1).val);
	}

	void print() {
		for (int i=0; i<N_DIM*N_DIM; ++i) {
			int x = i/N_DIM;
			int y = i%N_DIM;
			this -> print(x,y);
			//printf("(%f,%f);", thetas(x,y,0), thetas(x,y,1));
			if (i%(N_DIM) == N_DIM-1) std::cout << "\n";
		}
	}

	void print_file(std::string base_name, std::string metadata = "no metadata") {
		std::string pr_int = std::to_string(num_prints);
		if (num_prints < 10) pr_int = "0" + std::to_string(num_prints);

		// file name of the form "ensembles/NAME_#prints.csv"
		std::string name = "ensembles/" + base_name + "_" + pr_int + ".csv";

		// create folder, should it not exist yet
		if (!std::filesystem::exists("ensembles")) {
			std::filesystem::create_directory("ensembles");
		}

		int n=0;
		// modify filename to not overwrite already saved data
		while (std::filesystem::exists(name)) {
			name = "ensembles/" + base_name + "_" + pr_int + "_" +  std::to_string(n) + ".csv";
			++n;
		}

		std::fstream file(name, std::fstream::out | std::fstream::app);
		file << "# " << metadata << "\n";
		for (int i=0; i<N_DIM*N_DIM; ++i) {
			int x = i/N_DIM;
			int y = i%N_DIM;
			file << std::scientific << thetas(x,y,0).val << "," << thetas(x,y,1).val;
			if (i%(N_DIM) != (N_DIM-1)) {
				file << ",";
			} else {
				file << "\n";
			}
		}
		file.close();
		++num_prints;
	}

	void load_file(std::string name) {
		if (!std::filesystem::exists(name)) {
			std::cerr << "Error: file " << name << " does not exist!" << std::endl;
			exit;
		}

		std::ifstream file(name);

		if (!file.is_open()) {
			std::cerr << "Error: file " << name << " could not be opened!" << std::endl;
			exit;
		}

		std::string str;
		int n = 0;
		std::string metadata;
		std::getline(file, metadata);

		while (std::getline(file, str)) {
			std::stringstream ss(str);
			std::string elem;
			while (std::getline(ss, elem, ',') && n<2*N_DIM*N_DIM) {
				int x = (n/2)/N_DIM;
				int y = (n/2)%N_DIM;
				if (n%2 == 0) { thetas(x, y, 0) = std::stod(elem); }
				else { thetas(x, y, 1) = std::stod(elem); }
				++n;
			}
		}

		std::cout << "File read: " << name << "\nMetadata: " << metadata << "\nField loaded:" << std::endl;
		this -> print();
	}

	private:
	// tracking how many times weve printed to file
	static int num_prints;


}; // end of u1_field

int u1_field::num_prints = 0;


