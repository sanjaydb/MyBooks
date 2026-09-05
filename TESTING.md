# Testing status

Automated checks run on each push and pull request. A green badge in the main README reflects the latest default-branch result.

| Area | Platform / tool | Automated check |
| --- | --- | --- |
| Windows C, malware-analysis C, stack and heap safety | Windows runner, MSVC x64 | Compile every `.c` file with warnings enabled |
| Windows x86 assembly and machine-code examples | MSVC x86 | Compile every `.c` file with warnings enabled |
| Linux machine-code examples | Ubuntu, GCC | Compile every `.c` file with warnings enabled |
| Linux shell scripts | Ubuntu, Bash and ShellCheck | Syntax and static-analysis checks |
| Repository safety | Ubuntu | Reject common binaries, archives, secrets, and malware sample formats |

Automated compilation does not prove that an example is secure or suitable for production. Review the source, run security-related examples only in an isolated lab, and report discrepancies through an issue.
