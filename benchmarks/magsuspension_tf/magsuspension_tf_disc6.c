#include <dsverifier.h>

digital_system controller = {
        .b = { 0.07421875f, 0.201171875f },
        .b_uncertainty = { 0.0, 0.0 },
        .b_size = 2,
        .a = { 0.1875f, 0.5f },
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
        .b = { 3.833f, 3.833f },
        .b_uncertainty = { 0.0, 0.0 },
        .b_size = 2,
        .a = { 1.0f, -5.066f, 1.0f },
        .a_uncertainty = { 0.0, 0.0, 0.0 },
        .a_size = 3,
};

