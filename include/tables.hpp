//
// Created by cherry on 5/2/25.
//

#ifndef TABLES_HPP
#define TABLES_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

namespace isa {
    enum InstructionType {
        R, I, S, B, U, J,
    };

    struct InstructionFormat {
        uint8_t opcode;
        int16_t funct3;         // -1 if unused
        int16_t funct7;         // -1 if unused
        InstructionType type;       // R, I, S, B, U, J
    };

    struct RegisterFormat {
        std::string alias;
        int index;
    };

    inline std::unordered_map<std::string, InstructionFormat> opcode_table = {
        // R type instructions
        {"add", {0b0110011, 0b000, 0b0000000, R}},
        {"sub", {0b0110011, 0b000, 0b0100000, R}},
        {"sll", {0b0110011, 0b001, 0b0000000, R}},
        {"slt", {0b0110011, 0b010, 0b0000000, R}},
        {"sltu", {0b0110011, 0b011, 0b0000000, R}},
        {"xor", {0b0110011, 0b100, 0b0000000, R}},
        {"srl", {0b0110011, 0b101, 0b0000000, R}},
        {"sra", {0b0110011, 0b101, 0b0100000, R}},
        {"or", {0b0110011, 0b110, 0b0000000, R}},
        {"addw", {0b0111011, 0b000, 0b0000000, R}},
        {"subw", {0b0111011, 0b000, 0b0100000, R}},
        {"sllw", {0b0111011, 0b001, 0b0000000, R}},
        {"srlw", {0b0111011, 0b101, 0b0000000, R}},
        {"sraw", {0b0111011, 0b101, 0b0100000, R}},

        // I type instructions
        {"lb", {0b0000011, 0b000, -1, I}},
        {"lh", {0b0000011, 0b001, -1, I}},
        {"lw", {0b0000011, 0b010, -1, I}},
        {"ld", {0b0000011, 0b011, -1, I}},
        {"lbu", {0b0000011, 0b100, -1, I}},
        {"lhu", {0b0000011, 0b101, -1, I}},
        {"lwu", {0b0000011, 0b110, -1, I}},
        {"fence", {0b0001111, 0b000, -1, I}},
        {"fence.i", {0b0001111, 0b001, -1, I}},
        {"addi", {0b0010011, 0b000, -1, I}},
        {"slli", {0b0010011, 0b001, 0b0000000, I}},
        {"slti", {0b0010011, 0b010, -1, I}},
        {"sltiu", {0b0010011, 0b011, -1, I}},
        {"xori", {0b0010011, 0b100, -1, I}},
        {"srli", {0b0010011, 0b101, 0b0000000, I}},
        {"srai", {0b0010011, 0b101, 0b0100000, I}},
        {"ori", {0b0010011, 0b110, -1, I}},
        {"andi", {0b0010011, 0b111, -1, I}},
        {"addiw", {0b0011011, 0b000, -1, I}},
        {"slliw", {0b0011011, 0b001, 0b0000000, I}},
        {"srliw", {0b0011011, 0b101, 0b0000000, I}},
        {"sraiw", {0b0011011, 0b111, 0b0100000, I}},
        {"jalr", {0b1100111, 0b000, -1, I}},
        {"ecall", {0b1110011, 0b000, 0b0000000, I}},
        {"ebreak", {0b0010011, 0b000, 0b0100000, I}},
        {"CSRRW", {0b0010011, 0b001, -1, I}},
        {"CSRRS", {0b0010011, 0b010, -1, I}},
        {"CSRRC", {0b0010011, 0b011, -1, I}},
        {"CSRRWI", {0b0010011, 0b101, -1, I}},
        {"CSRRSI", {0b0010011, 0b110, -1, I}},
        {"CSRRCI", {0b0010011, 0b111, -1, I}},

        // S type instructions
        {"sb", {0b0100011, 0b000, -1, S}},
        {"sh", {0b0100011, 0b001, -1, S}},
        {"sw", {0b0100011, 0b010, -1, S}},
        {"sd", {0b0100011, 0b011, -1, S}},

        // B type instructions
        {"beq", {0b1100011, 0b000, -1, B}},
        {"bne", {0b1100011, 0b001, -1, B}},
        {"blt", {0b1100011, 0b100, -1, B}},
        {"bge", {0b1100011, 0b101, -1, B}},
        {"bltu", {0b1100011, 0b110, -1, B}},
        {"bgeu", {0b1100011, 0b111, -1, B}},

        // U type instructions
        {"auipc", {0b0010111, -1, -1, U}},
        {"lui", {0b0110111, -1, -1, U}},

        // J type instruction (he's just special)
        {"jal", {0b1101111, -1, -1, J}}
    };

    inline std::unordered_map<std::string, RegisterFormat> regs_table = {
        {"x0", {"zero", 0}}, {"x1", {"ra", 1}}, {"x2", {"sp", 2}}, {"x3", {"gp", 3}}, {"x4", {"tp", 4}},
        {"x5", {"t0", 5}}, {"x6", {"t1", 6}}, {"x7", {"t2", 7}}, {"x8", {"s0/fp", 8}}, {"x9", {"s1", 9}},
        {"x10", {"a0", 10}}, {"x11", {"a1", 11}}, {"x12", {"a2", 12}}, {"x13", {"a3", 13}}, {"x14", {"a4", 14}},
        {"x15", {"a5", 15}}, {"x16", {"a6", 16}}, {"x17", {"a7", 17}}, {"x18", {"s2", 18}}, {"x19", {"s3", 19}},
        {"x20", {"s4", 20}}, {"x21", {"s5", 21}}, {"x22", {"s6", 22}}, {"x23", {"s7", 23}}, {"x24", {"s8", 24}},
        {"x25", {"s9", 25}}, {"x26", {"s10", 26}}, {"x27", {"s11", 27}}, {"x28", {"t3", 28}}, {"x29", {"t4", 29}},
        {"x30", {"t5", 30}}, {"x31", {"t6", 31}}

        // TODO: Add FP regs f0-f31 in future
    };

    inline std::unordered_map<std::string, std::string> load_type_instructions_table = {
        {"lb", "load"}, {"lh", "load"}, {"lw", "load"}, {"ld", "load"}, // load I-type instructions
    };
}

#endif //TABLES_HPP
