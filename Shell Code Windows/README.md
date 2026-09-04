# Safe Windows x86 Shellcode Basics

Ten local-only examples of small x86 machine-code functions embedded in C harnesses.

| Example | Behavior |
| --- | --- |
| `return_value.c` | Return the constant 42. |
| `add_values.c` | Add two signed integers. |
| `subtract_values.c` | Subtract two signed integers. |
| `multiply_values.c` | Multiply two signed integers. |
| `xor_values.c` | Apply bitwise XOR. |
| `invert_bits.c` | Apply bitwise NOT. |
| `maximum_value.c` | Return the larger signed integer. |
| `string_length.c` | Count bytes in a null-terminated ASCII string. |
| `sum_bytes.c` | Sum the bytes in a buffer. |
| `rotate_left.c` | Rotate a 32-bit value left. |

## Build

Open the **x86 Native Tools Command Prompt for VS** and run:

```bat
cl /W4 /TC return_value.c
return_value.exe
```

These examples target 32-bit x86 only. They allocate writable memory, copy the demonstration bytes, change the region to execute/read, call the local function, and release the region. They never use RWX memory.

## Safety scope

The byte sequences perform only arithmetic, comparisons, string or buffer counting, and bit operations. They do not resolve APIs, inject into another process, start programs, access files or the network, establish persistence, or evade security controls. Use them only for learning calling conventions and basic machine-code encoding.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
