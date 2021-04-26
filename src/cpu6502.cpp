#include <stdio.h>
#include "cpu6502.h"

// Start - Memory impl
void Mem::Initialize()
{
    for (u32 i = 0; i < MAX_MEM; ++i)
    {
        Data[i] = 0;
    }
}

Byte Mem::operator[](u32 address) const
{
    return Data[address];
}

Byte& Mem::operator[](u32 address) {
    return Data[address];
}

void Mem::WriteWord(Word value, u32 address)
{
    Data[address] = (value & 0xFF);
    Data[address + 1] = (value >> 8);
}

// End - Memory impl


// Start - CPU impl
void CPU::Reset(Mem& memory)
{
    PC = 0xFFFC;
    SP = 0x0100;

    A = X = Y = 0;
    C = Z = I = D = B = V = N = 0;
    memory.Initialize();
}

Byte CPU::FetchByte(s32& cycles, Mem& memory)
{
    Byte data = memory[PC];
    PC++;
    cycles--;
    return data;
}

Byte CPU::ReadByte(s32& cycles, Byte address, Mem& memory)
{
    Byte data = memory[address];
    cycles--;
    return data;
}

Word CPU::FetchWord(s32& cycles, Mem& memory)
{
    /*
        6502 is little endian,
        that means fist byte is
        the least significant
    */
    Word data = memory[PC];
    PC++;

    data |= (memory[PC] << 8);
    PC++;

    cycles -= 2;
    return data;
}

void CPU::LDASetStatus()
{
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

s32 CPU::Execute(s32 cycles, Mem& memory)
{
    const s32 cyclesRequested = cycles;
    while (cycles > 0)
    {
        Byte instruction = FetchByte(cycles, memory);

        switch (instruction)
        {
            case INS_LDA_IM:
            {
                Byte value = FetchByte(cycles, memory);
                A = value;
                LDASetStatus();
            }
                break;
            case INS_LDA_ZP:
            {
                Byte zeroPageAddress = FetchByte(cycles, memory);
                A = ReadByte(cycles, zeroPageAddress, memory);
                LDASetStatus();
            }
                break;
            case INS_LDA_ZPX:
            {
                Byte zeroPageAddress = FetchByte(cycles, memory);
                zeroPageAddress += X;
                cycles--;
                A = ReadByte(cycles, zeroPageAddress, memory);
                LDASetStatus();
            }
                break;
            case INS_JSR:
            {
                Word subroutineAddr = FetchWord(cycles, memory);
                memory.WriteWord(PC - 1, SP);
                SP++;
                cycles -= 2;
                PC += subroutineAddr;
                cycles--;
            }
                break;
            default:
            {
                printf("Instruction %d not handled", instruction);
            }
                break;
        }
    }

    return cyclesRequested - cycles;
}
// End - CPU impl
