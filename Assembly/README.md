# Windows 11 x86 Assembly Examples

Ten small Microsoft x86 inline-assembly examples embedded in C source files so they can be compiled directly with `cl`.

| Example | Demonstrates |
| --- | --- |
| `add_numbers.c` | Integer addition |
| `subtract_numbers.c` | Integer subtraction |
| `multiply_numbers.c` | Signed multiplication |
| `divide_numbers.c` | Signed division and remainder |
| `maximum_value.c` | Comparison and conditional branching |
| `sum_array.c` | Looping through an integer array |
| `string_length.c` | Scanning a null-terminated string |
| `count_character.c` | Counting matching characters |
| `rotate_bits.c` | Bit rotation |
| `cpuid_vendor.c` | Reading the CPU vendor with `CPUID` |

## Build requirements

- Windows 11 on an x86 or x64 computer
- Visual Studio or Build Tools with the **Desktop development with C++** workload
- The **x86 Native Tools Command Prompt for VS**

```bat
cl /W4 /TC add_numbers.c
add_numbers.exe
```

These examples use MSVC's `__asm` extension and therefore compile only as 32-bit x86 targets. The x64 MSVC compiler does not support inline assembly. Standalone `.asm` files require `ml.exe` or `ml64.exe` and separate linking.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
