//
// Created by cherry on 5/4/25.
//

#ifndef FILE_PARSER_HPP
#define FILE_PARSER_HPP

#include <vector>
#include <fstream>
#include <sstream>
#include <optional>
#include "tables.hpp"

struct InstructionToken {
    std::string mnemonic;
    std::vector<std::string> operands;
    int line_number;
};

class Parser {
public:
    bool load_file(const std::string& file_name);
    void preprocess();
    void parse_lines();

    std::vector<InstructionToken> get_parsed_instructions() const;

private:
    std::vector<std::string> lines;
    std::vector<InstructionToken> instructions;

    std::string trim(const std::string& s);
    std::vector<std::string> tokenize(const std::string& line);
    bool is_comment_or_empty(const std::string& line);
    bool validate_instruction(const InstructionToken& token);
    std::optional<isa::InstructionFormat> get_opcode_info(const std::string& mnemonic);
};

#endif //FILE_PARSER_HPP
