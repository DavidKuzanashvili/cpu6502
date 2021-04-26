#include <gtest/gtest.h>

#include "cpu6502.h"

class INSJSRTest : public testing::Test {
public:
    CPU cpu;
    Mem mem;

    void SetUp() override
    {
        cpu.Reset(mem);
    }

    void TearDown() override
    {

    }
};

TEST_F(INSJSRTest, RunInlineProgram)
{
    mem[0xFFFC] = CPU::INS_JSR;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU::INS_LDA_IM;
    mem[0x4243] = 0x84;

    cpu.Execute(9, mem);

    EXPECT_EQ(cpu.A, 0x84);
}
