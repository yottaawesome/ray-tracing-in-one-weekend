export module raytracing:ray;
import :vec3;

export namespace Raytracing
{
	class Ray
	{
	public:
		Ray() = default;
		Ray(const Point3& origin, const Vec3& direction)
			: orig{origin}, dir{direction}
		{}

		auto Origin() const -> const Point3& { return orig; }
		auto Direction() const -> const Vec3& { return dir; }

		auto At(double t) const -> Point3
		{
			return orig + t * dir;
		}
	private:
		Point3 orig;
		Point3 dir;
	};
}
