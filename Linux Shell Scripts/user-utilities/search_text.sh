#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 TEXT [directory]  # Directory default: current directory"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
[[ $# -ge 1 && $# -le 2 ]] || { usage >&2; exit 2; }
text="$1"; directory="${2:-.}"
[[ -d "$directory" ]] || { echo "Error: directory not found: $directory" >&2; exit 2; }
if command -v rg >/dev/null 2>&1; then rg --line-number --ignore-case -- "$text" "$directory"
else grep -RIn --exclude-dir=.git -- "$text" "$directory"; fi
