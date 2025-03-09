import std;

// Creates a 256x256 PPM file.
auto main() -> int
{
    // Image
    constexpr int imageWidth = 256;
    constexpr int imageHeight = 256;
    // Render
    std::println("P3\n{} {}\n255", imageWidth, imageHeight);

    for (int j = 0; j < imageHeight; j++)
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++)
        {
            auto r = double(i) / (imageWidth - 1);
            auto g = double(j) / (imageHeight - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::println("{} {} {}", ir, ig, ib);
        }
    }

    std::clog << "\rDone.                 \n";
    return 0;
}
