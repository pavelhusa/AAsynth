/*
 * We're using some fixed point math, so here it is.
 * 
 * Based on: https://spin.atomicobject.com/2012/03/15/simple-fixed-point-math/
 */

/**
 * Returns int (0..255 => 0..1) 
 */
inline uint16_t fixed_mul_8(uint16_t x, uint16_t y) {
    return ((uint32_t)x * (uint32_t)y) / (1 << 8);
}

/**
 * Returns int (0..127 => 0..1) 
 */
inline uint16_t fixed_mul_4(uint16_t x, uint16_t y) {
    return ((uint32_t)x * (uint32_t)y) / (1 << 7);
}
