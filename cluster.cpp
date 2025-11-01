//cluster.cpp
#include "cluster.h"
#include <algorithm>
#include <cmath>
#include <iostream>

bool isHorizontal(const std::vector<line>& lines) {
    int minX = 999999, maxX = -1;
    int minY = 999999, maxY = -1;

    for (auto &l : lines) {
        minX = std::min(minX, l.position.x);
        maxX = std::max(maxX, l.position.x);
        minY = std::min(minY, l.position.y);
        maxY = std::max(maxY, l.position.y);
    }

    int spreadX = maxX - minX;
    int spreadY = maxY - minY;

    return spreadX > spreadY;   // TRUE = horizontal resistor
}

std::vector<line> clusterByX(std::vector<line> lines, int threshold) {
    if (lines.empty()) return {};

    std::sort(lines.begin(), lines.end(),
              [](const line& a, const line& b) {
                  return a.position.x < b.position.x;
              });

    std::vector<line> groups;
    line current = lines[0];

    for (size_t i = 1; i < lines.size(); i++) {
        int diff = std::abs(lines[i].position.x - current.position.x);

        if (diff < threshold) {
            if (lines[i].rect.area() > current.rect.area())
                current = lines[i];
        } else {
            groups.push_back(current);
            current = lines[i];
        }
    }

    groups.push_back(current);
    return groups;
}

std::vector<line> clusterByY(std::vector<line> lines, int threshold) {
    if (lines.empty()) return {};

    std::sort(lines.begin(), lines.end(),
              [](const line& a, const line& b) {
                  return a.position.y < b.position.y;
              });

    std::vector<line> groups;
    line current = lines[0];

    for (size_t i = 1; i < lines.size(); i++) {
        int diff = std::abs(lines[i].position.y - current.position.y);

        if (diff < threshold) {
            if (lines[i].rect.area() > current.rect.area())
                current = lines[i];
        } else {
            groups.push_back(current);
            current = lines[i];
        }
    }

    groups.push_back(current);
    return groups;
}