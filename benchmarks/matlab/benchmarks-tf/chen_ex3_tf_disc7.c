#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  8,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  8,
	.sample_time = 1.000000e-03
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 5.0292e-07 , -1.9925e-06 , 2.4513e-06 , 6.1205e-08 , -2.5109e-06 , 1.9776e-06 , -4.8968e-07 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  8,
	.a = {  1 , -6.985 , 20.9101 , -34.7754 , 34.701 , -20.7761 , 6.9105 , -0.98511 },
	.a_size =  8 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

