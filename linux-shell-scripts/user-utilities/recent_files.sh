#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 [directory] [days]  # Defaults: current directory, 7 days"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
directory="${1:-.}"; days="${2:-7}"
[[ -d "$directory" ]] || { echo "Error: directory not found: $directory" >&2; exit 2; }
[[ "$days" =~ ^[0-9]+$ ]] || { echo "Error: days must be a non-negative integer." >&2; exit 2; }
find "$directory" -type f -mtime "-${days}" -printf '%TY-%Tm-%Td %TH:%TM  %p\n' 2>/dev/null | sort -r
