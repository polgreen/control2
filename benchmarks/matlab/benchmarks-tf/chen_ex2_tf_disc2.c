#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  9,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  9,
	.sample_time = 2.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 6.0112 , -20.5377 , 28.744 , -21.0113 , 8.4062 , -1.7488 , 0.17935 , -0.017023 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  9,
	.a = {  1 , -4.1268 , 7.2139 , -6.9337 , 3.9803 , -1.3867 , 0.28386 , -0.030912 , 0.0013604 },
	.a_size =  9 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

