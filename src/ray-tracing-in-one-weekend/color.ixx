export module raytracing:color;
import std;
import :vec3;

export namespace Raytracing
{
    using Color = Vec3;

    void WriteColor(std::ostream& out, const Color& pixel_color) 
    {
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();

        // Translate the [0,1] component values to the byte range [0,255].
        auto rbyte = static_cast<int>(255.999 * r);
        auto gbyte = static_cast<int>(255.999 * g);
        auto bbyte = static_cast<int>(255.999 * b);

        // Write out the pixel color components.
        out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
    }
}
