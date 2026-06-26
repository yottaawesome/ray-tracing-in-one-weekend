import std;

#pragma pack(push, 1)
struct BMPHeader {
    std::uint16_t fileType{ 0x4D42 };
    std::uint32_t fileSize{ 0 };
    std::uint16_t reserved1{ 0 };
    std::uint16_t reserved2{ 0 };
    std::uint32_t offsetData{ 54 };
};

struct BMPInfoHeader {
    std::uint32_t size{ 40 };
    std::int32_t width{ 0 };
    std::int32_t height{ 0 };
    std::uint16_t planes{ 1 };
    std::uint16_t bitCount{ 24 };
    std::uint32_t compression{ 0 };
    std::uint32_t imageSize{ 0 };
    std::int32_t xPixelsPerMeter{ 0 };
    std::int32_t yPixelsPerMeter{ 0 };
    std::uint32_t colorsUsed{ 0 };
    std::uint32_t colorsImportant{ 0 };
};
#pragma pack(pop)

void convertP3ToBMP(const std::string& ppmPath, const std::string& bmpPath) {
    std::ifstream ifs(ppmPath);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open PPM file: " << ppmPath << "\n";
        return;
    }

    std::string magic;
    ifs >> magic;
    if (magic != "P3") {
        std::cerr << "Invalid format. Only P3 PPM is supported.\n";
        return;
    }

    int width = 0, height = 0, maxVal = 0;
    ifs >> width >> height >> maxVal;

    int paddingSize = (4 - (width * 3) % 4) % 4;
    std::vector<uint8_t> imgData(width * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int r, g, b;
            ifs >> r >> g >> b;

            // Normalize to 8-bit if maxVal is different
            r = (r * 255) / maxVal;
            g = (g * 255) / maxVal;
            b = (b * 255) / maxVal;

            int index = ((height - 1 - y) * width + x) * 3;
            imgData[index] = static_cast<uint8_t>(b);
            imgData[index + 1] = static_cast<uint8_t>(g);
            imgData[index + 2] = static_cast<uint8_t>(r);
        }
    }
    ifs.close();

    std::ofstream ofs(bmpPath, std::ios::binary);
    if (!ofs.is_open()) {
        std::cerr << "Failed to create BMP file: " << bmpPath << "\n";
        return;
    }

    BMPHeader bmpHeader;
    BMPInfoHeader bmpInfoHeader;

    bmpInfoHeader.width = width;
    bmpInfoHeader.height = height;
    bmpInfoHeader.imageSize = (width * 3 + paddingSize) * height;
    bmpHeader.fileSize = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + bmpInfoHeader.imageSize;

    ofs.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(BMPHeader));
    ofs.write(reinterpret_cast<const char*>(&bmpInfoHeader), sizeof(BMPInfoHeader));

    uint8_t pad[3] = { 0 };
    for (int y = 0; y < height; ++y) {
        ofs.write(reinterpret_cast<const char*>(&imgData[y * width * 3]), width * 3);
        ofs.write(reinterpret_cast<const char*>(pad), paddingSize);
    }

    ofs.close();
    std::cout << "Successfully converted to " << bmpPath << "\n";
}

int main() 
{
    convertP3ToBMP("input.ppm", "output.bmp");
    return 0;
}
