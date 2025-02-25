#include "Z:/dev/ai/CompanionX/include/engine/math.h"
#include <cmath>
#include <iostream>

Vec3 Mat4::transform(const Vec3 &v) const {
    float w = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15];
    if (w == 0) w = 1.0f;  // Avoid division by zero
    Vec3 result(
        (m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12]) / w,
        (m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13]) / w,
        (m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14]) / w
    );
    std::cout << "Transforming vertex (" << v.x << "," << v.y << "," << v.z << ") to (" 
              << result.x << "," << result.y << "," << result.z << ") with w=" << w << "\n";
    return result;
}

Mat4 rotateY(float angle) {
    Mat4 mat;
    float c = cos(angle);
    float s = sin(angle);
    mat[0] = c;   mat[2] = -s;  // First column
    mat[8] = s;   mat[10] = c;  // Third column
    std::cout << "Rotation Y matrix created with angle " << angle << " (cos=" << c << ", sin=" << s << ")\n";
    return mat;
}

Mat4 perspective(float fov, float aspect, float near, float far) {
    Mat4 mat;
    float tanHalfFov = tan(fov / 2.0f);
    mat[0] = 1.0f / (aspect * tanHalfFov);
    mat[5] = 1.0f / tanHalfFov;
    mat[10] = -(far + near) / (far - near);
    mat[11] = -1.0f;
    mat[14] = -(2.0f * far * near) / (far - near);
    mat[15] = 0.0f;
    std::cout << "Perspective matrix created with fov=" << fov << ", aspect=" << aspect << ", near=" << near << ", far=" << far << "\n";
    return mat;
}