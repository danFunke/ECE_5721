/**
 * @file sin_tables.c
 * @author D. Funke
 * @brief Look up tables for sine waves of 4, 8, 12, and 16 Hz sampled at 250 Hz
 * @date 2022-11-26
 * 
 */

#include "sin_tables.h"
#include "waveform_generator.h"

#define NUM_SAMPLES (250)

static float sin_4Hz[NUM_SAMPLES] = {
    1.00000, 1.10036, 1.19971, 1.29704, 1.39137, 1.48175, 1.56727, 1.64706, 1.72031, 1.78629,
    1.84433, 1.89384, 1.93433, 1.96538, 1.98669, 1.99803, 1.99929, 1.99046, 1.97163, 1.94299,
    1.90483, 1.85753, 1.80157, 1.73751, 1.66601, 1.58779, 1.50362, 1.41438, 1.32094, 1.22427,
    1.12533, 1.02513, 0.92467, 0.82498, 0.72705, 0.63188, 0.54042, 0.45361, 0.37231, 0.29735,
    0.22949, 0.16940, 0.11771, 0.07492, 0.04148, 0.01771, 0.00387, 0.00008, 0.00639, 0.02273,
    0.04894, 0.08476, 0.12982, 0.18366, 0.24575, 0.31545, 0.39207, 0.47483, 0.56288, 0.65536,
    0.75131, 0.84977, 0.94976, 1.05024, 1.15023, 1.24869, 1.34464, 1.43712, 1.52517, 1.60793,
    1.68455, 1.75425, 1.81634, 1.87018, 1.91524, 1.95106, 1.97727, 1.99361, 1.99992, 1.99613,
    1.98229, 1.95852, 1.92508, 1.88229, 1.83060, 1.77051, 1.70265, 1.62769, 1.54639, 1.45958,
    1.36812, 1.27295, 1.17502, 1.07533, 0.97487, 0.87467, 0.77573, 0.67906, 0.58562, 0.49638,
    0.41221, 0.33399, 0.26249, 0.19843, 0.14247, 0.09517, 0.05701, 0.02837, 0.00954, 0.00071,
    0.00197, 0.01331, 0.03462, 0.06567, 0.10616, 0.15567, 0.21371, 0.27969, 0.35294, 0.43273,
    0.51825, 0.60863, 0.70296, 0.80029, 0.89964, 1.00000, 1.10036, 1.19971, 1.29704, 1.39137,
    1.48175, 1.56727, 1.64706, 1.72031, 1.78629, 1.84433, 1.89384, 1.93433, 1.96538, 1.98669,
    1.99803, 1.99929, 1.99046, 1.97163, 1.94299, 1.90483, 1.85753, 1.80157, 1.73751, 1.66601,
    1.58779, 1.50362, 1.41438, 1.32094, 1.22427, 1.12533, 1.02513, 0.92467, 0.82498, 0.72705,
    0.63188, 0.54042, 0.45361, 0.37231, 0.29735, 0.22949, 0.16940, 0.11771, 0.07492, 0.04148,
    0.01771, 0.00387, 0.00008, 0.00639, 0.02273, 0.04894, 0.08476, 0.12982, 0.18366, 0.24575,
    0.31545, 0.39207, 0.47483, 0.56288, 0.65536, 0.75131, 0.84977, 0.94976, 1.05024, 1.15023,
    1.24869, 1.34464, 1.43712, 1.52517, 1.60793, 1.68455, 1.75425, 1.81634, 1.87018, 1.91524,
    1.95106, 1.97727, 1.99361, 1.99992, 1.99613, 1.98229, 1.95852, 1.92508, 1.88229, 1.83060,
    1.77051, 1.70265, 1.62769, 1.54639, 1.45958, 1.36812, 1.27295, 1.17502, 1.07533, 0.97487,
    0.87467, 0.77573, 0.67906, 0.58562, 0.49638, 0.41221, 0.33399, 0.26249, 0.19843, 0.14247,
    0.09517, 0.05701, 0.02837, 0.00954, 0.00071, 0.00197, 0.01331, 0.03462, 0.06567, 0.10616,
    0.15567, 0.21371, 0.27969, 0.35294, 0.43273, 0.51825, 0.60863, 0.70296, 0.80029, 0.89964
};

