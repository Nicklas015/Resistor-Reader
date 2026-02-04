#pragma once
#include <opencv2/core.hpp>

enum Color { BLUE, RED, GREEN, YELLOW, PURPLE, ORANGE, BLACK, GOLD };

inline const char* ColorToString(Color c) {
    switch (c) {
        case RED:    return "RED";
        case BLUE:   return "BLUE";
        case GREEN:  return "GREEN";
        case YELLOW: return "YELLOW";
        case PURPLE: return "PURPLE";
        case ORANGE: return "ORANGE";
        case BLACK: return "BLACK";
        case GOLD: return "GOLD";
        default:     return "UNKNOWN";
    }
}

struct ColorRange {
    cv::Scalar low;
    cv::Scalar high;
};

extern const ColorRange BLUE_RANGE;
extern const ColorRange RED_RANGE;
extern const ColorRange GREEN_RANGE;
extern const ColorRange YELLOW_RANGE;
extern const ColorRange PURPLE_RANGE;
extern const ColorRange ORANGE_RANGE;
extern const ColorRange BLACK_RANGE;
extern const ColorRange GOLD_RANGE;