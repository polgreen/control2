#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  10,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  10,
	.sample_time = 1.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 1.1906e-07 , 3.8473e-06 , 5.6387e-06 , -1.5838e-05 , 3.9517e-06 , 6.1221e-06 , -2.752e-06 , -4.6713e-08 , 1.9212e-08 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  10,
	.a = {  1 , -7.8747 , 27.7938 , -57.706 , 77.6691 , -70.2779 , 42.7497 , -16.8578 , 3.9105 , -0.40657 },
	.a_size =  10 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

