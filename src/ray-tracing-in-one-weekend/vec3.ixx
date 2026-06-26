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

        constexpr auto x() const noexcept -> double { return e[0]; }
        constexpr auto y() const noexcept -> double { return e[1]; }
        constexpr auto z() const noexcept -> double { return e[2]; }

        constexpr auto operator-() const noexcept -> Vec3
        {
            return Vec3(-e[0], -e[1], -e[2]);
        }

        constexpr auto operator[](int i) const noexcept -> double
        {
            return e[i];
        }

        constexpr auto operator[](int i) noexcept -> double&
        {
            return e[i];
        }

        constexpr auto operator+=(const Vec3& v) noexcept -> Vec3&
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        constexpr auto operator*=(double t) noexcept -> Vec3&
        {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        constexpr auto operator/=(double t) noexcept -> Vec3&
        {
            return *this *= 1 / t;
        }

        constexpr auto length() const noexcept -> double
        {
            return sqrt(length_squared());
        }

        constexpr auto length_squared() const noexcept -> double
        {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }
    };

    // point3 is just an alias for Vec3, but useful for geometric clarity in the code.
    using Point3 = Vec3;

    // Vector Utility Functions
    inline auto operator<<(std::ostream& out, const Vec3& v) -> std::ostream&
    {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    inline constexpr auto operator+(const Vec3& u, const Vec3& v)  noexcept -> Vec3
    {
        return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
    }

    inline constexpr auto operator-(const Vec3& u, const Vec3& v)  noexcept -> Vec3
    {
        return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
    }

    inline constexpr auto operator*(const Vec3& u, const Vec3& v) noexcept -> Vec3
    {
        return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
    }

    inline constexpr auto operator*(double t, const Vec3& v) noexcept -> Vec3
    {
        return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
    }

    inline constexpr auto operator*(const Vec3& v, double t) noexcept -> Vec3
    {
        return t * v;
    }

    inline constexpr auto operator/(const Vec3& v, double t) noexcept -> Vec3
    {
        return (1 / t) * v;
    }

    inline constexpr auto Dot(const Vec3& u, const Vec3& v) noexcept -> double
    {
        return u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
    }

    inline constexpr auto Cross(const Vec3& u, const Vec3& v) noexcept -> Vec3
    {
        return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
            u.e[2] * v.e[0] - u.e[0] * v.e[2],
            u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    inline constexpr auto UnitVector(const Vec3& v) noexcept -> Vec3
    {
        return v / v.length();
    }
}
