#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  9,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  9,
	.sample_time = 1.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 3.2317 , -15.1251 , 29.8654 , -32.205 , 20.4809 , -7.713 , 1.6169 , -0.15128 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  9,
	.a = {  1 , -5.5403 , 13.2843 , -17.9879 , 15.0293 , -7.9259 , 2.5735 , -0.46984 , 0.036883 },
	.a_size =  9 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

