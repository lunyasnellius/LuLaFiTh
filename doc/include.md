
# Core

the `core.hpp` of this project: 
- includes all the necessary standard library headers, 
- lists helpful enums,
- introduces necessary constants,
- defines the function `periodic`, implementing periodic boundary conditions, and
- defines the function `constrain`, used to enforce the peridicity of the phases characterizing the U(1) fields.

# Functions

the `functions.hpp` of this project:
- defines the function `real`, returning the real part of the gauge field, cos(theta), associated with the angle theta,
- defines the function `imag`, returning the imaginary part of the gauge field, sin(theta), associated with the angle theta, and
- defines the function `evaluate`, returning the gauge link associated with theta as a complex number (cos(),sin()).

# Rand

the `rand.hpp` of this project:
- defines the struct `random_var`, which is initialized with an integer-valued `seed` and has a member function `operator()()`, which returns a random number between -1 and 1 

# Include

include is the folder holding core, functions and rand.
The `include.hpp` file includes all source files and is the only header that needs to be included to use the full code base in a `.cpp` file. 



