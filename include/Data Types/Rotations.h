#pragma once
#include "Data Types/Matrix.h"
#include <initializer_list>
#include "Vectors.h"

class Rotation : public Matrix<double, 3, 3> {
public:
    enum class Axis {
        XAxis,
        YAxis,
        ZAxis
    };

    const Vector3D<double>& axis() const { return axisVector; }

    Rotation(std::initializer_list<double> lst, Vector3D<double> axis) : Matrix<double, 3, 3>(lst), axisVector(axis) {
    }

    // FACTORIES
    static Rotation ZAxis(double rotation) {
        double c = cos(rotation);
        double s = sin(rotation);
        return Rotation({
            c, -s, 0,
            s,  c, 0,
            0,  0, 1
            },
            Vector3D<double>(0, 0, 1)
        );
    }

    static Rotation YAxis(double rotation) {
        double c = cos(rotation);
        double s = sin(rotation);
        return Rotation({
            c, 0, s,
            0, 1, 0,
            -s, 0, c
            },
            Vector3D<double>(0, 1, 0)
        );
    }

    static Rotation XAxis(double rotation) {
        double c = cos(rotation);
        double s = sin(rotation);
        return Rotation({
            1, 0, 0,
            0, c, -s,
            0, s, c
        },
            Vector3D<double>(1, 0, 0)
        );
    }

    static Rotation about(Rotation::Axis axis, double rotation) {
        switch (axis) {
            case Rotation::Axis::XAxis:
                return Rotation::XAxis(rotation);
            case Rotation::Axis::YAxis:
                return Rotation::YAxis(rotation);
            case Rotation::Axis::ZAxis:
                return Rotation::ZAxis(rotation);
    }
    }
private:
    Vector3D<double> axisVector;
};