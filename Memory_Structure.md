# Virtual Machine – Memory Structure Overview

این سند نمای کلی از ساختار حافظه و داده‌های مورد استفاده در ماشین مجازی را توضیح می‌دهد.  

---

## 1. Boot Loader Address
- **Type:** `const char*`  
- **Purpose:** نگهداری مسیر فایل سیستم‌عامل برای بارگذاری.  
- **Example:**
  ```c
  "../DisassemblyPograms/os.txt"
  ```

```
+---------------------------+
|   BOOT LOADER ADDRESS     |
+---------------------------+
```

---

## 2. OS_RAM
- **Type:** `struct ram[10000]`  
- **Purpose:** ذخیره هر خط از کد اسمبلی سیستم‌عامل.  
- **Structure:**
  ```c
  struct ram {
      char command[5]; // Assembly mnemonic (4 chars + \0)
      int v1, v2, v3;  // Arguments (line numbers, addresses, values)
  };
  ```
- **Notes:** اندیس آرایه به‌عنوان **شماره خط** در پرش‌ها و اجرا استفاده می‌شود.

```
+-----------------------------------+
|             OS_RAM                |
|-----------------------------------|
| [0] -> struct ram {cmd,v1,v2,v3}  |
| [1] -> struct ram {cmd,v1,v2,v3}  |
| ...                               |
| [9999]                            |
+-----------------------------------+
```

---

## 3. PR_RAM (Program RAM)
- **Type:** `struct ram[10000]`  
- **Purpose:** ذخیره خطوط اسمبلی برنامه در حال اجرا.  
- **Structure:** مشابه **OS_RAM**.

```
+-----------------------------------+
|             PR_RAM                |
|-----------------------------------|
| [0] -> struct ram {cmd,v1,v2,v3}  |
| [1] -> struct ram {cmd,v1,v2,v3}  |
| ...                               |
| [9999]                            |
+-----------------------------------+
```

---

## 4. Heap Memory
- **Type:** `struct heap_s`  
- **Purpose:** ذخیره متغیرهای برنامه.  
- **Structure:**
  ```c
  struct heap_s {
      int ints;   // Integer variables
      char chrs;  // Single character storage
      char strs;  // Continuous chars storing strings
  };
  ```

```
+-------------------------------+
|          HEAP MEMORY          |
|-------------------------------|
| ints : int variables          |
| chrs : single characters      |
| strs : string buffer          |
+-------------------------------+
```

---

## 5. Stack Memory
- **Type:** `int stack[100]`  
- **Purpose:** عملیات **LIFO** (آخر وارد، اول خارج).

```
+---------------------+
|    STACK MEMORY     |
|---------------------|
| [0]   int           |
| [1]   int           |
| ...                 |
| [99]  int           |
+---------------------+
```

---

## 6. EIP Registers
- **Purpose:** نگهداری شماره خط در حال اجرا.  
- **Definition:**
  ```c
  int os_eip;  // Current line in OS_RAM
  int pr_eip;  // Current line in PR_RAM
  ```

```
+-----------------------+
|     EIP REGISTERS     |
|-----------------------|
| os_eip -> OS_RAM idx  |
| pr_eip -> PR_RAM idx  |
+-----------------------+
```

---

## 7. Registers
- **Type:** `struct regs`  
- **Purpose:** رجیسترهای عمومی برای اشاره به حافظه.  
- **Structure:**
  ```c
  struct regs {
      void *address; // Pointer to a memory location
      char type;     // 'I' (int), 'C' (char), 'S' (string)
  } registers;
  ```

```
+----------------------+
|      REGISTERS       |
|----------------------|
| address -> pointer   |
| type    -> I/C/S     |
+----------------------+
```

---

## 8. Control Flags
- **Purpose:** تعیین حافظه فعال.  
- **Definition:**
  ```c
  int which_ram; // 0 = OS_RAM, 1 = PR_RAM
  ```

```
+------------------------+
|     CONTROL FLAGS      |
|------------------------|
| which_ram -> activeRAM |
+------------------------+
```

---

✅ این شماتیک ترکیبی از توضیحات فنی + دیاگرام‌های بصری است و آماده‌ی استفاده در **README.md** یا مستندات پروژه است.  
