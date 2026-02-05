#include <iostream>
#include <cmath>
#include <string>

struct RGB { int r, g, b; };

RGB hslToRgb(float h, float s, float l) {
    auto hueToRgb = [](float p, float q, float t) {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        if (t < 1.0f/6) return p + (q - p) * 6 * t;
        if (t < 1.0f/2) return q;
        if (t < 2.0f/3) return p + (q - p) * (2.0f/3 - t) * 6;
        return p;
    };

    float r, g, b;
    if (s == 0) {
        r = g = b = l;
    } else {
        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;
        r = hueToRgb(p, q, h + 1.0f/3);
        g = hueToRgb(p, q, h);
        b = hueToRgb(p, q, h - 1.0f/3);
    }
    return {(int)(r * 255), (int)(g * 255), (int)(b * 255)};
}

std::string getHslString(float h_deg, float s_per, float l_per, const std::string& text) {
    RGB color = hslToRgb(h_deg / 360.0f, s_per / 100.0f, l_per / 100.0f);
    return "\x1b[38;2;" + std::to_string(color.r) + ";" + 
           std::to_string(color.g) + ";" + std::to_string(color.b) + "m" + text + "\x1b[0m";
}

int main() {
    std::cout << getHslString(280, 70, 60, "successful") << std::endl;
    return 0;
}
