#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	.b_size =  5,
	.a = {  0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	.a_size =  5,
	.sample_time = 1.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0.35943 , 0.62346 , 0.16865 , -0.095391 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	.b_size =  5,
	.a = {  1 , -0.02366 , 0.079806 , -5.8793e-07 , 3.8425e-23 },
	.a_size =  5 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 },
	};

