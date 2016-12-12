#include <dsverifier.h>

digital_system controller = {
        .b = { 0.001953125f, 0.5f },
        .b_uncertainty = { 0.0, 0.0 },
        .b_size = 2,
        .a = { 0.9970703125f, 0.1220703125f },
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
        .b = { 0.00125f, 0.00125f },
        .b_uncertainty = { 0.0, 0.0 },
        .b_size = 2,
        .a = { 1.0f, -2.001f, 1.0f },
        .a_uncertainty = { 0.0, 0.0, 0.0 },
        .a_size = 3,
};

