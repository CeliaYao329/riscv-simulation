#include "Simulation.h"
using namespace std;

extern void read_elf();
extern unsigned int cadr;
extern unsigned int csize;
extern unsigned int vadr;
extern unsigned long long gp;
extern unsigned int madr;
extern unsigned int endPC;
extern unsigned int entry;
extern FILE *file;


//ָ��������
long long inst_num = 0;

//ϵͳ�����˳�ָʾ
int exit_flag = 0;

//���ش����
//��ʼ��PC
void load_memory()
{
	fseek(file, cadr, SEEK_SET);
	fread(&memory[vadr >> 2], 1, csize, file);

	vadr = vadr >> 2;
	csize = csize >> 2;
	fclose(file);
}

int main()
{
	//����elf�ļ�
	read_elf();

	//�����ڴ�
	load_memory();

	//������ڵ�ַ
	PC = entry >> 2;

	//����ȫ�����ݶε�ַ�Ĵ���
	reg[3] = gp;

	reg[2] = MAX / 2;//ջ��ַ ��sp�Ĵ�����

	simulate();

	cout << "simulate over!" << endl;

	return 0;
}

void simulate()
{
	//����PC������
	int end = (int)endPC / 4 - 1;
	while (PC != end)
	{
		//����
		IF();
		ID();
		EX();
		MEM();
		WB();

		//�����м�Ĵ���
		IF_ID = IF_ID_old;
		ID_EX = ID_EX_old;
		EX_MEM = EX_MEM_old;
		MEM_WB = MEM_WB_old;

		if (exit_flag == 1)
			break;

		reg[0] = 0;//һֱΪ��

	}
}


//ȡָ��
void IF()
{
	//write IF_ID_old
	IF_ID_old.inst = memory[PC];
	PC = PC + 1;
	IF_ID_old.PC = PC;
}

//����
void ID()
{
	//Read IF_ID
	unsigned int inst = IF_ID.inst;
	int EXTop = 0;
	unsigned int EXTsrc = 0;

	char RegDst, ALUop, ALUSrc;
	char Branch, MemRead, MemWrite;
	char RegWrite, MemtoReg;

	OP = getbit(inst, 0, 6);
	fuc3 = getbit(inst, 12, 14);
	fuc7 = getbit(inst, 25, 31);
	shamt = getbit(inst, 20, 24);//same direction with rs2
	rs1 = getbit(inst, 15, 19);
	rs2 = getbit(inst, 20, 24);
	rd = getbit(inst, 7, 11);

	//immediate numbers are in different kinds and be put in different areas
	//don't know how to decode the imm number
	imm_I = getbit(inst, 20, 31);//I
	imm_S = getbit(inst, 7, 11) + getbit(inst, 25, 31)*(1 << 5);//S
	imm_SB = (1 << 1)*(getbit(inst, 8, 11) + getbit(inst, 25, 30)*(1 << 5) + getbit(inst, 7, 7)*(1 << 11) + getbit(inst, 31, 31)*(1 << 12));//SB
	imm_U = getbit(inst, 12, 31);//U
	imm_UJ= (1 << 1)*(getbit(inst, 21, 30) + getbit(inst, 20, 20)*(1 << 11) + getbit(inst, 12, 19)*(1 << 12) + getbit(inst, 31, 31)*(1 << 20));//UJ

	if (OP == OP_R)
	{
		if (fuc3 == F3_ADD&&fuc7 == F7_ADD)
		{
			EXTop = 0;
			RegDst = 0;
			ALUop = 0;
			ALUSrc = 0;
			Branch = 0;
			MemRead = 0;
			MemWrite = 0;
			RegWrite = 0;
			MemtoReg = 0;
		}
		else 
		{

		}
	}
	else if (OP == OP_I)
	{
		if (fuc3 == F3_ADDI)
		{

		}
		else
		{

		}
	}
	else if (OP == OP_SW)
	{
		if (fuc3 == F3_SB)
		{

		}
		else
		{

		}
	}
	else if (OP == OP_LW)
	{
		if (fuc3 == F3_LB)
		{

		}
		else
		{

		}
	}
	else if (OP == OP_BEQ)
	{
		if (fuc3 == F3_BEQ)
		{

		}
		else
		{

		}
	}
	else if (OP == OP_JAL)
	{

	}
	else
	{

	}

	//write ID_EX_old
	ID_EX_old.Rd = rd;
	ID_EX_old.Rt = rt;
	ID_EX_old.Imm = ext_signed(EXTsrc, EXTop);
	//...

	ID_EX_old.Ctrl_EX_ALUOp = ALUop;
	//....

}

//ִ��
void EX()
{
	//read ID_EX
	int temp_PC = ID_EX.PC;
	char RegDst = ID_EX.Ctrl_EX_RegDst;
	char ALUOp = ID_EX.Ctrl_EX_ALUOp;

	//Branch PC calulate
	//...

	//choose ALU input number
	//...

	//alu calculate
	int Zero;
	REG ALUout;
	switch (ALUOp) {
	default:;
	}

	//choose reg dst address
	int Reg_Dst;
	if (RegDst)
	{

	}
	else
	{

	}

	//write EX_MEM_old
	EX_MEM_old.ALU_out = ALUout;
	EX_MEM_old.PC = temp_PC;
	//.....
}

//���ʴ洢��
void MEM()
{
	//read EX_MEM

	//complete Branch instruction PC change

	//read / write memory

	//write MEM_WB_old
}


//д��
void WB()
{
	//read MEM_WB

	//write reg
}