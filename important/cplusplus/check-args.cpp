// Step 1
// Import the builtin library.
// e.g. iostream, vector, unistd.h
#include <iostream>
#include <vector>
#include <unistd.h>

// Step 2
// Create a class named `SecureSettings`
class SecureStrings {
private:
    // Step 3
    // Create a const table named `fs_whitelist`.
    // Type: vector, string
    const std::vector<std::string> fs_whitelist = {"test1", "test2",
                                                   "test3", "test4"};

    // Step 4
    // Create a boolean variable named `found`.
    // Set default value to false.
    bool found = false;

public:
    // Step 5
    // Called a function named `run()`.
    // Here are two arguments.
    // - int:  Declaring variables that need to store counts, quantities, IDs, etc.
    // - char: A pointer to a char (memory address). Commonly used to point to the first character of a C-style string.
    // This function accepts two arguments as input.
    // - argc: Arguments Count.
    // - argv: Arguments Variable.
    void run(int argc, char *argv[]) {
        // 1. Using for cycle to scan the `fs_whitelist` all variables.
        for (const std::string &fs : fs_whitelist) {
            // 2. If arguments count less than two, then return a tip.
            if (argc < 2) {
                std::cerr << "Error: Require at least one arguments." << std::endl;
                std::cout << "Usage: check-args <word>." << std::endl;
            // 3. If arguments including `fs_whitelist`, change `found` variable boolean true.(Set true)
            //    Then break the cycle.
            } else if (argv[1] == fs) {
                found = true;
                break;
            }
        }

        if (found) {
            std::cout << "Passed:" << "`" << argv[1] << "`" << std::endl;
        } else {
            std::cout << "This arguments is unsafe." << std::endl;
        }
    }
};

// Step 6
// Call `main()` function.
int main(int argc, char *argv[]) {
    // 1. Initialization class: `SecureStrings` as `SStrings`.
    SecureStrings SStrings;
    // 2. Reference class function: `SStrings.run()`.
    SStrings.run(argc, argv);

    // 3. Execution successful.
    return 0;
}

// README This is usage and build steps!
// NOTE: `g++ check-args.cpp -o ./check-args`
//       `./check-args <argv>`
