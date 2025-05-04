#include <iostream>
#include "file_parser.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: cherry-v <source_file.rsv>" << std::endl;
        return 1;
    }

    std::string file_name = argv[1];
    Parser parser;

    if (!parser.load_file(file_name)) {
        std::cerr << "Failed to load file: " << file_name << std::endl;
        return 1;
    }

    parser.preprocess();
    parser.parse_lines();

    std::cout << "========= Parsed Lines =========" << std::endl;
    for (const auto& instr : parser.get_parsed_instructions()) {
        std::cout << "[" << instr.line_number << "] " << instr.mnemonic;
        for (const auto& op : instr.operands) {
            std::cout << " " << op;
        }
        std::cout << std::endl;
    }

    return 0;
}