#pragma once
#include "Data Types/Vectors.h"
#include "Object Groups/Motors/ArmSegment.h"
#include <array>
#include <cstddef>

template <size_t Joints>
Vector<double, Joints> InverseKinematics(std::array<ArmSegment, Joints>& segments, Matrix<double, 3, 3>& baseOrientation);