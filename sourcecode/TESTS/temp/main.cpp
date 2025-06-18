#include <iostream>
#include <string>
#include <vector>

// Function to extract and remove all contents between brackets
std::vector<std::string> extractAllBracketContents(std::string& input) {
    std::vector<std::string> extractedContents;
    size_t openPos, closePos;

    while ((openPos = input.find('(')) != std::string::npos && (closePos = input.find(')', openPos)) != std::string::npos) {
        std::string extracted = input.substr(openPos + 1, closePos - openPos - 1);
        extractedContents.push_back(extracted);
        input.erase(openPos, closePos - openPos + 1); // Remove the bracketed section
    }

    return extractedContents;
}

int main() {
    std::string str = "(dffdfdfd)dduhfjkokfolsklsa4f2ff6d2g5(a1b2c3)dfokfokle(x1y2z3)(qwerty)";
    std::vector<std::string> extracted = extractAllBracketContents(str);

    std::cout << "Extracted contents:\n";
    for (const auto& item : extracted) {
        std::cout << item << std::endl;
    }

    std::cout << "Modified string: " << str << std::endl;

    return 0;
}
