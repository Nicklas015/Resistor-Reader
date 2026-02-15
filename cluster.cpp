// cluster.cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include "cluster.h"

bool is_horizontal(const std::vector<line>& lines) {
  int minX = 999999, maxX = -1;
  int minY = 999999, maxY = -1;

  for (auto& l : lines) {
    minX = std::min(minX, l.position.x);
    maxX = std::max(maxX, l.position.x);
    minY = std::min(minY, l.position.y);
    maxY = std::max(maxY, l.position.y);
  }

  int spreadX = maxX - minX;
  int spreadY = maxY - minY;

  return spreadX > spreadY;  // TRUE = horizontal resistor
}

bool orientation(const std::vector<line>& lines, bool is_horizontal) {
  std::vector<line> sorted = lines;

  if (is_horizontal) {
    std::sort(sorted.begin(), sorted.end(), [](const line& a, const line& b) {
      return a.position.x < b.position.x;
    });
  } else {
    std::sort(sorted.begin(), sorted.end(), [](const line& a, const line& b) {
      return a.position.y < b.position.y;
    });
  }

  int startGap, endGap;

  if (is_horizontal) {
    startGap = std::abs(sorted[1].position.x - sorted[0].position.x);
    endGap = std::abs(sorted.back().position.x -
                      sorted[sorted.size() - 2].position.x);
  } else {
    startGap = std::abs(sorted[1].position.y - sorted[0].position.y);
    endGap = std::abs(sorted.back().position.y -
                      sorted[sorted.size() - 2].position.y);
  }

  if (endGap > startGap) return false;

  return true;
}

// Removes Cluster detections of the same color band X positions
std::vector<line> cluster_by_x(std::vector<line> lines, int threshold) {
  if (lines.empty()) return {};

  std::sort(lines.begin(), lines.end(), [](const line& a, const line& b) {
    return a.position.x < b.position.x;
  });

  std::vector<line> groups;
  line current = lines[0];

  for (size_t i = 1; i < lines.size(); i++) {
    int diff = std::abs(lines[i].position.x - current.position.x);

    if (diff < threshold) {
      if (lines[i].rect.area() > current.rect.area()) current = lines[i];
    } else {
      groups.push_back(current);
      current = lines[i];
    }
  }

  groups.push_back(current);
  return groups;
}

// Removes Cluster detections of the same color band X positions
std::vector<line> cluster_by_y(std::vector<line> lines, int threshold) {
  if (lines.empty()) return {};

  std::sort(lines.begin(), lines.end(), [](const line& a, const line& b) {
    return a.position.y < b.position.y;
  });

  std::vector<line> groups;
  line current = lines[0];

  for (size_t i = 1; i < lines.size(); i++) {
    int diff = std::abs(lines[i].position.y - current.position.y);

    if (diff < threshold) {
      if (lines[i].rect.area() > current.rect.area()) current = lines[i];
    } else {
      groups.push_back(current);
      current = lines[i];
    }
  }

  groups.push_back(current);
  return groups;
}