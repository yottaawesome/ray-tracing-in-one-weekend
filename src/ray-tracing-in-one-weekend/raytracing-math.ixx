export module raytracing:math;
import std;

// From https://stackoverflow.com/a/34134071/7448661
namespace RayTracing::Math::Detail
{
    double constexpr sqrtNewtonRaphson(double x, double curr, double prev) noexcept
    {
        return curr == prev
            ? curr
            : sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
    }
}

export namespace RayTracing::Math
{
    double constexpr sqrt(double x) noexcept
    {
        return x >= 0 && x < std::numeric_limits<double>::infinity()
            ? Detail::sqrtNewtonRaphson(x, x, 0)
            : std::numeric_limits<double>::quiet_NaN();
    }
}
