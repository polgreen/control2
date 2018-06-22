#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  10,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  10,
	.sample_time = 2.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 4.9039e-06 , 0.00018161 , 0.00049682 , -0.00033616 , -0.000197 , 0.00021266 , -2.871e-05 , -9.2163e-06 , 6.3946e-08 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  10,
	.a = {  1 , -6.424 , 18.9912 , -33.8953 , 40.2382 , -32.9443 , 18.6021 , -6.9865 , 1.5841 , -0.1653 },
	.a_size =  10 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

