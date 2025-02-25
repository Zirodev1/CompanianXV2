#ifndef MATH_H
#define MATH_H

struct Vec3 {
  float x, y, z;

  Vec3(float x_ = 0.f, float y_ = 0.f, float z_ = 0.f) : x(x_), y(y_), z(z_) {}
  Vec3 operator+(const Vec3 v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
  Vec3 operator-(const Vec3 v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
  Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
};


struct Mat4{
  float m[16];
  Mat4() { for (int i = 0; i < 16; i++)
      m[i] = (i % 5 == 0) ? 1.f : 0.f;
  }
  float &operator[](int i) { return m[i]; }
  Vec3 transform(const Vec3 &v) const;
};

Mat4 rotateY(float angle);
Mat4 perspective(float fov, float aspect, float near, float far);

#endif