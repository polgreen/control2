#include <dsverifier.h>

digital_system controller = {
        .b = {  0.0, 0.0 },
        .b_uncertainty = { 0.0, 0.0 },
        .b_size = 2,
        .a = { 0.0, 0.0 },
        .a_uncertainty = { 0.0, 0.0 },
        .a_size = 2,
        .sample_time = 0.02
};

implementation impl = {
        .int_bits = 8,
        .frac_bits = 8,
        .max = 1.0,
        .min = -1.0,
        .scale = 1
};

digital_system plant = {
        .b = { -0.06875, 0.0, 0.0 },
        .b_uncertainty = { 0.0, 0.0 , 0.0 },
        .b_size = 3,
        .a = { 1, -1.696, 0.7089 },
        .a_uncertainty = { 0.0, 0.0 , 0.0 },
        .a_size = 3,
};

