#include <dsverifier.h>

digital_system controller = { 
	.b = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  10,
	.a = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.a_size =  10,
	.sample_time = 5.000000e-02
};

implementation impl = { 
	.int_bits =  8,
	.frac_bits =   8,
	.max =  -1.000000,
	.min =  1.000000
	};

digital_system plant = { 
	.b = {  0 , 3.1662e-09 , 8.9015e-08 , 3.4558e-08 , -4.2024e-07 , 3.3179e-07 , 5.3337e-08 , -1.0692e-07 , 1.6629e-08 , 1.3003e-09 },
	.b_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	.b_size =  10,
	.a = {  1 , -8.4899 , 32.1018 , -70.9545 , 101.0301 , -96.1028 , 61.0711 , -25.0009 , 5.9827 , -0.63763 },
	.a_size =  10 
	.a_uncertainty = {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};

