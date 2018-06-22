#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  8,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  8,
	.sample_time = 2.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0.041448 , 0.017986 , -0.10276 , 0.069699 , -0.021725 , 0.001424 , 9.301e-05 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  8,
	.a = {  1 , -3.8935 , 6.8354 , -7.022 , 4.5574 , -1.8705 , 0.45087 , -0.049787 },
	.a_size =  8 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

