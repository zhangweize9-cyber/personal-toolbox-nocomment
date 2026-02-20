#include <iostream>
#include <string>
#include <regex>

/**
 * Arrows Step 3: Wildcard Translator
 */

class ArrowsTranslator {
public:
    std::string translateLine(const std::string& registryLine) {
        std::regex pattern(".*st:[a-zA-Z0-9_]+\\s*=\\s*\"(.*)\".*");
        std::smatch matches;

        if (std::regex_search(registryLine, matches, pattern)) {
            std::string content = matches[1].str();
            
            return "    std::cout << \"" + content + "\" << std::endl;";
        }

        return "// [Skip] Non-printable or unmatched line";
    }
};

int main() {
    ArrowsTranslator translator;

    std::vector<std::string> lines = {
        "global. value.st:test = \"hello world\"",
        "global. value.st:greeting=\"Justice for Arrows\"",
        "global. value.nu:count=10"
    };

    std::cout << "/* Generated C++ Execution Block */" << std::endl;
    
    for (const auto& line : lines) {
        std::string result = translator.translateLine(line);
        if (result.find("// [Skip]") == std::string::npos) {
            std::cout << result << std::endl;
        }
    }

    return 0;
}
