/***************************************************************/
/*                                                             */
/*   RISC-V RV32 Instruction Level Simulator                   */
/*                                                             */
/*   ECEN 4243                                                 */
/*   Oklahoma State University                                 */
/*                                                             */
/***************************************************************/

#ifndef _SIM_ISA_H_
#define _SIM_ISA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

// OLD_SIGNEXT is flawed. It cannot sign extend a negative number into 
// a positive number even when "sb" falls on a zero.
//
// This is fixed with the DROP_ZEROS helper macro.

// Helper macros:
#define OLD_SIGNEXT(v, sb) ((v) | (((v) & (1 << (sb))) ? ~((1 << (sb))-1) : 0))
#define DROP_ZEROS(v, sb) (v << (32-sb)) >> (32-sb)

// New macros: value (v); sign bit (sb)
#define SIGNEXT(v, sb) OLD_SIGNEXT(DROP_ZEROS(v, sb), sb)
#define ZEROEXT(v, sb) (~0U >> (32-sb)) & v

// R Instructions
int ADD (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SUB (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] - CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SLL (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] << CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SLT (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  int cRs1 = CURRENT_STATE.REGS[Rs1];
  int cRs2 = CURRENT_STATE.REGS[Rs2];
  cur = (cRs1 < cRs2);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SLTU (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  unsigned int cRs1u = CURRENT_STATE.REGS[Rs1]; // "Current Rs1 Unsigned"
  unsigned int cRs2u = CURRENT_STATE.REGS[Rs2]; // "Current Rs2 Unsigned"
  cur = cRs1u < cRs2u;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int XOR (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] ^ CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SRL (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SRA (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  int cRs1 = CURRENT_STATE.REGS[Rs1];
  int cRs2 = CURRENT_STATE.REGS[Rs2];
  // Shift right arithmetic, shift right then sign extend with bitmask
  cur = (cRs1 < 0) ? ((cRs1 >> cRs2) | ~(~0U >> cRs2)) : (cRs1 >> cRs2);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int OR (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  cur = (CURRENT_STATE.REGS[Rs1] | CURRENT_STATE.REGS[Rs2]);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int AND (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  cur = (CURRENT_STATE.REGS[Rs1] & CURRENT_STATE.REGS[Rs2]);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}



// I Instructions
int ADDI (int Rd, int Rs1, int Imm, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,11);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int LB (int Rd, int Rs1, int Imm, int Funct3) {
  int cur = 0;
  int valInMem = mem_read_32(CURRENT_STATE.REGS[Rs1] + Imm);
  printf("Address: %d\n", (CURRENT_STATE.REGS[Rs1] + Imm));
  printf("valInMem: %d\n", valInMem);
  cur = SIGNEXT(valInMem, 7);
  printf("cur: %d\n", cur);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int LH (int Rd, int Rs1, int Funct3) {
  int cur = 0;
  int cRs1 = CURRENT_STATE.REGS[Rs1];
  cur = SIGNEXT(cRs1, 16);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int LW (int Rd, int Rs1, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int LBU (int Rd, int Rs1, int Funct3) {
  int cur = 0;
  int cRs1 = CURRENT_STATE.REGS[Rs1];
  cur = ZEROEXT(cRs1, 8);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int LHU (int Rd, int Rs1, int Funct3) {
  int cur = 0;
  int cRs1 = CURRENT_STATE.REGS[Rs1];
  cur = ZEROEXT(cRs1, 16);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SLLI (int Rd, int Rs1, int Zimm, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] << Zimm;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SLTI (int Rd, int Rs1, int Imm, int Funct3) {
  int cur = 0;
  cur = (CURRENT_STATE.REGS[Rs1] < Imm);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SLTIU (int Rd, int Rs1, int Imm, int Funct3) {
  int cur = 0;
  unsigned int cRs1u = CURRENT_STATE.REGS[Rs1]; // "Current Rs1 Unsigned"
  unsigned int Immu = Imm; // "Imm Unsigned"
  cur = cRs1u < Immu;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int XORI (int Rd, int Rs1, int Imm, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] ^ Imm;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SRLI (int Rd, int Rs1, int Imm, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> Imm;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SRAI (int Rd, int Rs1, int Imm, int Funct3) {
  int cur = 0;
  int cRs1 = CURRENT_STATE.REGS[Rs1];
  // Shift right arithmetic, shift right then sign extend with bitmask
  cur = (cRs1 < 0) ? ((cRs1 >> Imm) | ~(~0U >> Imm)) : (cRs1 >> Imm);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int ORI (int Rd, int Rs1, int Imm, int Funct3) {
  int cur = 0;
  cur = (CURRENT_STATE.REGS[Rs1] | Imm);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int ANDI (int Rd, int Rs1, int Imm, int Funct3) {
  int cur = 0;
  cur = (CURRENT_STATE.REGS[Rs1] & Imm);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}



// U Instructions
int AUIPC (int Rd, int Upimm) {
  int cur = 0;
  cur = Upimm << 12;
  NEXT_STATE.REGS[Rd] = (CURRENT_STATE.PC) + cur; // TODO: Should this be (PC - 4)?
  return 0;
}

int LUI (int Rd, int Upimm) {
  int cur = 0;
  cur = Upimm << 12;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}



// S Instructions
// ...



// B Instructions
int BNE (int Rs1, int Rs2, int Imm, int Funct3) {
  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] != CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;
}



// S Instruction
int SB (char* i_);
int SH (char* i_);
int SW (char* i_);

// B instructions
int BEQ (char* i_);
int BLT (char* i_);
int BGE (char* i_);
int BLTU (char* i_);
int BGEU (char* i_);

// I instruction
int JALR (char* i_);

// J instruction
int JAL (char* i_);

int ECALL (char* i_){return 0;}

#endif
