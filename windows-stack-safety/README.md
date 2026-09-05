# Windows Stack Overflow Safety Examples

Ten defensive C examples showing how stack-buffer errors arise and how to prevent them on Windows.

**Tested status:** all 10 examples compile with Visual Studio 2022 MSVC x64 and are checked automatically on GitHub Actions.

| Example | Lesson |
| --- | --- |
| `checked_string_copy.c` | Validate length before copying text. |
| `checked_memory_copy.c` | Validate byte counts before `memcpy`. |
| `off_by_one.c` | Reserve space for the null terminator. |
| `command_line_input.c` | Reject oversized command-line input. |
| `wide_string_copy.c` | Use element counts correctly with wide strings. |
| `canary_detection.c` | Demonstrate sentinel-based corruption detection. |
| `thread_stack_limits.c` | Inspect current thread stack boundaries. |
| `safe_alloca.c` | Limit dynamic stack allocation. |
| `recursion_limit.c` | Prevent uncontrolled recursive stack growth. |
| `array_index_check.c` | Validate indexes before stack-array access. |

## Build

Use a Developer Command Prompt for Visual Studio:

```bat
cl /W4 /sdl /GS checked_string_copy.c
```

For additional development-time diagnostics:

```bat
cl /W4 /sdl /GS /RTC1 checked_string_copy.c
cl /analyze checked_string_copy.c
```

`/GS` is enabled by default in modern MSVC builds, but it is written explicitly here for clarity. These examples reject unsafe input and contain no shellcode, return-address manipulation, ROP, process injection, or mitigation bypasses.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
