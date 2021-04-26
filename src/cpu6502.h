#ifndef CPU6502_CPU6502_H
#define CPU6502_CPU6502_H
// http://obelisk.me.uk/6502

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;
using s32 = signed int;

struct Mem
{
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    void Initialize();
    Byte operator[](u32 address) const; // Read 1 byte
    Byte& operator[](u32 address); // Write 1 byte
    void WriteWord(Word value, u32 address); // Write 2 byte
};

struct CPU
{
    Word PC;        // Program Counter
    Word SP;        // Stack Pointer

    Byte A, X, Y;  // Registers

    Byte C : 1; // status flag
    Byte Z : 1; // status flag
    Byte I : 1; // status flag
    Byte D : 1; // status flag
    Byte B : 1; // status flag
    Byte V : 1; // status flag
    Byte N : 1; // status flag

    // Op-Codes
    static constexpr Byte INS_LDA_IM = 0xA9;
    static constexpr Byte INS_LDA_ZP = 0xA5;
    static constexpr Byte INS_LDA_ZPX = 0xB5;
    static constexpr Byte INS_JSR = 0x20;

    void Reset(Mem& memory);
    Byte FetchByte(s32& cycles, Mem& memory);
    Byte ReadByte(s32& cycles, Byte address, Mem& memory);
    Word FetchWord(s32& cycles, Mem& memory);
    void LDASetStatus();
    s32 Execute(s32 cycles, Mem& memory);
};

#endif //CPU6502_CPU6502_H
