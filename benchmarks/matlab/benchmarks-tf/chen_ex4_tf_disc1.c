#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  10,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  10,
	.sample_time = 5.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 0.00073999 , 0.026239 , 0.096845 , 0.072163 , 0.0066828 , 0.0011268 , 0.0004635 , -0.00010888 , -2.6219e-06 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  10,
	.a = {  1 , -1.9074 , 2.2005 , -1.8996 , 1.3834 , -0.8586 , 0.42015 , -0.18079 , 0.057598 , -0.011109 },
	.a_size =  10 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

