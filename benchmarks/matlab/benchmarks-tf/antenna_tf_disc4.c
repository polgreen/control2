#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  7,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  7,
	.sample_time = 5.000000e-02
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 2.0993e-09 , 4.1461e-08 , 4.7741e-08 , -5.5837e-08 , -2.656e-08 , -8.8252e-10 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  7,
	.a = {  1 , -4.4738 , 8.5603 , -9.0608 , 5.6154 , -1.9205 , 0.27943 },
	.a_size =  7 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

