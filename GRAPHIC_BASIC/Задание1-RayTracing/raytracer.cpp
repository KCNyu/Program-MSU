#include <tuple>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

class vec3
{
public:
    float x = 0, y = 0, z = 0;
    constexpr vec3() : x(0), y(0), z(0) {}
    constexpr vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    constexpr vec3(const vec3 &v) : x(v.x), y(v.y), z(v.z) {}
    vec3 &operator=(const vec3 &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    vec3 &operator+=(const vec3 &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    vec3 &operator-=(const vec3 &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    vec3 &operator*=(const float v)
    {
        x *= v;
        y *= v;
        z *= v;
        return *this;
    }
    vec3 &operator/=(const float v)
    {
        x /= v;
        y /= v;
        z /= v;
        return *this;
    }
    float &operator[](const int i) { return i == 0 ? x : (1 == i ? y : z); }
    const float &operator[](const int i) const { return i == 0 ? x : (1 == i ? y : z); }
    vec3 operator+(const vec3 &v) const { return vec3(x + v.x, y + v.y, z + v.z); }
    vec3 operator-(const vec3 &v) const { return vec3(x - v.x, y - v.y, z - v.z); }
    vec3 operator*(const float v) const { return vec3(x * v, y * v, z * v); }
    vec3 operator/(const float v) const { return vec3(x / v, y / v, z / v); }
    float operator*(const vec3 &v) const { return x * v.x + y * v.y + z * v.z; }
    vec3 operator-() const { return vec3(-x, -y, -z); }
    float norm() const { return std::sqrt(x * x + y * y + z * z); }
    vec3 normalized() { return (*this) * (1.f / norm()); }
    static vec3 cross(const vec3 v1, const vec3 v2)
    {
        return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
    }
    static vec3 reflect(const vec3 &v1, const vec3 &v2)
    {
        return v1 - v2 * 2.f * (v1 * v2);
    }
    static vec3 refract(const vec3 &I, const vec3 &N, const float eta_t, const float eta_i = 1.f)
    {
        float cosi = -std::max(-1.f, std::min(1.f, I * N));
        if (cosi < 0)
            return refract(I, -N, eta_i, eta_t);
        float eta = eta_i / eta_t;
        float k = 1 - eta * eta * (1 - cosi * cosi);
        return k < 0 ? vec3{1, 0, 0} : I * eta + N * (eta * cosi - std::sqrt(k));
    }
};
class Material
{
public:
    float refractive_index = 1;
    float albedo[4] = {2, 0, 0, 0};
    vec3 diffuse_color = {0, 0, 0};
    float specular_exponent = 0;
};

class Sphere
{
public:
    vec3 center;
    float radius;
    Material material;

    constexpr Sphere() : center({0, 0, 0}), radius(0) {}
    constexpr Sphere(vec3 center, float radius, Material material) : center(center), radius(radius), material(material) {}
};

constexpr Material ivory = {1.0, {0.9, 0.5, 0.1, 0.0}, {0.3, 0.5, 0.7}, 50.};
constexpr Material red_rubber = {1.0, {1.4, 0.3, 0.0, 0.0}, {0.3, 0.1, 0.1}, 10.};

constexpr Sphere spheres[] = {
    {{-3, 0, -16}, 2.3, ivory},
    {{1.5, 3, -12}, 1.7, red_rubber},
};
constexpr vec3 lights[] = {{-20, 20, 20}, {30, 50, -25}};

std::tuple<bool, float> ray_sphere_intersect(const vec3 &orig, const vec3 &dir, const Sphere &s)
{
    vec3 L = s.center - orig;
    float tca = L * dir;
    float d2 = L * L - tca * tca;
    if (d2 > s.radius * s.radius)
        return {false, 0};
    float thc = std::sqrt(s.radius * s.radius - d2);
    float t0 = tca - thc, t1 = tca + thc;
    if (t0 > .001)
        return {true, t0};
    if (t1 > .001)
        return {true, t1};
    return {false, 0};
}
std::tuple<bool, vec3, vec3, Material> scene_intersect(const vec3 &orig, const vec3 &dir)
{
    vec3 pt, N;
    Material material;

    float nearest_dist = 1e10;
    if (std::abs(dir.y) > .001)
    {                                    // intersect the ray with the checkerboard, avoid division by zero
        float d = -(orig.y + 4) / dir.y; // the checkerboard plane has equation y = -4
        vec3 p = orig + dir * d;
        if (d > .001 && d < nearest_dist && std::abs(p.x) < 10 && p.z < -10 && p.z > -30)
        {
            nearest_dist = d;
            pt = p;
            N = {0, 1, 0};
            material.diffuse_color =  vec3{.3, .3, .3};
        }
    }

    for (const Sphere &s : spheres)
    { // intersect the ray with all spheres
        auto [intersection, d] = ray_sphere_intersect(orig, dir, s);
        if (!intersection || d > nearest_dist)
            continue;
        nearest_dist = d;
        pt = orig + dir * nearest_dist;
        N = (pt - s.center).normalized();
        material = s.material;
    }
    return {nearest_dist < 1000, pt, N, material};
}

vec3 cast_ray(const vec3 &orig, const vec3 &dir, const int depth = 0)
{
    auto [hit, point, N, material] = scene_intersect(orig, dir);
    if (depth > 4 || !hit)
        return {0.5, 0.5, 0.5}; // background color

    vec3 reflect_dir = vec3::reflect(dir, N).normalized();
    vec3 refract_dir = vec3::refract(dir, N, material.refractive_index).normalized();
    vec3 reflect_color = cast_ray(point, reflect_dir, depth + 1);
    vec3 refract_color = cast_ray(point, refract_dir, depth + 1);

    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for (const vec3 &light : lights)
    { // checking if the point lies in the shadow of the light
        vec3 light_dir = (light - point).normalized();
        auto [hit, shadow_pt, trashnrm, trashmat] = scene_intersect(point, light_dir);
        if (hit && (shadow_pt - point).norm() < (light - point).norm())
            continue;
        diffuse_light_intensity += std::max(0.f, light_dir * N);
        specular_light_intensity += std::pow(std::max(0.f, -vec3::reflect(-light_dir, N) * dir), material.specular_exponent);
    }
    return material.diffuse_color * diffuse_light_intensity * material.albedo[0] + vec3{1., 1., 1.} * specular_light_intensity * material.albedo[1] + reflect_color * material.albedo[2] + refract_color * material.albedo[3];
}

int main()
{
    constexpr int width = 1024;
    constexpr int height = 768;
    constexpr float fov = 1.05; // 60 degrees field of view in radians
    std::vector<vec3> framebuffer(width * height);
    for (int pix = 0; pix < width * height; pix++)
    { // actual rendering loop
        float dir_x = (pix % width + 0.5) - width / 2.;
        float dir_y = -(pix / width + 0.5) + height / 2.; // this flips the image at the same time
        float dir_z = -height / (2. * tan(fov / 2.));
        framebuffer[pix] = cast_ray(vec3{0, 0, 0}, vec3{dir_x, dir_y, dir_z}.normalized());
    }

    std::ofstream ofs("./out.ppm", std::ios::binary);
    ofs << "P6\n"
        << width << " " << height << "\n255\n";
    for (vec3 &color : framebuffer)
    {
        float max = std::max(1.f, std::max(color[0], std::max(color[1], color[2])));
        for (int chan : {0, 1, 2})
            ofs << (char)(255 * color[chan] / max);
    }
    return 0;
}
