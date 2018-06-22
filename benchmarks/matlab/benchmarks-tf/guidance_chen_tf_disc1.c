#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  6,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  6,
	.sample_time = 1.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0.00484 , -0.0023813 , -0.00012632 , 0.0047142 , -0.0016843 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  6,
	.a = {  1.2184 , -3.9926 , 5.9024 , -5.1692 , 2.5806 , -0.5403 },
	.a_size =  6 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 },
	};

