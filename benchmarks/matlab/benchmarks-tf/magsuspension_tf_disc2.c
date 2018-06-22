#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 },
	.b_size =  3,
	.a = {  0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 },
	.a_size =  3,
	.sample_time = 1.000000e-03
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0.0012501 , 0.0012501 },
	.b_uncertainty = {  0 , 0 , 0 },
	.b_size =  3,
	.a = {  1 , -2.001 , 1 },
	.a_size =  3 
	.a_uncertainty = {  0 , 0 , 0 },
	};

