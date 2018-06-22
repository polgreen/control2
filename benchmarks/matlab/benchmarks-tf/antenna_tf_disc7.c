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
	.b = {  0 , 8.2993e-18 , 2.0661e-16 , 3.2861e-16 , -3.296e-16 , -2.0478e-16 , -8.1567e-18 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  7,
	.a = {  1 , -5.9744 , 14.8723 , -19.7455 , 14.7464 , -5.8737 , 0.97482 },
	.a_size =  7 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

