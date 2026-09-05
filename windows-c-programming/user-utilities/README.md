# Windows User Utilities in C

Ten simple C programs for everyday Windows tasks.

| Program | Purpose |
| --- | --- |
| `clipboard_viewer.c` | Print Unicode text currently stored on the clipboard. |
| `file_info.c` | Display a file's size and timestamps. |
| `list_directory.c` | List files and folders in a directory. |
| `search_text.c` | Find text within a plain-text file. |
| `drive_list.c` | List available Windows drives and their types. |
| `environment_info.c` | Display common user environment locations. |
| `screen_info.c` | Show monitor count, desktop size, and work-area size. |
| `current_time.c` | Show local time, UTC time, and time-zone information. |
| `countdown_timer.c` | Run a simple countdown timer. |
| `copy_file_safe.c` | Copy a file without overwriting an existing destination. |

## Build

Open a **Developer Command Prompt for Visual Studio**, enter this directory, and compile any example:

```bat
cl /W4 clipboard_viewer.c
cl /W4 file_info.c
cl /W4 copy_file_safe.c
```

The programs use Windows APIs available through the standard Windows SDK and do not require third-party libraries.

Run a program without the required arguments to see its usage instructions.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
