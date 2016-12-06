#include <dsverifier.h>

digital_system controller = {
        .b = { 0.2f, -0.18f },
        .b_uncertainty = { 0.0, 0.0 },
        .b_size = 2,
        .a = { 1.0f, 0.3f },
        .a_uncertainty = { 0.0, 0.0 },
        .a_size = 2,
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
        .b = { 6.7203E43 },
        .b_uncertainty = { 0.0 },
        .b_size = 1,
        .a = { 1.0f, -2.6881E43 },
        .a_uncertainty = { 0.0, 0.0 },
        .a_size = 2,
};

