#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  10,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  10,
	.sample_time = 1.000000e-02
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 8.6942e-13 , 2.0361e-11 , -1.989e-11 , -8.7281e-11 , 1.5038e-10 , -4.9905e-11 , -3.017e-11 , 1.4908e-11 , 7.2859e-13 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  10,
	.a = {  1 , -8.9075 , 35.2666 , -81.4563 , 120.9586 , -119.7551 , 79.0489 , -33.5466 , 8.3053 , -0.91393 },
	.a_size =  10 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

