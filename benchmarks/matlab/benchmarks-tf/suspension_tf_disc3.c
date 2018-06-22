#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	.b_size =  5,
	.a = {  0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	.a_size =  5,
	.sample_time = 5.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0.25014 , 0.49996 , 0.24948 , -0.00032935 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	.b_size =  5,
	.a = {  1 , -0.00074795 , 3.2372e-06 , -7.0249e-32 , 8.3767e-113 },
	.a_size =  5 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	};

