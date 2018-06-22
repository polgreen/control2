#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  7,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  7,
	.sample_time = 2.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 9.891e-07 , 6.7317e-06 , 2.4869e-07 , -3.7584e-06 , -1.1904e-06 , -3.1071e-08 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  7,
	.a = {  1 , -1.5036 , -0.12107 , 0.6991 , -0.014361 , -0.066134 , 0.0060967 },
	.a_size =  7 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

