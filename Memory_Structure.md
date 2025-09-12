# Sky-Machine – Memory Structure Overview

This document provides an overview of the memory structure and data used in a virtual machine.

---

## 1. Boot Loader Address
- **Type:** `const char*`
- **Purpose:** Holds the path to the operating system file to load.
- **Example:**
```c
"../DisassemblyPograms/os.txt"
```

| BOOT LOADER ADDRESS |

---

## 2. OS_RAM
- **Type:** `struct ram[10000]`
- **Purpose:** Holds each line of OS assembly code.
- **Structure:**
```c
struct ram {
char command[5]; // Assembly mnemonic (4 chars + \0)
int v1, v2, v3; // Arguments (line numbers, addresses, values)
};
```
- **Notes:** Array index is used as **line number** in jumps and execution.


| OS_RAM |
|-----------------------------------|
| [0] -> struct ram {cmd,v1,v2,v3} |
| [1] -> struct ram {cmd,v1,v2,v3} |
| ... |
| [9999] |

---

## 3. PR_RAM (Program RAM)
- **Type:** `struct ram[10000]`
- **Purpose:** Stores assembly lines of the currently running program.
- **Structure:** Similar to **OS_RAM**.



| PR_RAM |
|-----------------------------------|
| [0] -> struct ram {cmd,v1,v2,v3} |
| [1] -> struct ram {cmd,v1,v2,v3} |
| ...
| [9999] |


---

## 4. Heap Memory
- **Type:** `struct heap_s`
- **Purpose:** Store program variables.
- **Structure:** 
```c 
struct heap_s { 
int ints; // Integer variables 
char chrs; // Single character storage 
char strs; // Continuous chars storing strings 
}; 
```

| HEAP MEMORY |
|----------------------------|
| ints : int variables |
| chrs : single characters |
| strs : string buffer |

---

## 5. Stack Memory
- **Type:** `int stack[100]`
- **Purpose:** **LIFO** (last in, first out) operation.


| STACK MEMORY |
|-------------------|
| [0] int |
| [1] int |
| ... |
| [99] int |


---

## 6. EIP Registers
- **Purpose:** Maintains the line number of the current execution.
- **Definition:**
```c
int os_eip; // Current line in OS_RAM
int pr_eip; // Current line in PR_RAM
```


| EIP REGISTERS |
|-------------------|
| os_eip -> OS_RAM idx |
| pr_eip -> PR_RAM idx |

---

## 7. Registers
- **Type:** `struct regs`
- **Purpose:** General registers for pointing to memory.
- **Structure:**
```c
struct regs {
void *address; // Pointer to a memory location
char type; // 'I' (int), 'C' (char), 'S' (string)
} registers;
```

| REGISTERS |
|--------------------|
| address -> pointer |
| type -> I/C/S |

---

## 8. Control Flags
- **Purpose:** Determines active memory.
- **Definition:**
```c
int which_ram; // 0 = OS_RAM, 1 = PR_RAM
```

| CONTROL FLAGS |
|------------------------|
| which_ram -> activeRAM |

---