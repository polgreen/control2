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
	.b = {  0 , -0.82452 , 2.4814 , -2.3235 , 0.6896 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	.b_size =  5,
	.a = {  1 , -5.8673 , 10.0745 , -5.8673 , 1 },
	.a_size =  5 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	};

