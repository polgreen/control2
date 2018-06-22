#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  8,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  8,
	.sample_time = 5.000000e-03
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 1.2864e-05 , -4.9033e-05 , 5.6466e-05 , 7.4229e-06 , -6.3691e-05 , 4.7229e-05 , -1.1258e-05 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  8,
	.a = {  1 , -6.9247 , 20.5514 , -33.8862 , 33.5251 , -19.9013 , 6.5635 , -0.92774 },
	.a_size =  8 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

