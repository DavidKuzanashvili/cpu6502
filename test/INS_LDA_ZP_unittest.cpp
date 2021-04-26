#include <gtest/gtest.h>

#include "cpu6502.h"

class INSLDAZPTest : public testing::Test {
public:
    CPU cpu{};
    Mem mem{};

    void SetUp() override
    {
        cpu.Reset(mem);
    }

    void TearDown() override
    {

    }
};

TEST_F(INSLDAZPTest, LDAZPCanLoadValueIntoARegister)
{
    // Arrange
    mem[0xFFFC] = CPU::INS_LDA_ZP;
    mem[0xFFFD] = 0x37;
    mem[0x37] = 0x81;

    // Act
    CPU cpuCopy = cpu;
    s32 cycles = cpu.Execute(3, mem);

    // Assert
    EXPECT_EQ(cycles, 3);
    EXPECT_EQ(cpu.A, 0x81);
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);
    EXPECT_EQ(cpu.C, cpuCopy.C);
    EXPECT_EQ(cpu.I, cpuCopy.I);
    EXPECT_EQ(cpu.D, cpuCopy.D);
    EXPECT_EQ(cpu.B, cpuCopy.B);
    EXPECT_EQ(cpu.V, cpuCopy.V);
}

TEST_F(INSLDAZPTest, LDAZPXCanLoadValueIntoARegister)
{
    // Arrange
    cpu.X = 0x5;

    mem[0xFFFC] = CPU::INS_LDA_ZPX;
    mem[0xFFFD] = 0x42;
    mem[0x47] = 0x81;

    // Act
    CPU cpuCopy = cpu;
    s32 cycles = cpu.Execute(4, mem);

    // Assert
    EXPECT_EQ(cycles, 4);
    EXPECT_EQ(cpu.A, 0x81);
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);
    EXPECT_EQ(cpu.C, cpuCopy.C);
    EXPECT_EQ(cpu.I, cpuCopy.I);
    EXPECT_EQ(cpu.D, cpuCopy.D);
    EXPECT_EQ(cpu.B, cpuCopy.B);
    EXPECT_EQ(cpu.V, cpuCopy.V);
}

TEST_F(INSLDAZPTest, LDAZPXCanLoadValueIntoARegisterWhenItWraps)
{
    // Arrange
    cpu.X = 0xFF;

    mem[0xFFFC] = CPU::INS_LDA_ZPX;
    mem[0xFFFD] = 0x80;
    mem[0x07F] = 0x81;

    // Act
    CPU cpuCopy = cpu;
    s32 cycles = cpu.Execute(4, mem);

    // Assert
    EXPECT_EQ(cycles, 4);
    EXPECT_EQ(cpu.A, 0x81);
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);
    EXPECT_EQ(cpu.C, cpuCopy.C);
    EXPECT_EQ(cpu.I, cpuCopy.I);
    EXPECT_EQ(cpu.D, cpuCopy.D);
    EXPECT_EQ(cpu.B, cpuCopy.B);
    EXPECT_EQ(cpu.V, cpuCopy.V);
}
