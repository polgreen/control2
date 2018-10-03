#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 },
	.b_size =  3,
	.a = {  0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 },
	.a_size =  3,
	.sample_time = 0
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  -0.001151 , -0.0036198 , -0.00042016 },
	.b_uncertainty = {  0 , 0 , 0 },
	.b_size =  3,
	.a = {  0 , 0 , 0.05 },
	.a_size =  3 
	.a_uncertainty = {  0 , 0 , 0 },
	};
