# Windows SMB Utilities in C

Ten small Windows C examples for legitimate SMB share inspection and file access.

| Program | Purpose |
| --- | --- |
| `local_shares.c` | List shares published by the local computer. |
| `remote_shares.c` | List shares published by a specified computer. |
| `share_details.c` | Display details about one SMB share. |
| `server_info.c` | Display basic information about an SMB server. |
| `smb_sessions.c` | List active SMB sessions. |
| `smb_open_files.c` | List files currently open through SMB. |
| `list_unc_directory.c` | List a directory using a UNC path. |
| `unc_path_info.c` | Display information about a UNC file or directory. |
| `read_remote_text_file.c` | Read a text file from a UNC path. |
| `copy_from_share.c` | Safely copy a file from a share without overwriting. |

## Build

Use a Developer Command Prompt for Visual Studio:

```bat
cl /W4 local_shares.c /link Netapi32.lib
cl /W4 remote_shares.c /link Netapi32.lib
cl /W4 list_unc_directory.c
```

Files using Network Management APIs include their required `Netapi32.lib` directive. Use only computers and shares you are authorized to access. Session and open-file enumeration normally requires administrator privileges on the target server.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