static float sin_8Hz[NUM_SAMPLES] = {
    1.00000, 1.19971, 1.39137, 1.56727, 1.72031, 1.84433, 1.93433, 1.98669, 1.99929, 1.97163,
    1.90483, 1.80157, 1.66601, 1.50362, 1.32094, 1.12533, 0.92467, 0.72705, 0.54042, 0.37231,
    0.22949, 0.11771, 0.04148, 0.00387, 0.00639, 0.04894, 0.12982, 0.24575, 0.39207, 0.56288,
    0.75131, 0.94976, 1.15023, 1.34464, 1.52517, 1.68455, 1.81634, 1.91524, 1.97727, 1.99992,
    1.98229, 1.92508, 1.83060, 1.70265, 1.54639, 1.36812, 1.17502, 0.97487, 0.77573, 0.58562,
    0.41221, 0.26249, 0.14247, 0.05701, 0.00954, 0.00197, 0.03462, 0.10616, 0.21371, 0.35294,
    0.51825, 0.70296, 0.89964, 1.10036, 1.29704, 1.48175, 1.64706, 1.78629, 1.89384, 1.96538,
    1.99803, 1.99046, 1.94299, 1.85753, 1.73751, 1.58779, 1.41438, 1.22427, 1.02513, 0.82498,
    0.63188, 0.45361, 0.29735, 0.16940, 0.07492, 0.01771, 0.00008, 0.02273, 0.08476, 0.18366,
    0.31545, 0.47483, 0.65536, 0.84977, 1.05024, 1.24869, 1.43712, 1.60793, 1.75425, 1.87018,
    1.95106, 1.99361, 1.99613, 1.95852, 1.88229, 1.77051, 1.62769, 1.45958, 1.27295, 1.07533,
    0.87467, 0.67906, 0.49638, 0.33399, 0.19843, 0.09517, 0.02837, 0.00071, 0.01331, 0.06567,
    0.15567, 0.27969, 0.43273, 0.60863, 0.80029, 1.00000, 1.19971, 1.39137, 1.56727, 1.72031,
    1.84433, 1.93433, 1.98669, 1.99929, 1.97163, 1.90483, 1.80157, 1.66601, 1.50362, 1.32094,
    1.12533, 0.92467, 0.72705, 0.54042, 0.37231, 0.22949, 0.11771, 0.04148, 0.00387, 0.00639,
    0.04894, 0.12982, 0.24575, 0.39207, 0.56288, 0.75131, 0.94976, 1.15023, 1.34464, 1.52517,
    1.68455, 1.81634, 1.91524, 1.97727, 1.99992, 1.98229, 1.92508, 1.83060, 1.70265, 1.54639,
    1.36812, 1.17502, 0.97487, 0.77573, 0.58562, 0.41221, 0.26249, 0.14247, 0.05701, 0.00954,
    0.00197, 0.03462, 0.10616, 0.21371, 0.35294, 0.51825, 0.70296, 0.89964, 1.10036, 1.29704,
    1.48175, 1.64706, 1.78629, 1.89384, 1.96538, 1.99803, 1.99046, 1.94299, 1.85753, 1.73751,
    1.58779, 1.41438, 1.22427, 1.02513, 0.82498, 0.63188, 0.45361, 0.29735, 0.16940, 0.07492,
    0.01771, 0.00008, 0.02273, 0.08476, 0.18366, 0.31545, 0.47483, 0.65536, 0.84977, 1.05024,
    1.24869, 1.43712, 1.60793, 1.75425, 1.87018, 1.95106, 1.99361, 1.99613, 1.95852, 1.88229,
    1.77051, 1.62769, 1.45958, 1.27295, 1.07533, 0.87467, 0.67906, 0.49638, 0.33399, 0.19843,
    0.09517, 0.02837, 0.00071, 0.01331, 0.06567, 0.15567, 0.27969, 0.43273, 0.60863, 0.80029

};

