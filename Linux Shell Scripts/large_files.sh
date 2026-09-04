#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 [directory] [count]  # Defaults: current directory, 10"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
directory="${1:-.}"
count="${2:-10}"
[[ -d "$directory" ]] || { echo "Error: directory not found: $directory" >&2; exit 2; }
[[ "$count" =~ ^[1-9][0-9]*$ ]] || { echo "Error: count must be positive." >&2; exit 2; }

echo "Largest $count files under: $(realpath "$directory")"
find "$directory" -type f -printf '%s\t%p\n' 2>/dev/null \
  | sort -nr | head -n "$count" | numfmt --field=1 --to=iec --suffix=B
