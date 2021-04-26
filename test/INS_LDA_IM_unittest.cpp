#include <gtest/gtest.h>

#include "cpu6502.h"

class INSLDAIMTest : public testing::Test {
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

TEST_F(INSLDAIMTest, LDAImmediateCanLoadValueIntoARegister)
{
    // Arrange
    mem[0xFFFC] = CPU::INS_LDA_IM;
    mem[0xFFFD] = 0x84;

    // Act
    CPU cpuCopy = cpu;
    s32 cycles = cpu.Execute(2, mem);

    // Assert
    EXPECT_EQ(cycles, 2);
    EXPECT_EQ(cpu.A, 0x84);
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);
    EXPECT_EQ(cpu.C, cpuCopy.C);
    EXPECT_EQ(cpu.I, cpuCopy.I);
    EXPECT_EQ(cpu.D, cpuCopy.D);
    EXPECT_EQ(cpu.B, cpuCopy.B);
    EXPECT_EQ(cpu.V, cpuCopy.V);
}
