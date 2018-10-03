#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 },
	.b_size =  4,
	.a = {  0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 },
	.a_size =  4,
	.sample_time = 5.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0 , 0 , -0.52272 },
	.b_uncertainty = {  0 , 0 , 0 , 0 },
	.b_size =  4,
	.a = {  1 , -1.0886 , 0 , 0 },
	.a_size =  4 
	.a_uncertainty = {  0 , 0 , 0 , 0 },
	};
