#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 [directory] FILE_NAME_PART"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
if [[ $# -eq 1 ]]; then directory="."; pattern="$1";
elif [[ $# -eq 2 ]]; then directory="$1"; pattern="$2";
else usage >&2; exit 2; fi
[[ -d "$directory" ]] || { echo "Error: directory not found: $directory" >&2; exit 2; }
find "$directory" -type f -iname "*${pattern}*" 2>/dev/null
