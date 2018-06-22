#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 },
	.b_size =  3,
	.a = {  0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 },
	.a_size =  3,
	.sample_time = 1
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0.14959 , -0.14344 },
	.b_uncertainty = {  0 , 0 , 0 },
	.b_size =  3,
	.a = {  1 , -1.9558 , 0.95253 },
	.a_size =  3 
	.a_uncertainty = {  0 , 0 , 0 },
	};

