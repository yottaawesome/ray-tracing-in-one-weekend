export module raytracing:vec3;
import std;
import :math;

export namespace Raytracing
{
    struct Vec3
    {
        double e[3]{ 0, 0, 0 };

        constexpr Vec3() noexcept = default;
        constexpr Vec3(double e0, double e1, double e2) noexcept
            : e{ e0, e1, e2 }
        {}

        constexpr double x() const noexcept { return e[0]; }
        constexpr double y() const noexcept { return e[1]; }
        constexpr double z() const noexcept { return e[2]; }

        constexpr Vec3 operator-() const noexcept
        {
            return Vec3(-e[0], -e[1], -e[2]);
        }

        constexpr double operator[](int i) const noexcept
        {
            return e[i];
        }

        constexpr double& operator[](int i) noexcept
        {
            return e[i];
        }

        constexpr Vec3& operator+=(const Vec3& v) noexcept
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        constexpr Vec3& operator*=(double t) noexcept
        {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        constexpr Vec3& operator/=(double t) noexcept
        {
            return *this *= 1 / t;
        }

        constexpr double length() const noexcept
        {
            return sqrt(length_squared());
        }

        constexpr double length_squared() const noexcept
        {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }
    };

    // point3 is just an alias for Vec3, but useful for geometric clarity in the code.
    using Point3 = Vec3;

    // Vector Utility Functions
    inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
    {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    constexpr inline Vec3 operator+(const Vec3& u, const Vec3& v)  noexcept
    {
        return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
    }

    constexpr inline Vec3 operator-(const Vec3& u, const Vec3& v)  noexcept
    {
        return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
    }

    constexpr inline Vec3 operator*(const Vec3& u, const Vec3& v) noexcept
    {
        return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
    }

    constexpr inline Vec3 operator*(double t, const Vec3& v) noexcept
    {
        return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
    }

    constexpr inline Vec3 operator*(const Vec3& v, double t) noexcept
    {
        return t * v;
    }

    constexpr inline Vec3 operator/(const Vec3& v, double t) noexcept
    {
        return (1 / t) * v;
    }

    constexpr inline double dot(const Vec3& u, const Vec3& v) noexcept
    {
        return u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
    }

    constexpr inline Vec3 cross(const Vec3& u, const Vec3& v) noexcept
    {
        return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
            u.e[2] * v.e[0] - u.e[0] * v.e[2],
            u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    constexpr inline Vec3 unit_vector(const Vec3& v) noexcept
    {
        return v / v.length();
    }
}