#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  9,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  9,
	.sample_time = 1.000000e-03
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0.034966 , -0.24368 , 0.7278 , -1.2076 , 1.2023 , -0.71819 , 0.23834 , -0.033897 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  9,
	.a = {  1 , -7.9671 , 27.7702 , -55.3119 , 68.8553 , -54.8574 , 27.3157 , -7.7723 , 0.96754 },
	.a_size =  9 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

