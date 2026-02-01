#include <iostream>
#include <fstream>
#include <string>
// `g++ highlight-purple.cpp -o highlighter`

const std::string PURPLE = "\x1b[38;2;155;89;182;1m";  // purple
const std::string RESET = "\x1b[0m";
const std::string TARGET = "successful";

void highlightFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file." << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = 0;
        while ((pos = line.find(TARGET, pos)) != std::string::npos) {
            line.replace(pos, TARGET.length(), PURPLE + TARGET + RESET);
            pos += PURPLE.length() + TARGET.length() + RESET.length();
        }
        std::cout << line << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./highlighter <filename>" << std::endl;
        return 1;
    }
    highlightFile(argv[1]);
    return 0;
}
