#!/usr/bin/env bash
set -euo pipefail

[[ "${1:-}" == "--help" ]] && { echo "Usage: $0  # List local user accounts"; exit 0; }
printf '%-24s %-8s %-32s %s\n' "USER" "UID" "HOME" "SHELL"
printf '%-24s %-8s %-32s %s\n' "----" "---" "----" "-----"
while IFS=: read -r username _ uid _ _ home shell; do
  printf '%-24s %-8s %-32s %s\n' "$username" "$uid" "$home" "$shell"
done < /etc/passwd
