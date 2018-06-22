#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  7,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  7,
	.sample_time = 5.000000e-01
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 1.5266e-05 , 8.7632e-06 , -1.0769e-05 , 1.9653e-07 , -1.9287e-07 , -2.954e-09 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  7,
	.a = {  1 , -2.0821 , 1.1843 , -0.12316 , 0.021972 , -0.00098061 , 2.9023e-06 },
	.a_size =  7 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

