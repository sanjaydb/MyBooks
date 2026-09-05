# Linux Shell Scripts

Ten simple Bash utilities for common Linux administration tasks.

**Tested status:** all 30 scripts receive Bash syntax and ShellCheck validation on Ubuntu through GitHub Actions.

## Scripts

| Script | Purpose |
| --- | --- |
| `system_info.sh` | Display a concise system-health summary. |
| `disk_usage_alert.sh` | Warn when a filesystem exceeds a usage threshold. |
| `memory_usage.sh` | Show memory and swap consumption. |
| `service_status.sh` | Check whether a systemd service is active. |
| `large_files.sh` | Find the largest files beneath a directory. |
| `user_accounts.sh` | List local user accounts in a readable table. |
| `listening_ports.sh` | Display listening network ports and processes. |
| `failed_logins.sh` | Show recent failed login attempts. |
| `backup_directory.sh` | Create a timestamped compressed directory backup. |
| `check_updates.sh` | Check for available package updates. |

## Usage

```bash
chmod +x system_info.sh
./system_info.sh
```

Run a script with `--help` to see its arguments. Some commands may require `sudo`.

## Everyday user utilities

The [`user-utilities`](./user-utilities/) directory contains ten additional scripts for common personal tasks such as finding files, searching text, extracting archives, creating checksums, and keeping quick notes.

## Developer utilities

The [`developer-utilities`](./developer-utilities/) directory contains ten scripts for Git summaries, code statistics, TODO searches, JSON formatting, local file serving, dependency checks, and other everyday development tasks.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
