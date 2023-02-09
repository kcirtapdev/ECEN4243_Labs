/***************************************************************/
/*                                                             */
/*   RISC-V RV32 Instruction Level Simulator                   */
/*                                                             */
/*   ECEN 4243                                                 */
/*   Oklahoma State University                                 */
/*                                                             */
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "isa.h"

char *byte_to_binary(int x) {

  static char b[9];
  b[0] = '\0';

  int z;
  for (z = 128; z > 0; z >>= 1) {
    strcat(b, ((x & z) == z) ? "1" : "0");
  }

  return b;
}

char *byte_to_binary32(int x) {

  static char b[33];
  b[0] = '\0';

  unsigned int z;
  for (z = 2147483648; z > 0; z >>= 1) {
    strcat(b, ((x & z) == z) ? "1" : "0");
  }

  return b;
}

int bchar_to_int(char* rsa) {

  int i = 0;
  int result = 0;
  int t = 0;
  while(rsa[i] != '\0')i++;
  while(i>0)
    {
      --i;
      // printf("%d\n", (rsa[i]-'0')<<t);
      result += (rsa[i] - '0')<<t;
      t++;
    }
  return result;
}

int r_process(char* i_) {

  char d_opcode[8];
  d_opcode[0] = i_[31-6]; 
  d_opcode[1] = i_[31-5]; 
  d_opcode[2] = i_[31-4]; 
  d_opcode[3] = i_[31-3];
  d_opcode[4] = i_[31-2]; 
  d_opcode[5] = i_[31-1]; 
  d_opcode[6] = i_[31-0];
  d_opcode[7] = '\0';
  char rs1[6]; rs1[5] = '\0';		   
  char rs2[6]; rs2[5] = '\0';
  char rd[6]; rd[5] = '\0';
  char funct3[4]; funct3[3] = '\0';
  for(int i = 0; i < 5; i++) {
    rs1[i] = i_[31-19+i];
    rs2[i] = i_[31-24+i];            
    rd[i] = i_[31-11+i];
  }
  for(int i = 0; i < 3; i++) {
    funct3[i] = i_[31-14+i];
  }
  int Rs1 = bchar_to_int(rs1);
  int Rs2 = bchar_to_int(rs2);		   
  int Rd = bchar_to_int(rd);
  int Funct3 = bchar_to_int(funct3);
  printf ("Opcode = %s\n Rs1 = %d\n Rs2 = %d\n Rd = %d\n Funct3 = %d\n\n",
	  d_opcode, Rs1, Rs2, Rd, Funct3);
  printf("\n");

  /* Example - use and replicate */
  if(!strcmp(d_opcode,"0110011")) {
    printf("--- This is an ADD instruction. \n");
    ADD(Rd, Rs1, Rs2, Funct3);
    return 0;
  }

  /* Add other data instructions here */ 


  return 1;	
}

