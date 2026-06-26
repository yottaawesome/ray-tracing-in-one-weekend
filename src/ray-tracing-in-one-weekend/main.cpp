import std;
import raytracing;

// See 5.1 Ray-Sphere Intersection for the mathematics of this function.
constexpr auto HitSphere(const Raytracing::Point3& center, double radius, const Raytracing::Ray& r) -> bool
{
    auto oc = Raytracing::Vec3{ center - r.Origin() };
    auto a = Raytracing::Dot(r.Direction(), r.Direction());
    auto b = -2.0 * Raytracing::Dot(r.Direction(), oc);
    auto c = Raytracing::Dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}

auto RayColor(const Raytracing::Ray& r) -> Raytracing::Color
{
    if (HitSphere(Raytracing::Point3{ 0, 0, -1 }, 0.5, r))
        return Raytracing::Color{ 1, 0, 0 };

    // A lerp between two values white and blue.
    // blendedValue=(1−a)⋅startValue+a⋅endValue, with a|0<=a<=1
    auto unitDirection = Raytracing::UnitVector(r.Direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * Raytracing::Color{ 1.0, 1.0, 1.0 } + a * Raytracing::Color{ 0.5, 0.7, 1.0 };
}

// If you don't have a locally-installed PPM viewer, 
// you use https://0xc0de.fr/webppm/.
auto main() -> int
{
    // Image
    constexpr auto aspectRatio = 16.0 / 9.0;
    constexpr auto imageWidth = 400;
    constexpr auto intRatio = static_cast<int>(imageWidth / aspectRatio);

    // Calculate the image height, and ensure that it's at least 1.
    constexpr auto imageHeight = (intRatio < 1) ? 1 : intRatio;

    // Camera
    constexpr auto focalLength = 1.0;
    constexpr auto viewportHeight = 2.0;
    constexpr auto viewportWidth = viewportHeight * (double{ imageWidth } / imageHeight);
    constexpr auto cameraCenter = Raytracing::Point3{ 0, 0, 0 };

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    constexpr auto viewportU = Raytracing::Vec3(viewportWidth, 0, 0);
    constexpr auto viewportV = Raytracing::Vec3(0, -viewportHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    constexpr auto pixelDeltaU = viewportU / imageWidth;
    constexpr auto pixelDeltaV = viewportV / imageHeight;

    // Calculate the location of the upper left pixel.
    auto viewportUpperLeft = cameraCenter - Raytracing::Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    auto pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    // Render

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) 
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) 
        {
            auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            auto r = Raytracing::Ray(cameraCenter, rayDirection);

            auto pixelColor = Raytracing::Color{ RayColor(r) };
            Raytracing::WriteColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";

    return 0;
}
