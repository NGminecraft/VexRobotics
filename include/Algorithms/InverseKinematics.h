#pragma once
#include "DataTypes/Vectors.h"
#include "ObjectGroups/Motors/Precision/PreciseSegment.h"
#include <array>
#include <cstddef>

template <size_t Joints>
Vector<double, Joints> InverseKinematics(std::array<PreciseSegment*, Joints>& segments, Matrix<double, 3, 3>& baseOrientation);