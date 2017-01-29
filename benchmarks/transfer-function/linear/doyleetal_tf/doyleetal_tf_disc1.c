#include <dsverifier.h>

digital_system controller = {
        .b = { 0.01f, 0.01f, 0.01f, 0.01f },
        .b_uncertainty = { 0.0, 0.0, 0.0, 0.0 },
        .b_size = 4,
        .a = { 0.01f, 0.01f, 0.01f , 0.01f },
        .a_uncertainty = { 0.0, 0.0, 0.0, 0.0 },
        .a_size = 4,
        .sample_time = 0.01,
};

implementation impl = {
        .int_bits = 4,
        .frac_bits = 11,
        .max = 1.0,
        .min = -1.0,
        .scale = 1,
};

digital_system plant = {
        .b = {-0.01285f, 0.02582f, -0.01293f },
        .b_uncertainty = { 0.0, 0.0, 0.0 },
        .b_size = 3,
        .a = { 1.0f, - 2.99f, 2.983f, -0.9929f},
        .a_uncertainty = { 0.0, 0.0, 0.0, 0.0},
        .a_size = 4,
};

