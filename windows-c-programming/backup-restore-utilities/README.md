# Windows Backup and Restore Utilities in C

Ten conservative examples for backing up files, restoring data, and checking backup integrity.

| Program | Purpose |
| --- | --- |
| `backup_file.c` | Create a timestamped copy of one file. |
| `restore_file_safe.c` | Restore a file without overwriting an existing destination. |
| `backup_directory.c` | Copy a directory tree to a new backup location. |
| `restore_directory_safe.c` | Restore a directory tree only when the destination is absent. |
| `verify_files.c` | Compare two files using SHA-256. |
| `create_manifest.c` | Write a size-and-time manifest for a directory. |
| `list_backups.c` | List files in a backup directory. |
| `file_versions.c` | Find timestamped backup versions of a file. |
| `environment_snapshot.c` | Save important user environment paths to a text file. |
| `backup_space_check.c` | Check whether a destination has enough free space for a file. |

## Build

```bat
cl /W4 backup_file.c
cl /W4 backup_directory.c /link Shell32.lib
cl /W4 verify_files.c /link Bcrypt.lib
```

Every required library is also declared in its source file. Restore examples deliberately refuse to overwrite existing destinations. Test with disposable data before using these examples for important files.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