int i_process(char* i_) {

  char d_opcode[8];
  d_opcode[0] = i_[31-6]; 
  d_opcode[1] = i_[31-5]; 
  d_opcode[2] = i_[31-4]; 
  d_opcode[3] = i_[31-3];
  d_opcode[4] = i_[31-2]; 
  d_opcode[5] = i_[31-1]; 
  d_opcode[6] = i_[31-0]; 
  d_opcode[7] = '\0';
  char d_cond[5];
  d_cond[0] = i_[0]; 
  d_cond[1] = i_[1]; 
  d_cond[2] = i_[2]; 
  d_cond[3] = i_[3]; 
  d_cond[4] = '\0';
  char rs1[6]; rs1[5] = '\0';		   
  char rd[6]; rd[5] = '\0';
  char funct3[4]; funct3[3] = '\0';
  char imm[13]; imm[12] = '\0';
  for(int i = 0; i < 5; i++) {
    rs1[i] = i_[31-19+i];
    rd[i] = i_[31-11+i];
  }
  for(int i = 0; i < 12; i++) {
    imm[i] = i_[31-31+i];
  }
  for(int i = 0; i < 3; i++) {
    funct3[i] = i_[31-14+i];
  }
  char rn[5]; rn[4] = '\0';
  char rd[5]; rd[4] = '\0';
  char operand2[13]; operand2[12] = '\0';
  for(int i = 0; i < 4; i++) {
    rn[i] = i_[12+i];
    rd[i] = i_[16+i];
  }
  for(int i = 0; i < 12; i++) {
    operand2[i] = i_[20+i];
  }
  int Rs1 = bchar_to_int(rs1);
  int Rd = bchar_to_int(rd);
  int Funct3 = bchar_to_int(funct3);
  int Imm = bchar_to_int(imm);
  int Operand2 = bchar_to_int(operand2);
  int I = i_[6]-'0';
  int S = i_[11]-'0';
  int CC = bchar_to_int(d_cond);
  printf ("Opcode = %s\n Rs1 = %d\n Imm = %d\n Rd = %d\n Funct3 = %d\n\n",
	  d_opcode, Rs1, Imm, Rd, Funct3);
  printf("\n");

  
  // use for LSL and LSR case
  char shamt5[6]; char sh[3]; char rm[5];
  if(!I) {
    shamt5[5] = '\0'; sh[2] = '\0'; rm[4] = '\0';
    for(int i = 0; i < 6; i++) {
      if(i<2) 
        sh[i] = operand2[i+5];
      if(i<4)
        rm[i] = operand2[i+8];
      shamt5[i] = operand2[i];
    }
    printf("shamt5 = %s\n sh = %s\n Rm = %s\n", shamt5, sh, rm);
  }
int Rm = bchar_to_int(rm);
  /* Example - use and replicate */
  if(!strcmp(d_opcode,"0100")) {
    printf("--- This is an ADD instruction. \n");
    ADD(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }	

  /* Add other data instructions here */ 
  else if(!strcmp(d_opcode, "0000")) {
    printf("--- This is an AND instruction. \n");
    AND(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }

  else if(!strcmp(d_opcode, "0001")) {
    printf("--- This is an EOR instruction. \n");
    AND(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }

  else if(!strcmp(d_opcode, "0010")) {
    printf("--- This is a SUB instruction. \n");
    SUB(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }

  else if(!strcmp(d_opcode, "0011")) {
    printf("--- This is an RSB instruction. \n");
    RSB(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }

  else if(!strcmp(d_opcode, "0101")) {
    printf("--- This is an ADC instruction. \n");
    ADC(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }

  else if(!strcmp(d_opcode, "0110")) {
    printf("--- This is an SBC instruction. \n");
    SBC(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }

  else if(!strcmp(d_opcode, "0111")) {
    printf("--- This is an RSC instruction. \n");
    RSC(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }
  
  else if(!strcmp(d_opcode, "1000")) {
    printf("--- This is a TST instruction. \n");
    TST(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }

  else if(!strcmp(d_opcode, "1001")) {
    printf("--- This is a TEQ instruction. \n");
    TEQ(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }

  else if(!strcmp(d_opcode, "1010")) {
    printf("--- This is a CMP instruction. \n");
    CMP(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }

  else if(!strcmp(d_opcode, "1011")) {
    printf("--- This is a CMN instruction. \n");
    CMN(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }

  else if(!strcmp(d_opcode, "1100")) {
    printf("--- This is an ORR instruction. \n");
    ORR(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }
  
  // Takes care of LSL LSR ASR and ROR
  else if(!strcmp(d_opcode, "1101")) {
    printf("--- This is an MOV instruction. \n");
      MOV(Rd, Rn, Operand2, I, S, CC);
      return 0;
  }

  else if(!strcmp(d_opcode, "1110")) {
    printf("--- This is a BIC instruction. \n");
    BIC(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }

  else if(!strcmp(d_opcode, "1111")) {
    printf("--- This is an MVN instruction. \n");
    MVN(Rd, Rn, Operand2, I, S, CC);
    return 0;
  }

  return 1;	
}

int b_process(char* i_) {
  
  /* This function execute branch instruction */

  char d_opcode[8];
  d_opcode[0] = i_[31-6]; 
  d_opcode[1] = i_[31-5]; 
  d_opcode[2] = i_[31-4]; 
  d_opcode[3] = i_[31-3];
  d_opcode[4] = i_[31-2]; 
  d_opcode[5] = i_[31-1]; 
  d_opcode[6] = i_[31-0]; 
  d_opcode[7] = '\0';
  char rs1[6]; rs1[5] = '\0';
  char rs2[6]; rs2[5] = '\0';		     
  char funct3[4]; funct3[3] = '\0';
  char imm[13]; 
  for(int i = 0; i < 5; i++) {
    rs1[i] = i_[31-19+i];
    rs2[i] = i_[31-24+i];                
  }
  // Old-fashioned method but works :)
  imm[0] = i_[31-31]; 
  imm[1] = i_[31-7]; 
  imm[2] = i_[31-30]; 
  imm[3] = i_[31-29];
  imm[4] = i_[31-28]; 
  imm[5] = i_[31-27]; 
  imm[6] = i_[31-26];
  imm[7] = i_[31-25];
  imm[8] = i_[31-11];
  imm[9] = i_[31-10];
  imm[10] = i_[31-9];
  imm[11] = i_[31-8];
  imm[12] = '\0';  

  for(int i = 0; i < 3; i++) {
    funct3[i] = i_[31-14+i];
  }
  int Rs1 = bchar_to_int(rs1);
  int Rs2 = bchar_to_int(rs2);  
  int Funct3 = bchar_to_int(funct3);
  int Imm = bchar_to_int(imm);
  printf ("Opcode = %s\n Rs1 = %d\n Rs2 = %d\n Imm = %d\n Funct3 = %d\n\n",
	  d_opcode, Rs1, Rs2, Imm, Funct3);
  printf("\n");    

  /* Add branch instructions here */

  /* This is an Add Immediate Instruciton */
  if(!strcmp(d_opcode,"1100011")) {
    printf("--- This is an BNE instruction. \n");
    BNE(Rs1, Rs2, Imm, Funct3);
    return 0;
  }	    

  return 1;

}

int s_process(char* i_) {

  /* This function execute S type instructions */

  /* Add store instructions here */ 

  return 1;

}

int j_process(char* i_) {

  /* This function execute Jump instructions */

  /* Add jump instructions here */ 

  return 1;

}

int u_process(char* i_) {

  /* This function execute U type instructions */

  /* Add U instructions here */ 

  return 1;

}

int interruption_process(char* i_) {

  ECALL(i_);
  RUN_BIT = 0;
  return 0;

}

int decode_and_execute(char* i_) {

  /* 
     This function decode the instruction and update 
     CPU_State (NEXT_STATE)
  */

  if((i_[25] == '0') && (i_[26] == '0') &&
     (i_[27] == '1') && (i_[28] == '0') &&
     (i_[29] == '0') && (i_[30] == '1') && (i_[31] == '1')) {
    printf("- This is an Immediate Type Instruction. \n");
    i_process(i_);
  }
  if((i_[25] == '0') && (i_[26] == '1') &&
     (i_[27] == '1') && (i_[28] == '0') &&
     (i_[29] == '0') && (i_[30] == '1') && (i_[31] == '1')) {
    printf("- This is an R Type Instruction. \n");
    r_process(i_);
  }    
  if((i_[25] == '1') && (i_[26] == '1') &&
     (i_[27] == '0') && (i_[28] == '0') &&
     (i_[29] == '0') && (i_[30] == '1') && (i_[31] == '1')) {
    printf("- This is a B Type Instruction. \n");
    b_process(i_);
  }
  if((i_[25] == '0') && (i_[26] == '1') &&
     (i_[27] == '0') && (i_[28] == '0') &&
     (i_[29] == '0') && (i_[30] == '1') && (i_[31] == '1')) {
    printf("- This is a S Type Instruction. \n");
    s_process(i_);
  }  
  if((i_[25] == '1') && (i_[26] == '1') &&
     (i_[27] == '0') && (i_[28] == '1') &&
     (i_[29] == '1') && (i_[30] == '1') && (i_[31] == '1')) {
    printf("- This is a J Type Instruction. \n");
    j_process(i_);
  }
  if((i_[25] == '0') && (i_[26] == '0') &&
     (i_[27] == '1') && (i_[28] == '0') &&
     (i_[29] == '1') && (i_[30] == '1') && (i_[31] == '1')) {
    printf("- This is a U Type Instruction. \n");
    u_process(i_);
  }  
  if((i_[25] == '1') && (i_[26] == '1') &&
     (i_[27] == '1') && (i_[28] == '0') &&
     (i_[29] == '0') && (i_[30] == '1') && (i_[31] == '1')) {
    printf("- This is a Software Interruption Instruction. \n");
    interruption_process(i_);
  }

  return 0;

}

unsigned int OPCODE (unsigned int i_word) {

  return ((i_word<<27)>>27);

}

void process_instruction() {

  /* 
     execute one instruction here. You should use CURRENT_STATE and modify
     values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     access memory. 
  */   

  unsigned int inst_word = mem_read_32(CURRENT_STATE.PC);
  printf("The instruction is: %x \n", inst_word);
  printf("33222222222211111111110000000000\n");
  printf("10987654321098765432109876543210\n");
  printf("--------------------------------\n");
  printf("%s \n", byte_to_binary32(inst_word));
  printf("\n");
  decode_and_execute(byte_to_binary32(inst_word));

  NEXT_STATE.PC += 4;

}
