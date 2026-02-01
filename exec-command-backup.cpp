#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <iomanip>
#include <array>
#include <cstdlib>
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
        if (line.substr(i, 7) == "command") {
            for(int j=0; j<7; ++j) std::cout << colorify(line[i+j], 280);
            i += 6;
        } 
        else if (line[i] == 'a') std::cout << colorify('a', 91);
        else if (line[i] == 'b') std::cout << colorify('b', 120);
        else if (line[i] == 'c') std::cout << colorify('c', 71);
        else if (line[i] == 'd') std::cout << colorify('d', 130);
        else if (line[i] == 'e') std::cout << colorify('e', 140);
        else if (line[i] == 'f') std::cout << colorify('f', 150);
        else if (line[i] == 'g') std::cout << colorify('g', 160);
        else if (line[i] == 'h') std::cout << colorify('h', 170);
        else if (line[i] == 'i') std::cout << colorify('i', 180);
        else if (line[i] == 'j') std::cout << colorify('j', 190);
        else if (line[i] == 'k') std::cout << colorify('k', 200);
        else if (line[i] == 'l') std::cout << colorify('l', 210);
        else if (line[i] == 'm') std::cout << colorify('m', 199);
        else if (line[i] == 'n') std::cout << colorify('n', 319);
        else if (line[i] == 'o') std::cout << colorify('o', 419);
        else if (line[i] == 'p') std::cout << colorify('p', 220);
        else if (line[i] == 'q') std::cout << colorify('q', 230);
        else if (line[i] == 'r') std::cout << colorify('r', 240);
        else if (line[i] == 's') std::cout << colorify('s', 250);
        else if (line[i] == 't') std::cout << colorify('t', 260);
        else if (line[i] == 'u') std::cout << colorify('u', 261);
        else if (line[i] == 'v') std::cout << colorify('v', 231);
        else if (line[i] == 'w') std::cout << colorify('w', 281);
        else if (line[i] == 'x') std::cout << colorify('x', 291);
        else if (line[i] == 'y') std::cout << colorify('y', 141);
        else if (line[i] == 'z') std::cout << colorify('z', 175);
        else std::cout << line[i];
    }
}

struct termios orig_termios;
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    std::cout << "\x1b[?25h" << std::flush;
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    std::cout << "\x1b[?25l" << std::flush;
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    std::ifstream file(argv[1]);
    std::vector<std::string> lines;
    std::string temp;
    while (std::getline(file, temp)) lines.push_back(temp);

    std::atexit(disableRawMode);
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
            if (i< (std::min((int)lines.size(), screen_height) - 1)) {
                std::cout << "\n";
            }
        }
        std::cout << std::flush;

        char c;
        if (read(STDIN_FILENO, &c, 1) == 0) continue;

        if (c == 'q' || c == 'Q') break; //
        if (c == 'k' && cursor > 0) cursor--;
        if (c == 'j' && cursor < lines.size() - 1) cursor++;
        if (c == '\n') {
            disableRawMode();
            std::string command = lines[cursor];
            std::string output = exec(command.c_str());
            std::cout << "\nExec output:\n" << output;
            return 0;
        }
    }

    disableRawMode();
    std::cout << "\nExit.\n";
    return 0;
}
