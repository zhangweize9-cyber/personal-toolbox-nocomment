#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <iomanip>
#include <array>
#include <cstdlib>
#include <filesystem>
// `g++ -std=c++17 pretty-error-output.cpp -o peoutput`

namespace fs = std::filesystem;

// Using hsl display colors.
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
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) result += buffer.data();
    pclose(pipe);
    return result;
}

// WIP
// void renderLineContent(std::string line) {
//     size_t pos = 0;
//
//     struct Tag { std::string key; std::string color; };
//     std::vector<Tag> tags = {
//         {"[error]", "\x1b[1;31mERROR\x1b[0m"},
//         {"[warning]", "\x1b[1;33mWARN\x1b[0m"},
//         {"[hint]", "\x1b[1;32mHINT\x1b[0m"},
//         {"[info]", "\x1b[1;34mINFO\x1b[0m"}
//     };
//
//     for (const auto& tag : tags) {
//         if ((pos = line.find(tag.key)) != std::string::npos) {
//             std::cout << tag.color << " ";
//             line.erase(pos, tag.key.length());
//             break; 
//         }
//     }
//
//     for (size_t i = 0; i < line.length(); ++i) {
//         if (i + 7 <= line.length() && line.substr(i, 7) == "command") {
//             for(int j=0; j<7; ++j) std::cout << colorify(line[i+j], 280);
//             i += 6;
//         } 
//         else if (i + 9 <= line.length() && line.substr(i, 9) == "Traceback") {
//             std::cout << "\x1b[1;36mTraceback\x1b[0m";
//             i += 8;
//         }
//         else if (std::string("()/.").find(line[i]) != std::string::npos) {
//             std::cout << colorify(line[i], 200);
//         }
//         else {
//             std::cout << line[i];
//         }
//     }
// }
void renderLineContent(std::string line) {
    size_t pos = 0;
    struct Tag { std::string key; std::string color; };
    std::vector<Tag> tags = {
        {"[error]", "\x1b[1;31mERROR\x1b[0m"},
        {"[warning]", "\x1b[1;33mWARN\x1b[0m"},
        {"[hint]", "\x1b[1;32mHINT\x1b[0m"},
        {"[info]", "\x1b[1;34mINFO\x1b[0m"}
    };

    for (const auto& tag : tags) {
        if ((pos = line.find(tag.key)) != std::string::npos) {
            std::cout << tag.color << " ";
            line.erase(pos, tag.key.length());
            break; 
        }
    }

    for (size_t i = 0; i < line.length(); ++i) {
        if (i + 7 <= line.length() && line.substr(i, 7) == "command") {
            for(int j=0; j<7; ++j) std::cout << colorify(line[i+j], 280);
            i += 6;
        } 
        else if (i + 9 <= line.length() && line.substr(i, 9) == "Traceback") {
            std::cout << "\x1b[1;36mTraceback\x1b[0m";
            i += 8;
        }
        else if (std::string("()/\\.:-").find(line[i]) != std::string::npos) {
            std::cout << "\x1b[38;2;60;140;255m" << line[i] << "\x1b[0m";
        }
        else {
            std::cout << line[i];
        }
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

// int main(int argc, char* argv[]) {
//     if (argc < 2) return 1;
//     std::ifstream file(argv[1]);
//     std::vector<std::string> lines;
//     std::string temp;
//     while (std::getline(file, temp)) lines.push_back(temp);
//
//     enableRawMode();
//     int cursor = 0;
//
//     while (true) {
//         std::cout << "\x1b[H\x1b[2J"; 
//         std::cout << "Debug Mode [k/j:move, Enter:output, Q:quit]\n\n";
//
//         for (int i = 0; i < (int)lines.size(); ++i) {
//             std::cout << std::setw(3) << i + 1 << " ";
//
//             if (i == cursor) std::cout << "\x1b[1;35m* \x1b[0m";
//             else std::cout << "  ";
//
//             renderLineContent(lines[i]);
//             std::cout << "\n";
//         }
//         std::cout << std::flush;
//
//         char c;
//         if (read(STDIN_FILENO, &c, 1) == 0) continue;
//         if (c == 'q' || c == 'Q') break;
//         if (c == 'k' && cursor > 0) cursor--;
//         if (c == 'j' && cursor < (int)lines.size() - 1) cursor++;
//         if (c == '\n') {
//             disableRawMode();
//             std::string output = exec(lines[cursor].c_str());
//             std::cout << "\nExec output:\n" << output;
//             return 0;
//         }
//     }
//     return 0;
// }

int main(int argc, char* argv[]) {
    std::vector<std::string> lines;
    
    if (!isatty(STDIN_FILENO)) {
        std::string input_line;
        while (std::getline(std::cin, input_line)) lines.push_back(input_line);
        freopen("/dev/tty", "r", stdin);
    } else if (argc >= 2) {
        std::ifstream file(argv[1]);
        std::string temp;
        while (std::getline(file, temp)) lines.push_back(temp);
    }

    if (lines.empty()) { std::cout << "No content to audit.\n"; return 0; }

    enableRawMode();
    int cursor = 0;

    while (true) {
        std::cout << "\x1b[H\x1b[2J"; 
        std::cout << "Audit Mode [k/j:move, G:line_num, Enter:jump/exec, Q:quit]\n\n";

        for (int i = 0; i < (int)lines.size(); ++i) {
            std::cout << std::setw(3) << i + 1 << (i == cursor ? " \x1b[1;35m* \x1b[0m" : "   ");
            renderLineContent(lines[i]);
            std::cout << "\n";
        }

        char c;
        if (read(STDIN_FILENO, &c, 1) <= 0) continue;

        if (c == 'q' || c == 'Q') break;
        if (c == 'k' && cursor > 0) cursor--;
        if (c == 'j' && cursor < (int)lines.size() - 1) cursor++;
        
        if (c == 'G' || c == 'g') {
            disableRawMode();
            std::cout << "\nJump to line: ";
            int target; std::cin >> target;
            if (target > 0 && target <= lines.size()) cursor = target - 1;
            enableRawMode();
        }

        if (c == '\n') {
            std::string selected = lines[cursor];
            if (fs::exists(selected)) {
                if (fs::is_directory(selected)) {
                    lines.clear();
                    for (const auto& entry : fs::directory_iterator(selected)) 
                        lines.push_back(entry.path().string());
                    cursor = 0;
                } else {
                    std::ifstream f(selected);
                    lines.clear();
                    std::string t;
                    while (std::getline(f, t)) lines.push_back(t);
                    cursor = 0;
                }
            } else {
                disableRawMode();
                std::cout << "\nExec: " << selected << "\n" << exec(selected.c_str());
                return 0;
            }
        }
    }
    return 0;
}
