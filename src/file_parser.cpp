//
// Created by cherry on 5/4/25.
//

#include "file_parser.hpp"
#include "tables.hpp"
#include <algorithm>
#include <iostream>
#include <cstring>

bool Parser::load_file(const std::string &file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "[Parser] Could not open file: " << file_name << std::endl;
        return false;
    }

    std::string line;
    int original_line_number = 1;
    while (std::getline(file, line)) {
        lines.emplace_back(original_line_number++, line);
    }

    return true;
}

void Parser::preprocess() {
    std::vector<std::pair<int, std::string>> cleaned_lines;
    for (auto& [line_number, line] : lines) {
        std::string trimmed = trim(line);
        if (!is_comment_or_empty(trimmed)) {
            cleaned_lines.emplace_back(line_number, trimmed);
        }
    }
    lines = cleaned_lines;
}

void Parser::parse_lines() {
    for (const auto& [original_line_number, line] : lines) {
        std::vector<std::string> tokens = tokenize(line);
        if (tokens.empty()) continue;

        InstructionToken token;
        token.mnemonic = tokens[0];
        token.operands = std::vector<std::string>(tokens.begin() + 1, tokens.end());
        token.line_number = original_line_number;

        if (!validate_instruction(token)) {
            std::cerr << "-> Skipping invalid instruction at line " << token.line_number << std::endl;
            continue;
        }

        instructions.push_back(token);
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

    // Strip comments if present
    size_t comment_pos = line.find_first_of("#;");
    std::string line_no_comment = (comment_pos != std::string::npos)
                                    ? line.substr(0, comment_pos)
                                    : line;

    std::istringstream iss(line_no_comment);
    std::string token;

    while (std::getline(iss, token, ',')) {
        std::istringstream sub_iss(token);
        std::string sub_token;
        while (sub_iss >> sub_token) {
            // Handle memory operand like 0(x5)
            size_t paren_pos = sub_token.find('(');
            if (paren_pos != std::string::npos && sub_token.back() == ')') {
                std::string imm = sub_token.substr(0, paren_pos);
                std::string reg = sub_token.substr(paren_pos + 1, sub_token.length() - paren_pos - 2);
                if (!imm.empty()) tokens.push_back(imm);
                tokens.push_back(reg);
            } else {
                tokens.push_back(sub_token);
            }
        }
    }

    return tokens;
}


bool Parser::validate_instruction(const InstructionToken &token) {
    auto opcodeIt = isa::opcode_table.find(token.mnemonic);
    if (opcodeIt == isa::opcode_table.end()) {
        std::cerr << "[Error on line " << token.line_number << "] Unknown instruction: " << token.mnemonic << std::endl;
        return false;
    }

    const auto format = opcodeIt->second;
    size_t expected_num_of_operands = 0;

    if (format.type == isa::R) expected_num_of_operands = 3;
    if (format.type == isa::I) expected_num_of_operands = 3;
    if (format.type == isa::S) expected_num_of_operands = 2;
    if (format.type == isa::B) expected_num_of_operands = 3;
    if (format.type == isa::U) expected_num_of_operands = 2;
    if (format.type == isa::J) expected_num_of_operands = 2;

    if (token.operands.size() != expected_num_of_operands) {
        std::cerr << "[Error on line "
                    << token.line_number
                    << "] Invalid number of operands. Expected "
                    << expected_num_of_operands << ", got " << token.operands.size() << std::endl;
        return false;
    }


    std::string rd, rs1, rs2, imm;
    switch (format.type) {
        case isa::R:
            for (const auto& op : token.operands) {
                if (op.starts_with("x")) {
                    if (isa::regs_table.find(op) == isa::regs_table.end()) {
                        std::cerr << "[Error on line " << token.line_number << "] Invalid register name: " << op << std::endl;
                        return false;
                    }
                }
            }
            break;
        case isa::I:
            rd = token.operands[0];

            if (rd.starts_with("x")) {
                if (isa::regs_table.find(rd) == isa::regs_table.end()) {
                    std::cerr << "[Error on line " << token.line_number << "] Invalid register name: " << rd << std::endl;
                    return false;
                }
            } else {
                std::cerr << "[Error on line " << token.line_number << "] Invalid register name: " << rd << ". Register name should start with 'x'." << std::endl;
                return false;
            }

            if (isa::load_type_instructions_table.find(token.mnemonic) == isa::load_type_instructions_table.end()) {
                rs1 = token.operands[1];
                imm = token.operands[2];
            } else {
                imm = token.operands[1];
                rs1 = token.operands[2];
            }

            if (rs1.starts_with("x")) {
                if (isa::regs_table.find(rs1) == isa::regs_table.end()) {
                    std::cerr << "[Error on line " << token.line_number << "] Invalid register name: " << rs1 << std::endl;
                    return false;
                }
            }

            // check immediate
            for (const auto& c : imm) {
                if (!isdigit(c)) {
                    std::cerr << "[Error on line " << token.line_number << "] Immediate value is not a number: " << imm << std::endl;
                    break;
                }
            }
            break;
        case isa::S:
            break;
        case isa::B:
            break;
        case isa::U:
            break;
        case isa::J:
            break;
        defult:
            std::cerr << "[Error on line " << token.line_number << "] Unknown instruction: " << token.mnemonic << std::endl;
            return false;
    }

    return true;
}

std::optional<isa::InstructionFormat> Parser::get_opcode_info(const std::string &mnemonic) {
    auto it = isa::opcode_table.find(mnemonic);
    if (it == isa::opcode_table.end()) {
        return it->second;
    }
    return std::nullopt;
}