static float sin_12Hz[NUM_SAMPLES] = {
    1.00000, 1.29704, 1.56727, 1.78629, 1.93433, 1.99803, 1.97163, 1.85753, 1.66601, 1.41438,
    1.12533, 0.82498, 0.54042, 0.29735, 0.11771, 0.01771, 0.00639, 0.08476, 0.24575, 0.47483,
    0.75131, 1.05024, 1.34464, 1.60793, 1.81634, 1.95106, 1.99992, 1.95852, 1.83060, 1.62769,
    1.36812, 1.07533, 0.77573, 0.49638, 0.26249, 0.09517, 0.00954, 0.01331, 0.10616, 0.27969,
    0.51825, 0.80029, 1.10036, 1.39137, 1.64706, 1.84433, 1.96538, 1.99929, 1.94299, 1.80157,
    1.58779, 1.32094, 1.02513, 0.72705, 0.45361, 0.22949, 0.07492, 0.00387, 0.02273, 0.12982,
    0.31545, 0.56288, 0.84977, 1.15023, 1.43712, 1.68455, 1.87018, 1.97727, 1.99613, 1.92508,
    1.77051, 1.54639, 1.27295, 0.97487, 0.67906, 0.41221, 0.19843, 0.05701, 0.00071, 0.03462,
    0.15567, 0.35294, 0.60863, 0.89964, 1.19971, 1.48175, 1.72031, 1.89384, 1.98669, 1.99046,
    1.90483, 1.73751, 1.50362, 1.22427, 0.92467, 0.63188, 0.37231, 0.16940, 0.04148, 0.00008,
    0.04894, 0.18366, 0.39207, 0.65536, 0.94976, 1.24869, 1.52517, 1.75425, 1.91524, 1.99361,
    1.98229, 1.88229, 1.70265, 1.45958, 1.17502, 0.87467, 0.58562, 0.33399, 0.14247, 0.02837,
    0.00197, 0.06567, 0.21371, 0.43273, 0.70296, 1.00000, 1.29704, 1.56727, 1.78629, 1.93433,
    1.99803, 1.97163, 1.85753, 1.66601, 1.41438, 1.12533, 0.82498, 0.54042, 0.29735, 0.11771,
    0.01771, 0.00639, 0.08476, 0.24575, 0.47483, 0.75131, 1.05024, 1.34464, 1.60793, 1.81634,
    1.95106, 1.99992, 1.95852, 1.83060, 1.62769, 1.36812, 1.07533, 0.77573, 0.49638, 0.26249,
    0.09517, 0.00954, 0.01331, 0.10616, 0.27969, 0.51825, 0.80029, 1.10036, 1.39137, 1.64706,
    1.84433, 1.96538, 1.99929, 1.94299, 1.80157, 1.58779, 1.32094, 1.02513, 0.72705, 0.45361,
    0.22949, 0.07492, 0.00387, 0.02273, 0.12982, 0.31545, 0.56288, 0.84977, 1.15023, 1.43712,
    1.68455, 1.87018, 1.97727, 1.99613, 1.92508, 1.77051, 1.54639, 1.27295, 0.97487, 0.67906,
    0.41221, 0.19843, 0.05701, 0.00071, 0.03462, 0.15567, 0.35294, 0.60863, 0.89964, 1.19971,
    1.48175, 1.72031, 1.89384, 1.98669, 1.99046, 1.90483, 1.73751, 1.50362, 1.22427, 0.92467,
    0.63188, 0.37231, 0.16940, 0.04148, 0.00008, 0.04894, 0.18366, 0.39207, 0.65536, 0.94976,
    1.24869, 1.52517, 1.75425, 1.91524, 1.99361, 1.98229, 1.88229, 1.70265, 1.45958, 1.17502,
    0.87467, 0.58562, 0.33399, 0.14247, 0.02837, 0.00197, 0.06567, 0.21371, 0.43273, 0.70296
};

