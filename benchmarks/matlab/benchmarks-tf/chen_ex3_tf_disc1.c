#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  8,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  8,
	.sample_time = 5.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0.36493 , 0.53172 , -0.35409 , -0.18606 , -0.022438 , -0.002679 , 2.6531e-05 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  8,
	.a = {  1 , -0.72945 , 0.27618 , -0.1439 , 0.039231 , -0.017037 , 0.0016359 , -0.00055308 },
	.a_size =  8 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

