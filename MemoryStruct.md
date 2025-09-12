# Memory Structure Overview for Virtual Machine

+------------------------------------------------------------+
| BOOT LOADER ADDRESS |
| - A constant char pointer holding path to the OS file |
| Example: "../DisassemblyPograms/os.txt" |
+------------------------------------------------------------+

+------------------------------------------------------------+
| OS_RAM |
| - An array of struct ram with 10,000 entries |
| - Each entry holds one line of OS assembly code |
| |
| struct ram { |
| char command

; // Assembly mnemonic (4 chars + \0)|
| int v1, v2, v3; // Arguments (line numbers, addresses, values) |
| } |
| |
| - The index is used as line number for jumps and execution|
+------------------------------------------------------------+

+------------------------------------------------------------+
| PR_RAM (Program RAM) |
| - Same structure and size as OS_RAM |
| - Stores the currently running program’s assembly lines |
+------------------------------------------------------------+

+------------------------------------------------------------+
| HEAP MEMORY |
| struct heap_s { |
| int ints; // Integer variables |
| char chrs; // Single character storage |
| char strs; // Continuous chars storing strings |
| } |
| - Accessed via registers holding pointers and type info |
+------------------------------------------------------------+

+------------------------------------------------------------+
| STACK MEMORY |
| - Integer array of size 100 |
| - Used for last-in-first-out (LIFO) operations |
+------------------------------------------------------------+

+------------------------------------------------------------+
| EIP REGISTERS |
| - int os_eip, pr_eip |
| - Track current execution line number in OS_RAM and PR_RAM |
+------------------------------------------------------------+

+------------------------------------------------------------+
| REGISTERS |
| struct regs registers; |
| struct regs { |
| void *address; // Pointer to a memory location |
| char type; // Data type: 'I' (int), 'C' (char), 'S' (string) |
| } |
+------------------------------------------------------------+

+------------------------------------------------------------+
| CONTROL FLAGS |
| int which_ram; // Indicates active RAM (OS or Program) |
+------------------------------------------------------------+


This schematic provides a clear and professional overview of your virtual machine's memory layout and data structures, ready to be used in technical documentation or README files.
