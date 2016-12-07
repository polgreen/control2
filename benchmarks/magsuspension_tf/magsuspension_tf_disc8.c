#include <dsverifier.h>

digital_system controller = {
        .b = { 0.361328125f, 0.8056640625f },
        .b_uncertainty = { 0.0, 0.0 },
        .b_size = 2,
        .a = { 0.74609375f, 0.5f },
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
        .b = { 0.03132f, 0.03132f },
        .b_uncertainty = { 0.0, 0.0 },
        .b_size = 2,
        .a = { 1.0f, -2.025f, 1.0f },
        .a_uncertainty = { 0.0, 0.0, 0.0 },
        .a_size = 3,
};

