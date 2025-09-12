# Sky Machine

![Sky Machine Logo](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTXaj0Y_9zRW2zJiyFo64VrtQihzsteh6c8fOv3r21a961fK3Oo6rqX5Vw&s=10)

---

## Bubble Operating System and Sky Machine Virtual CPU

Sky Machine is a university-level educational project simulating a virtual machine environment on Windows.  
This virtual machine runs a minimalist Operating System called **Bubble**, implemented using a unique assembly-like programming language designed specifically for this platform.

---

## Project Overview

- The virtual machine architecture simulates memory, registers, hard disk, and CPU operation logic fully implemented in C.  
- It supports a custom assembly-like language with concise syntax for programming the virtual CPU.  
- This is a single-threaded virtual CPU capable of executing only one program at a time.

---

## How It Works

1. Simulates virtual hardware components including registers and memory heaps.  
2. Uses a unique low-level programming language with instructions similar to assembly for system and user-level programming.  
3. Provides facilities for arithmetic, logical, control flow, I/O, and file operations in the custom language.  
4. Maintains separate memory spaces for OS (Bubble) and user programs, switching execution context accordingly.

---

## Instruction Set Overview

| Instruction | Description                                                                            | Example                  |
|-------------|----------------------------------------------------------------------------------------|--------------------------|
| ASSN Rn Value  | Assigns a literal value to register \( R_n \).                                         | `ASSN 1 100`             |
| MOVE Rn Addr Type | Moves data of specified type from virtual RAM address \( Addr \) to register \( R_n \).      | `MOVE 2 15 I`            |
| ASSV Rn Rm    | Copies the contents from register \( R_m \) to register \( R_n \).                      | `ASSV 1 2`               |
| COMP Rn Rm Rz | Compares if \( R_n < R_m \), stores 1 in \( R_z \) if true, else 0.                     | `COMP 1 2 3`             |
| EQAL Pn Pm Pz | Checks equality of registers \( P_n \) and \( P_m \), stores result in \( P_z \).        | `EQAL 1 2 3`             |
| NEQL Pn Pm Pz | Checks inequality of registers \( P_n \) and \( P_m \), stores result in \( P_z \).      | `NEQL 1 2 3`             |
| CJMP Pn Line  | Conditional jump to line number \( Line \) if \( P_n \) is 1 (true).                     | `CJMP 0 100`             |
| JUMP Line     | Unconditional jump to line \( Line \).                                                  | `JUMP 50`                |
| HALT          | Terminates the running program, control returns to the OS.                             | `HALT`                   |
| PUTC Pn       | Outputs the character stored in register \( P_n \).                                   | `PUTC 3`                 |
| PUTS Pn Pm    | Outputs the string starting at address pointed by \( P_n \) printing \( P_m \) chars.  | `PUTS 4 5`               |
| PUTI Pn       | Outputs the integer value stored in register \( P_n \).                               | `PUTI 6`                 |
| PUSH Pn Pm Px | Stores the \( P_m \)-th index of string starting at \( P_n \) into register \( P_x \).  | `PUSH 1 2 3`             |
| ADDN Pn Pm Pz | Adds values from \( P_n \) and \( P_m \), stores result in \( P_z \).                   | `ADDN 1 2 3`             |
| ADDO Pn       | Increments the value in register \( P_n \) by 1.                                      | `ADDO 1`                 |
| MULT Pn Pm Pz | Multiplies values of \( P_n \) and \( P_m \), stores in \( P_z \).                     | `MULT 1 2 3`             |
| DIVI Pn Pm Pz | Divides \( P_n \) by \( P_m \), stores quotient in \( P_z \).                          | `DIVI 1 2 3`             |
| MODE Pn Pm Pz | Calculates \( P_n \mod P_m \), stores remainder in \( P_z \).                          | `MODE 1 2 3`             |
| GETC Pn       | Reads a single character input to register \( P_n \).                                 | `GETC 1`                 |
| GETI Pn       | Reads a single digit (0-9) input, stores its integer value in \( P_n \).               | `GETI 1`                 |
| GETS Pn Pm    | Reads a string starting at address pointed by \( P_n \), stores length in \( P_m \).   | `GETS 1 2`               |
| ANDC Pn Pm Pz | Logical AND of registers \( P_n \) and \( P_m \), stores in \( P_z \).                 | `ANDC 1 2 3`             |
| ORLC Pn Pm Pz | Logical OR of registers \( P_n \) and \( P_m \), stores in \( P_z \).                  | `ORLC 1 2 3`             |
| NOTC Pn       | Logical NOT of register \( P_n \).                                                    | `NOTC 1`                 |

---

## Advantages

- **Educational Value:** Fully coded in C, providing insight into low-level system programming and CPU simulation.  
- **Unique Language:** Dedicated assembly-like language designed for precise control and demonstration of virtual CPU concepts.  
- **Single-threaded Simplicity:** Focus on sequential execution helps emphasize CPU instruction processing mechanics.

---

## Limitations

- **Single-process Execution:** Only one program can execute at a time on the virtual CPU.  
- **Early Development State:** Some API features are planned but not yet implemented.  
- **Platform Specific:** Implemented primarily for Windows.

---

## Usage and Safety Notes

This project is intended strictly for educational and research use within controlled university or development environments. Running unverified code or modifying system settings outside isolated virtual machines is **not recommended**.

---

## Team Members

- [plutron](https://github.com/plutron)  
- [MohammadMahdiTT](https://github.com/MohammadMahdiTT)  
- [deep4sky3abyss8](https://github.com/deep4sky3abyss8)

---

## Flow Diagram

