//
// Created by cherry on 5/4/25.
//

#include "file_parser.hpp"
#include <algorithm>
#include <iostream>

bool Parser::load_file(const std::string &file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "[Parser] Could not open file: " << file_name << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return true;
}

void Parser::preprocess() {
    std::vector<std::string> cleaned_lines;
    for (auto& line : lines) {
        std::string trimmed = trim(line);
        if (!is_comment_or_empty(trimmed)) {
            cleaned_lines.push_back(trimmed);
        }
    }
    lines = cleaned_lines;
}

void Parser::parse_lines() {
    int line_num = 1;
    for (const auto& line : lines) {
        std::vector<std::string> tokens = tokenize(line);
        if (tokens.empty()) {
            ++line_num;
            continue;
        }

        InstructionToken token;
        token.mnemonic = tokens[0];
        token.operands = std::vector<std::string>(tokens.begin() + 1, tokens.end());
        token.line_number = line_num;

        if (!validate_instruction(token)) {
            std::cerr << "[Parser] Invalid instruction at line " << line_num << ": " << line << std::endl;
            continue;
        }

        instructions.push_back(token);
        ++line_num;
    }
}

std::vector<InstructionToken> Parser::get_parsed_instructions() const {
    return instructions;
}

std::string Parser::trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

bool Parser::is_comment_or_empty(const std::string &line) {
    return line.empty() || line[0] == '#' || line[0] == ';';
}

std::vector<std::string> Parser::tokenize(const std::string &line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;

    while (std::getline(iss, token, ',')) {
        std::istringstream sub_iss(token);
        std::string sub_token;
        while (sub_iss >> sub_token) {
            tokens.push_back(sub_token);
        }
    }

    return tokens;
}

bool Parser::validate_instruction(const InstructionToken &token) {
    return isa::opcode_table.find(token.mnemonic) != isa::opcode_table.end();
}

std::optional<isa::InstructionFormat> Parser::get_opcode_info(const std::string &mnemonic) {
    auto it = isa::opcode_table.find(mnemonic);
    if (it == isa::opcode_table.end()) {
        return it->second;
    }
    return std::nullopt;
}
