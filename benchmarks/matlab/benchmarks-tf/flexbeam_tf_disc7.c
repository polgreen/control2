#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  7,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  7,
	.sample_time = 1.000000e-03
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 8.2466e-07 , -2.4742e-06 , 1.6507e-06 , 1.6471e-06 , -2.4727e-06 , 8.245e-07 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  7,
	.a = {  1 , -5.9985 , 14.9932 , -19.9873 , 14.9882 , -5.9946 , 0.999 },
	.a_size =  7 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

