#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	.b_size =  5,
	.a = {  0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	.a_size =  5,
	.sample_time = 2.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0.0018609 , 0.0015597 , -0.0024632 , -0.002162 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	.b_size =  5,
	.a = {  1 , -4.0401 , 6.0803 , -4.0401 , 1 },
	.a_size =  5 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	};

