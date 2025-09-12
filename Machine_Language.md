# Basic Programming Language and OS API - Project Documentation

## Overview

This project implements a custom low-level programming language and an operating system API designed for a virtual machine environment. The language operates with a set of 15 registers (R0-R14) that act as pointers to virtual RAM addresses. The memory is segmented for integers, characters, and strings with predefined address ranges.

## Architecture and Design

- Registers are pointer-based and must reference valid memory locations before use; otherwise, the program will crash.
- Memory ranges:
  - Integers and characters: addresses 0-99
  - Strings: addresses 0-999
- Memory and registers operate under strict pointer arithmetic and manual data manipulation.

## Instruction Set

| Instruction | Description                                                   | Example                                   |
|-------------|---------------------------------------------------------------|-------------------------------------------|
| `ASSN Rn V`   | Store value `V` directly in register `Rn`                    | `ASSN 1 100` ; sets reg[1] to 100         |
| `MOVE Rn A T` | Set register `Rn` to point to memory address `A` of type `T` | `MOVE 9 99 I` ; reg[9] points to int at 99|
| `ASSV Rn Rm`  | Copy value from register `Rm` to `Rn`                        | `ASSV 3 4`                                |
| `COMP Rn Rm Rz` | `Rz = (Rn < Rm) ? 1 : 0`                                    |                                           |
| `EQAL Pn Pm Pz` | `Pz = (Pn == Pm) ? 1 : 0`                                    |                                           |
| `NEQL Pn Pm Pz` | `Pz = (Pn != Pm) ? 1 : 0`                                    |                                           |
| `CJMP Pn L`   | If reg[Pn] == 1, jump to line `L`                             |                                           |
| `JUMP L`      | Unconditional jump to line `L`                                |                                           |
| `HALT`        | Terminate program and return to OS                            |                                           |
| `PUTC Pn`     | Output character in reg[Pn]                                   |                                           |
| `PUTS Pn Pm`  | Output string starting at address reg[Pn] length reg[Pm]     |                                           |
| `PUTI Pn`  | printf("%d", reg[Pn] )     |                                           |
| `PUSH Pn Pm Px`  | printf("%d", reg[Pn] )     |                                           |
| `ADDN Pn Pm Pz` | reg[Pz] = reg[Pn] + reg[Pm]                                 |                                           |
| `ADDO Pn` | reg[Pn] = reg[Pn]+1 ;                                 |                                           |
| `MULT Pn Pm Pz` | reg[Pz] = reg[Pn] * reg[Pm]                                 |                                           |
| `DIVI Pn Pm Pz` | reg[Pz] = reg[Pn] / reg[Pm]                                 |                                           |
| `MODE Pn Pm Pz` | reg[Pz] = reg[Pn] % reg[Pm]                                 |                                           |
| `GETC Pn`     | Read a character into reg[Pn]                                 |                                           |
| `GETI Pn`     | Read a single digit number into reg[Pn]                       |                                           |
| `GETS Pn Pm`     | put str start from Pn and save how many chars got to Pm .                     |                                           |
| `PRIT str`    | Print a literal string during program load                    |                                           |
| `ANDC Pn Pm Pz`				|   reg[Pz] = (reg[Pn] && reg[Pm]) |                                           |
| `ORLC Pn Pm Pz`				|   reg [Pz] = (reg[Pn] || reg[Pm]) |                                           |
| `NOTC Pn` 				|   reg[Pn] = !reg[Pn] |                                           |


## OS API Functions

- `TIME Pn` : Stores current date/time string in reg[Pn].
- `FGET R1 R2` : R2 = fgetc(R2);
- `OPEN R1 R2 R3` : Opens a file with path in reg[R1], mode in R2, stores file pointer in R3.
- `CLOS R1` : Closes the file pointed by reg[R1].
- `READ R1` : Reads and prints file content from file pointer in reg[R1].
- `WRIT R1 R2` : Writes string from reg[R1] to file pointer in reg[R2].
- `APND R1 R2` : Appends string from reg[R1] to file pointer in reg[R2].
- `MAKE R1` : Creates a file with name from reg[R1].
- `KILL R1` : Deletes the file named in reg[R1].
- `RUNF R1` : Loads and runs a program pointed by reg[R1].
- `CLER` : clear screen
- `CTCT color` : Sets terminal color (`R`, `G`, `B`, `Y`, `0`->reset).

## Example: Reading a Multi-digit Number

```
MOVE 9 99 I 
ASSN 9 0    
MOVE 8 98 I  
MOVE 7 97 C   
ASSN 7 36     
MOVE 6 96 I      
MOVE 5 95 I
ASSN 5 10
GETI 8  
EQAL 8 7 6    
CJMP 6 15  
MULT 9 5 9      
ADDN 9 8 9 
JUMP 9
HALT
```





## Usage Notes

- Always initialize registers by moving them to valid memory addresses before usage.
- Control flow relies heavily on conditional and unconditional jumps (`CJMP`, `JUMP`).
- Terminal color changes must be reset manually after use.
- Program termination returns control to the host OS.

---
