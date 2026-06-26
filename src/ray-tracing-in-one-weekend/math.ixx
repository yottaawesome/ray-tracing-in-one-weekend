export module raytracing:math;
import std;

// From https://stackoverflow.com/a/34134071/7448661
namespace
{
    constexpr auto sqrtNewtonRaphson(double x, double curr, double prev) noexcept -> double
    {
        return curr == prev
            ? curr
            : sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
    }
}

export namespace Raytracing
{
    constexpr auto sqrt(double x) noexcept -> double
    {
        return x >= 0 and x < std::numeric_limits<double>::infinity()
            ? sqrtNewtonRaphson(x, x, 0)
            : std::numeric_limits<double>::quiet_NaN();
    }
}
