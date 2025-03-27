#include <iostream>
#include <vector>
#include <sstream>
#include <deque>
#include <limits>
#include <algorithm>
#include <unordered_set>

#define HISTORY_SIZE 50

const std::vector<int> SUPPORTED_BASES = {
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 20, 24, 26, 32, 36, 
    60, 64, 81, 100, 256, 1024, 4096, 1'000'000
};

std::deque<std::string> history;

/// Convert a number from any base to decimal (Base-10)
unsigned long long to_decimal(const std::string& number, int from_base) {
    try {
        return std::stoull(number, nullptr, from_base);
    } catch (...) {
        throw std::runtime_error("Error: Invalid number '" + number + "' for base " + std::to_string(from_base));
    }
}

/// Convert a decimal number to any other base, with optional explanation
std::string from_decimal(unsigned long long decimal_value, int to_base, bool explain) {
    if (decimal_value == 0) return "0";

    const std::string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result;
    std::ostringstream explanation;

    while (decimal_value > 0) {
        int remainder = decimal_value % to_base;
        result.insert(result.begin(), digits[remainder]);
        if (explain) {
            explanation << decimal_value << " ÷ " << to_base << " = " 
                        << decimal_value / to_base << ", remainder = " << remainder << "\n";
        }
        decimal_value /= to_base;
    }

    if (explain) std::cout << "\nConversion Explanation:\n" << explanation.str();
    return result;
}

/// Perform arithmetic operations (+, -, *, /) in a given base
std::string perform_operation(const std::string& num1, const std::string& num2, int base, char operation) {
    unsigned long long dec1 = to_decimal(num1, base);
    unsigned long long dec2 = to_decimal(num2, base);
    unsigned long long result = 0;

    switch (operation) {
        case '+': result = dec1 + dec2; break;
        case '-': result = (dec1 > dec2) ? dec1 - dec2 : 0; break;
        case '*': result = dec1 * dec2; break;
        case '/': 
            if (dec2 == 0) throw std::runtime_error("Error: Division by zero");
            result = dec1 / dec2; 
            break;
        default: throw std::runtime_error("Error: Invalid operation");
    }

    return from_decimal(result, base, false);
}

/// Axion AI suggests the most optimal base for the given number
int suggest_best_base(const std::string& number) {
    size_t length = number.length();
    if (length <= 5) return 2;
    if (length <= 10) return 10;
    if (length <= 15) return 16;
    if (length <= 30) return 60;
    return 81;
}

/// Confirm large base operations
bool confirm_large_operation(int base) {
    if (base > 256) {
        std::cout << "Warning: Operations in base " << base << " may be slow. Continue? (y/n): ";
        std::string input;
        std::getline(std::cin, input);
        return input == "y" || input == "Y";
    }
    return true;
}

/// Print detailed help information
void print_help() {
    std::cout << "Usage: t81base <command> [options]\n\n"
              << "Commands:\n"
              << "  convert <num> <from_base> <to_base>  Convert number between bases\n"
              << "  calc <num1> <op> <num2> <base>       Perform arithmetic in a base\n"
              << "  suggest <num>                        Suggest optimal base\n"
              << "  --interactive                        Start interactive mode\n"
              << "  --explain                            Show step-by-step conversion\n"
              << "  --help                               Show this help menu\n\n"
              << "Supported Bases:\n";
    for (int base : SUPPORTED_BASES) {
        std::cout << "  Base-" << base << "  Supported\n";
    }
    std::cout << std::endl;
}

/// Interactive mode with command history
void interactive_mode() {
    std::cout << "T81Base Interactive Mode - Type 'exit' to quit\n";

    while (true) {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);
        if (input.empty()) continue;

        if (history.size() >= HISTORY_SIZE) history.pop_front();
        history.push_back(input);

        std::istringstream iss(input);
        std::vector<std::string> args{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

        if (args.empty()) continue;

        try {
            if (args[0] == "convert" && args.size() >= 4) {
                std::string number = args[1];
                int from_base = std::stoi(args[2]);
                int to_base = std::stoi(args[3]);
                bool explain = args.size() == 5 && args[4] == "--explain";

                if (confirm_large_operation(to_base)) {
                    std::cout << "Result: " << from_decimal(to_decimal(number, from_base), to_base, explain) << "\n";
                }
            } else if (args[0] == "calc" && args.size() == 5) {
                std::cout << "Result: " << perform_operation(args[1], args[3], std::stoi(args[4]), args[2][0]) << "\n";
            } else if (args[0] == "suggest" && args.size() == 2) {
                std::cout << "Suggested base: " << suggest_best_base(args[1]) << "\n";
            } else if (args[0] == "exit") {
                std::cout << "Exiting Interactive Mode...\n";
                break;
            } else {
                std::cout << "Invalid command. Use 'convert', 'calc', 'suggest', or 'exit'.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
        }
    }
}

/// Command-line execution
int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return 1;
    }

    std::string command = argv[1];

    try {
        if (command == "convert" && argc >= 5) {
            std::cout << from_decimal(to_decimal(argv[2], std::stoi(argv[3])), std::stoi(argv[4]), argc == 6 && std::string(argv[5]) == "--explain") << "\n";
        } else if (command == "calc" || command == "suggest") {
            interactive_mode();
        } else if (command == "--interactive") {
            interactive_mode();
        } else if (command == "--help") {
            print_help();
        } else {
            print_help();
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
