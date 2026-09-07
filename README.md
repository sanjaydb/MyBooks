# MyBooks: Companion Sample Code

[![Windows builds](https://github.com/sanjaydb/MyBooks/actions/workflows/windows-build.yml/badge.svg?branch=main)](https://github.com/sanjaydb/MyBooks/actions/workflows/windows-build.yml)
[![Linux checks](https://github.com/sanjaydb/MyBooks/actions/workflows/linux-checks.yml/badge.svg?branch=main)](https://github.com/sanjaydb/MyBooks/actions/workflows/linux-checks.yml)
[![Repository safety](https://github.com/sanjaydb/MyBooks/actions/workflows/repository-safety.yml/badge.svg?branch=main)](https://github.com/sanjaydb/MyBooks/actions/workflows/repository-safety.yml)
[![License: CC0-1.0 OR MIT](https://img.shields.io/badge/license-CC0--1.0%20OR%20MIT-blue.svg)](LICENSE.md)

I am writing practical books about Linux and Windows systems programming, assembly language, reverse engineering, and defensive malware analysis. This repository contains sample code from those books.

I publish the examples openly so readers around the world can test them, report mistakes, suggest improvements, and help me make the code and books more accurate. I have been writing these books for several months and update them whenever time permits. I may also create companion videos in the future.

Feedback, corrections, issues, and pull requests are welcome. Thank you for helping improve this work!

## Repository sections

| Section | Contents |
| --- | --- |
| [Linux shell scripts](linux-shell-scripts/) | Administration, user, and developer Bash utilities. |
| [Windows C programming](windows-c-programming/) | Windows administration, user, sockets, IPC, SMB, Internet, backup, and encryption examples. |
| [Malware analysis](malware-analysis/) | Defensive analysis and PE, DLL, and COFF inspection examples. |
| [Assembly](assembly/) | Windows 11 x86 inline-assembly examples for MSVC `cl`. |
| [Windows shellcode](shellcode-windows/) | Safe, local-only Windows x86 machine-code demonstrations. |
| [Linux shellcode](shellcode-linux/) | Safe, local-only Linux x86-64 machine-code demonstrations. |
| [Windows stack safety](windows-stack-safety/) | Defensive examples explaining and preventing stack-buffer errors. |
| [Windows heap safety](windows-heap-safety/) | Defensive examples explaining and preventing heap errors. |

See [BOOKS.md](BOOKS.md) for the chapter-ready roadmap and [TESTING.md](TESTING.md) for build coverage and verification status.

## Safety and scope

The security-related material is for lawful education, defensive research, and isolated lab use. Do not use it to access or damage systems without explicit authorization. This repository intentionally excludes live malware, credentials, personal data, compiled binaries, and weaponized payloads.

## Contributing

Corrections are especially valuable. Please read [CONTRIBUTING.md](CONTRIBUTING.md) before opening an issue or pull request. Report security or privacy concerns according to [SECURITY.md](SECURITY.md).

## License

Unless a file says otherwise, you may use this repository under either **CC0-1.0** or the **MIT License**, at your choice. See [LICENSE.md](LICENSE.md).

## Repository notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
