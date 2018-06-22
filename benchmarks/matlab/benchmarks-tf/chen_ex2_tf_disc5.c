#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  9,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  9,
	.sample_time = 1.000000e-02
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0.34668 , -2.3222 , 6.6656 , -10.6285 , 10.1675 , -5.8355 , 1.8605 , -0.25421 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  9,
	.a = {  1 , -7.6805 , 25.8044 , -49.5338 , 59.4195 , -45.6115 , 21.8796 , -5.9966 , 0.71892 },
	.a_size =  9 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

