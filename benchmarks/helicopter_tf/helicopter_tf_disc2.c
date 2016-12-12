#include <dsverifier.h>

digital_system controller = {
        .b = { 0.0078125f, 0.001953125f },
        .b_uncertainty = { 0.0, 0.0 },
        .b_size = 2,
        .a = { 0.84375f },
        .a_uncertainty = { 0.0 },
        .a_size = 1,
        .sample_time = 2,
};

implementation impl = {
        .int_bits = 3,
        .frac_bits = 7,
        .max = 1.0,
        .min = -1.0,
        .scale = 1,
};

digital_system plant = {
        .b = { 0.009796f, -0.0196f, 0.0098f },
        .b_uncertainty = { 0.0, 0.0, 0.0 },
        .b_size = 3,
        .a = { 1.0f, -3.0f, 2.999f, -0.9996f },
        .a_uncertainty = { 0.0, 0.0, 0.0, 0.0 },
        .a_size = 4,
};

