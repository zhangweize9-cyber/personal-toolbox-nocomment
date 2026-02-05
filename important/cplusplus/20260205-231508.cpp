#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <iomanip>
#include <array>
// `g++ exec-command.cpp -o exec-cmd`

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

std::string colorify(char c, float h) {
    RGB r = hslToRgb(h/360.0f, 0.8, 0.6);
    return "\x1b[38;2;" + std::to_string(r.r) + ";" + std::to_string(r.g) + ";" + std::to_string(r.b) + "m" + c + "\x1b[0m";
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "Error";
    
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    pclose(pipe);
    return result;
}

void renderLineContent(const std::string& line) {
    for (size_t i = 0; i < line.length(); ++i) {
        if (line.substr(i, 10) == "successful") {
            for(int j=0; j<10; ++j) std::cout << colorify(line[i+j], 280);
            i += 9;
        } 
        else if (line[i] == 'a') std::cout << colorify('a', 120);
        else if (line[i] == 'o') std::cout << colorify('o', 0);
        else std::cout << line[i];
    }
}

struct termios orig_termios;
void disableRawMode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); }
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    std::ifstream file(argv[1]);
    std::vector<std::string> lines;
    std::string temp;
    while (std::getline(file, temp)) lines.push_back(temp);

    enableRawMode();
    int cursor = 0;
    int screen_height = 20;

    while (true) {
        std::cout << "\x1b[H\x1b[2J"; 
        std::cout << "--- Command Mode [k/j:move, Enter:output, Q:quit] ---\n\n";

        for (int i = 0; i < lines.size() && i < screen_height; ++i) {
            std::cout << std::setw(3) << i + 1 << " ";
            
            if (i == cursor) std::cout << "\x1b[1;35m* \x1b[0m";
            else std::cout << "  ";

            renderLineContent(lines[i]);
            std::cout << "\n";
        }

        char c;
        if (read(STDIN_FILENO, &c, 1) == 0) continue;

        if (c == 'q' || c == 'Q') break; //
        if (c == 'k' && cursor > 0) cursor--;
        if (c == 'j' && cursor < lines.size() - 1) cursor++;
        if (c == '\n') {
            disableRawMode();
            std::string command = lines[cursor];
            std::string output = exec(command.c_str());
            std::cout << "Exec output: " << output;
            return 0;
        }
    }

    disableRawMode();
    std::cout << "\nExit.\n";
    return 0;
}
