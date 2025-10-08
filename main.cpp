#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "pixel.h"

void average_colors(std::vector<Pixel> &pixel_list);
void flip_vertically(std::vector<Pixel> &pixel_list);

static Pixel parse_pixel_line(const std::string &line) {
    Pixel p{};
    size_t c1 = line.find(',');
    size_t c2 = line.find(',', c1 + 1);
    size_t c3 = line.find(',', c2 + 1);
    size_t c4 = line.find(',', c3 + 1);

    std::string sx = line.substr(0, c1);
    std::string sy = line.substr(c1 + 1, c2 - (c1 + 1));
    std::string sr = line.substr(c2 + 1, c3 - (c2 + 1));
    std::string sg = line.substr(c3 + 1, c4 - (c3 + 1));
    std::string sb = line.substr(c4 + 1);

    p.x = std::stoi(sx);
    p.y = std::stoi(sy);
    p.r = static_cast<float>(std::stod(sr));
    p.g = static_cast<float>(std::stod(sg));
    p.b = static_cast<float>(std::stod(sb));
    return p;
}

void average_colors(std::vector<Pixel> &pixel_list) {
    long long n = static_cast<long long>(pixel_list.size());
    long double sumR = 0.0L, sumG = 0.0L, sumB = 0.0L;
    for (const auto &p : pixel_list) {
        sumR += p.r;
        sumG += p.g;
        sumB += p.b;
    }
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Average R: " << static_cast<double>(sumR / n) << "\n";
    std::cout << "Average G: " << static_cast<double>(sumG / n) << "\n";
    std::cout << "Average B: " << static_cast<double>(sumB / n) << "\n";
}

void flip_vertically(std::vector<Pixel> &pixel_list) {
    int maxY = 0;
    for (const auto &p : pixel_list) if (p.y > maxY) maxY = p.y;
    int height = maxY + 1;
    for (auto &p : pixel_list) p.y = (height - 1) - p.y;
}

int main(int argc, char* argv[]) {
    std::string inputFile = (argc >= 2) ? argv[1] : "pixels.dat";

    std::ifstream in(inputFile);
    std::vector<Pixel> pixel_list;
    
    std::string line;
    while (std::getline(in, line)) {
        Pixel p = parse_pixel_line(line);
        pixel_list.push_back(p);
    }
    in.close();

    average_colors(pixel_list);
    flip_vertically(pixel_list);

    std::ofstream out("flipped.dat");
    out << std::setprecision(16);
    for (const auto &p : pixel_list) {
        out << p.x << ',' << p.y << ',' << p.r << ',' << p.g << ',' << p.b << '\n';
    }
    out.close();

    std::cout << "Flipped image written to flipped.dat\n";
    return 0;
}
