#include <iostream>
#include <cstdlib>
#include <string>
// `g++ colorful-string.cpp -o colorful-string`

bool isTrueColorSupported() {
    char* colorterm = std::getenv("COLORTERM");
    if (colorterm != nullptr) {
        std::string val(colorterm);
        return (val == "truecolor" || val == "24bit");
    }
    return false;
}

void printTrueColor(int r, int g, int b, const std::string& text) {
    std::cout << "\x1b[38;2;" << r << ";" << g << ";" << b << "m" 
              << text << "\x1b[0m" << std::endl;
}

int main() {
    // if (isTrueColorSupported()) {
        printTrueColor(155, 89, 182, "True Color Mode: Enabled.");
    // } else {
        // std::cout << "Standard Mode: Disabled." << std::endl;
    // }
    return 0;
}
