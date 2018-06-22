#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 },
	.b_uncertainty = {  0 , 0 },
	.b_size =  2,
	.a = {  0 , 0 },
	.a_uncertainty = {  0 , 0 },
	.a_size =  2,
	.sample_time = 1
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0.00097541 },
	.b_uncertainty = {  0 , 0 },
	.b_size =  2,
	.a = {  1 , -0.95123 },
	.a_size =  2 
	.a_uncertainty = {  0 , 0 },
	};

