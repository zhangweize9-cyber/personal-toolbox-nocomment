#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct RGB { int r, g, b; };
RGB hslToRgb(float h, float s, float l) {
    auto hueToRgb = [](float p, float q, float t) {
        if (t < 0) t += 1; if (t > 1) t -= 1;
        if (t < 1.0f/6) return p + (q - p) * 6 * t;
        if (t < 1.0f/2) return q;
        if (t < 2.0f/3) return p + (q - p) * (2.0f/3 - t) * 6;
        return p;
    };
    float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    float p = 2 * l - q;
    return {(int)(hueToRgb(p, q, h + 1.0f/3) * 255), 
            (int)(hueToRgb(p, q, h) * 255), 
            (int)(hueToRgb(p, q, h - 1.0f/3) * 255)};
}

std::string colorify(char c, float h, float s = 0.8, float l = 0.6) {
    RGB rgb = hslToRgb(h/360.0f, s, l);
    return "\x1b[38;2;" + std::to_string(rgb.r) + ";" + std::to_string(rgb.g) + ";" + std::to_string(rgb.b) + "m" + c + "\x1b[0m";
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    std::ifstream file(argv[1]);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    for (size_t i = 0; i < content.length(); ++i) {
        if (content.substr(i, 10) == "successful") {
            for(int j=0; j<10; ++j) std::cout << colorify(content[i+j], 280, 0.9, 0.6);
            i += 9;
        } 
        else if (content[i] == 'a') std::cout << colorify('a', 120);
        else if (content[i] == 'o') std::cout << colorify('o', 0);
        else std::cout << content[i];
    }
    return 0;
}
