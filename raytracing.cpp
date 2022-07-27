// It is better to keep aspect ratios of image and viewport the same
// and yes you can just calculate it here in code
#define IMAGE_WIDTH 512
#define IMAGE_HEIGHT 512

#define VIEWPORT_WIDTH 1.0
#define VIEWPORT_HEIGHT 1.0

// Camera coordinates in viewport space
#define CAM_X 0.5
#define CAM_Y 0.5
#define CAM_Z -1.0

#include <cmath>
#include <fstream>
#include <iostream>

class Vec3 {
public:
  float x, y, z;
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
  float length() const { return sqrt(x * x + y * y + z * z); }
  Vec3 normalized() const {
    float l = length();
    return {x / l, y / l, z / l};
  }
  float dot(const Vec3 &other) const {
    return x * other.x + y * other.y + z * other.z;
  }
  Vec3 operator*(const float &value) const {
    return {x * value, y * value, z * value};
  }
  friend Vec3 operator*(const float &value, const Vec3 &vec) {
    return vec * value;
  }
  Vec3 operator-(const Vec3 &other) const {
    return {x - other.x, y - other.y, z - other.z};
  }
  Vec3 operator+(const Vec3 &other) const {
    return {x + other.x, y + other.y, z + other.z};
  }
};

struct Ray_Sphere_Intersection_Result {
  bool is_null;
  Vec3 point;
};

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
Ray_Sphere_Intersection_Result
ray_sphere_intersection(const Vec3 &ro, const Vec3 &rd,
                        const Vec3 &sphere_center, const float &sphere_radius) {
  auto L = sphere_center - ro;
  auto tca = L.dot(rd);
  if (tca < 0)
    return {true, {0, 0, 0}};
  auto d = sqrt(L.dot(L) - tca * tca);
  if (d < 0)
    return {true, {0, 0, 0}};
  if (d > sphere_radius)
    // Ray over shoots sphere
    return {true, {0, 0, 0}};
  auto thc = sqrt(sphere_radius * sphere_radius - d * d);
  auto t0 = tca - thc;
  // t1 = tca + thc
  return {false, ro + rd * t0};
}

// def clamp(v, lower, upper):
//        return min(upper, max(v, lower))

Vec3 ray_origin(CAM_X, CAM_Y, CAM_Z);
auto SPHERE_CENTER = Vec3(.5, .5, 2);
auto SPHERE_RADIUS = 1.0;
auto LIGHT_DIRECTION = Vec3(-1, -1, -1).normalized();

int main() {
  std::ofstream file("render_cpp.ppm");
  file << "P3\n"; // "P3" means this is a RGB color image in ASCII
  file << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << '\n';
  file << "255\n"; // Maximum value for each color channel
  for (int Y = 0; Y < IMAGE_HEIGHT; Y++) {
    for (int X = 0; X < IMAGE_WIDTH; X++) {
      auto pixel_position = Vec3((X / IMAGE_WIDTH) * VIEWPORT_WIDTH,
                                 (Y / IMAGE_HEIGHT) * VIEWPORT_HEIGHT, 0.0);
      auto ray_direction = (pixel_position - ray_origin).normalized();
      file << "0 0 0\n";
    }
  }
  return 0;
}
