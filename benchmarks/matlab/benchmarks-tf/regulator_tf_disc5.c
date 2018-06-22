#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  6,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  6,
	.sample_time = 5.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 1.9852 , 6.116 , 0.9231 , 0.004032 , 2.2146e-07 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  6,
	.a = {  1 , -1.6912 , 0.71738 , -0.0053185 , 3.7839e-06 , -1.4028e-11 },
	.a_size =  6 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 },
	};

