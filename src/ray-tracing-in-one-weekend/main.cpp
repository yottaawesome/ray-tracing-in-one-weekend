import std;
import raytracing;

// Creates a 256x256 PPM file.
// If you don't have a locally-installed PPM viewer, 
// you use https://0xc0de.fr/webppm/.
auto main() -> int
{
    // Image
    constexpr auto imageWidth = 256;
    constexpr auto imageHeight = 256;

    // Render
    std::cout << std::format("P3\n{} {}\n255\n", imageWidth, imageHeight);

    for (int j = 0; j < imageHeight; j++)
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++)
        {
            auto pixel_color = Raytracing::Color(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0);
            Raytracing::WriteColor(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
    return 0;
}
