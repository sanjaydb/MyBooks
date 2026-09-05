# Safe Linux x86-64 Shellcode Basics

Ten local-only examples of small x86-64 System V machine-code functions embedded in C harnesses.

**Tested status:** all 10 harnesses compile with GCC on Ubuntu through GitHub Actions.

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

On a 64-bit x86 Linux system:

```bash
gcc -std=c11 -Wall -Wextra -O2 return_value.c -o return_value
./return_value
```

The harness allocates writable memory, copies the demonstration bytes, changes the region to execute/read, invokes the local function, and releases the mapping. It never requests writable and executable memory simultaneously.

## Safety scope

The byte sequences perform only arithmetic, comparisons, string or buffer counting, and bit operations. They make no Linux system calls and do not inject into processes, launch commands, access files or networks, establish persistence, or evade security controls.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
