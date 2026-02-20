#include <iostream>
#include <string>
#include <map>
#include <functional>

struct Arg {
    std::string value;
    std::function<void(const std::string&)> onChange;
};

int main(int argc, char* argv[]) {
    std::cout << "Hello World!" << std::endl;
    std::map<std::string, Arg> args;

    args["-n"].onChange = [](const std::string& val) {
        std::cout << "Number set to " << val << std::endl;
    };

    args["--output"].onChange = [](const std::string& val) {
        std::cout << "Output file to " << val << std::endl;
    };

    for (int i = 1; i < argc; i++) {
	std::string token = argv[i];

	if (token == "-n" || token == "--output") {
	    if (i + 1 < argc) {
		std::string val = argv[i + 1];
		i++;
		args[token].value = val;
		if (args[token].onChange) args[token].onChange(val);
	    }
	} else {
	    args["input"].value = token;
	    if (args["input"].onChange) args["input"].onChange(token);
	}
    }

    int n = std::stoi(args["-n"].value);
    std::string inputFile = args["input"].value;
    std::string outputFile = args["--output"].value;

    std::cout << "Running test -n " << n
	      << " " << inputFile
	      << " --output" << outputFile << std::endl;

    return 0;
}
