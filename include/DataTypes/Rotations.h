#pragma once
#include "DataTypes/Matrix.h"
#include <cmath>
#include <initializer_list>
#include "Vectors.h"

class Rotation : public Matrix<double, 3, 3> {
public:
    enum class Axis {
        XAxis,
        YAxis,
        ZAxis
    };

    // Access the rotation axis (for single-axis rotations)
    const Vector3D<double>& axis() const { return axisVector; }

    // Constructor with explicit axis
    Rotation(std::initializer_list<double> lst, const Vector3D<double>& axis) 
        : Matrix<double, 3, 3>(lst), axisVector(axis) {}
    
    // Constructor for arbitrary rotation (axis computed separately if needed)
    explicit Rotation(std::initializer_list<double> lst) 
        : Matrix<double, 3, 3>(lst), axisVector(0, 0, 0) {}
    
    // Identity rotation
    Rotation() 
        : Matrix<double, 3, 3>({1, 0, 0, 0, 1, 0, 0, 0, 1}), axisVector(0, 0, 0) {}

    // Check if this rotation has a defined axis
    bool hasDefinedAxis() const { 
        return axisVector.magnitude() > 0.0; 
    }

    // FACTORIES
    static Rotation XAxis(double rotation) {
        double c = std::cos(rotation);
        double s = std::sin(rotation);
        return Rotation({
            1, 0, 0,
            0, c, -s,
            0, s, c
        }, Vector3D<double>(1, 0, 0));
    }

    static Rotation YAxis(double rotation) {
        double c = std::cos(rotation);
        double s = std::sin(rotation);
        return Rotation({
            c, 0, s,
            0, 1, 0,
            -s, 0, c
        }, Vector3D<double>(0, 1, 0));
    }

    static Rotation ZAxis(double rotation) {
        double c = std::cos(rotation);
        double s = std::sin(rotation);
        return Rotation({
            c, -s, 0,
            s,  c, 0,
            0,  0, 1
        }, Vector3D<double>(0, 0, 1));
    }

    static Rotation about(Axis axis, double rotation) {
        switch (axis) {
            case Axis::XAxis: return XAxis(rotation);
            case Axis::YAxis: return YAxis(rotation);
            case Axis::ZAxis: return ZAxis(rotation);
        }
        return Rotation(); // Default to identity
    }

    // Arbitrary axis rotation using Rodrigues' formula
    static Rotation aboutAxis(const Vector3D<double>& axis, double angle) {
        Vector3D<double> k = axis.normalize();
        double c = std::cos(angle);
        double s = std::sin(angle);
        double t = 1.0 - c;
        
        return Rotation({
            t*k[0]*k[0] + c,       t*k[0]*k[1] - s*k[2], t*k[0]*k[2] + s*k[1],
            t*k[0]*k[1] + s*k[2], t*k[1]*k[1] + c,       t*k[1]*k[2] - s*k[0],
            t*k[0]*k[2] - s*k[1], t*k[1]*k[2] + s*k[0], t*k[2]*k[2] + c
        }, k);
    }

    // Override matrix multiplication to handle axis vectors
    // Note: Composed rotations lose the single-axis property
    Rotation operator*(const Rotation& other) const {
        // Multiply as matrices
        Matrix<double, 3, 3> resultMatrix = static_cast<const Matrix<double, 3, 3>&>(*this) 
                                           * static_cast<const Matrix<double, 3, 3>&>(other);
        
        // For composed rotations, axis is no longer well-defined
        // So we set it to zero vector
        return Rotation({
            resultMatrix(0,0), resultMatrix(0,1), resultMatrix(0,2),
            resultMatrix(1,0), resultMatrix(1,1), resultMatrix(1,2),
            resultMatrix(2,0), resultMatrix(2,1), resultMatrix(2,2)
        }, Vector3D<double>(0, 0, 0));
    }

private:
    Vector3D<double> axisVector; // Only valid for single-axis rotations
};