static float sin_16Hz[NUM_SAMPLES] = {
    1.00000, 1.39137, 1.72031, 1.93433, 1.99929, 1.90483, 1.66601, 1.32094, 0.92467, 0.54042,
    0.22949, 0.04148, 0.00639, 0.12982, 0.39207, 0.75131, 1.15023, 1.52517, 1.81634, 1.97727,
    1.98229, 1.83060, 1.54639, 1.17502, 0.77573, 0.41221, 0.14247, 0.00954, 0.03462, 0.21371,
    0.51825, 0.89964, 1.29704, 1.64706, 1.89384, 1.99803, 1.94299, 1.73751, 1.41438, 1.02513,
    0.63188, 0.29735, 0.07492, 0.00008, 0.08476, 0.31545, 0.65536, 1.05024, 1.43712, 1.75425,
    1.95106, 1.99613, 1.88229, 1.62769, 1.27295, 0.87467, 0.49638, 0.19843, 0.02837, 0.01331,
    0.15567, 0.43273, 0.80029, 1.19971, 1.56727, 1.84433, 1.98669, 1.97163, 1.80157, 1.50362,
    1.12533, 0.72705, 0.37231, 0.11771, 0.00387, 0.04894, 0.24575, 0.56288, 0.94976, 1.34464,
    1.68455, 1.91524, 1.99992, 1.92508, 1.70265, 1.36812, 0.97487, 0.58562, 0.26249, 0.05701,
    0.00197, 0.10616, 0.35294, 0.70296, 1.10036, 1.48175, 1.78629, 1.96538, 1.99046, 1.85753,
    1.58779, 1.22427, 0.82498, 0.45361, 0.16940, 0.01771, 0.02273, 0.18366, 0.47483, 0.84977,
    1.24869, 1.60793, 1.87018, 1.99361, 1.95852, 1.77051, 1.45958, 1.07533, 0.67906, 0.33399,
    0.09517, 0.00071, 0.06567, 0.27969, 0.60863, 1.00000, 1.39137, 1.72031, 1.93433, 1.99929,
    1.90483, 1.66601, 1.32094, 0.92467, 0.54042, 0.22949, 0.04148, 0.00639, 0.12982, 0.39207,
    0.75131, 1.15023, 1.52517, 1.81634, 1.97727, 1.98229, 1.83060, 1.54639, 1.17502, 0.77573,
    0.41221, 0.14247, 0.00954, 0.03462, 0.21371, 0.51825, 0.89964, 1.29704, 1.64706, 1.89384,
    1.99803, 1.94299, 1.73751, 1.41438, 1.02513, 0.63188, 0.29735, 0.07492, 0.00008, 0.08476,
    0.31545, 0.65536, 1.05024, 1.43712, 1.75425, 1.95106, 1.99613, 1.88229, 1.62769, 1.27295,
    0.87467, 0.49638, 0.19843, 0.02837, 0.01331, 0.15567, 0.43273, 0.80029, 1.19971, 1.56727,
    1.84433, 1.98669, 1.97163, 1.80157, 1.50362, 1.12533, 0.72705, 0.37231, 0.11771, 0.00387,
    0.04894, 0.24575, 0.56288, 0.94976, 1.34464, 1.68455, 1.91524, 1.99992, 1.92508, 1.70265,
    1.36812, 0.97487, 0.58562, 0.26249, 0.05701, 0.00197, 0.10616, 0.35294, 0.70296, 1.10036,
    1.48175, 1.78629, 1.96538, 1.99046, 1.85753, 1.58779, 1.22427, 0.82498, 0.45361, 0.16940,
    0.01771, 0.02273, 0.18366, 0.47483, 0.84977, 1.24869, 1.60793, 1.87018, 1.99361, 1.95852,
    1.77051, 1.45958, 1.07533, 0.67906, 0.33399, 0.09517, 0.00071, 0.06567, 0.27969, 0.60863
};

float sin_tables_get_value(int frequency, int index)
{
    float ret = 0;

    switch (frequency) {
        case DELTA_WAVE:
            ret = sin_4Hz[index];
            break;

        case THETA_WAVE:
            ret = sin_8Hz[index];
            break;

        case ALPHA_WAVE:
            ret = sin_12Hz[index];
            break;
        
        case BETA_WAVE:
            ret = sin_16Hz[index];
            break;
    }

    return ret;
}