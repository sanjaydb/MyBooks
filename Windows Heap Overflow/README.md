# Windows Heap Overflow Safety Examples

Ten defensive C examples showing how to prevent heap-buffer errors on Windows.

| Example | Lesson |
| --- | --- |
| `checked_string_copy.c` | Allocate and copy a bounded string safely. |
| `checked_memory_copy.c` | Validate byte counts before a heap copy. |
| `allocation_overflow.c` | Detect multiplication overflow before allocation. |
| `safe_realloc.c` | Preserve the original allocation when resizing fails. |
| `heap_validation.c` | Validate a private Windows heap after normal use. |
| `array_bounds.c` | Check indexes before heap-array access. |
| `secure_cleanup.c` | Clear sensitive bytes before freeing memory. |
| `pointer_lifetime.c` | Avoid double-free and dangling-pointer use. |
| `flexible_buffer.c` | Safely allocate a header plus variable-length data. |
| `heap_sentinel.c` | Check a sentinel placed after a bounded buffer. |

## Build

Use a Developer Command Prompt for Visual Studio:

```bat
cl /W4 /sdl checked_string_copy.c
```

Additional development checks:

```bat
cl /W4 /sdl /RTC1 checked_string_copy.c
cl /analyze checked_string_copy.c
```

These examples reject unsafe sizes and never intentionally write outside an allocation. They contain no heap exploitation, arbitrary-write primitive, heap grooming, use-after-free abuse, code execution, or mitigation bypass.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
