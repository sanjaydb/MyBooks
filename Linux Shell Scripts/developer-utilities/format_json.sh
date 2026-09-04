#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 JSON_FILE [OUTPUT_FILE]"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
[[ $# -ge 1 && $# -le 2 ]] || { usage >&2; exit 2; }
[[ -f "$1" ]] || { echo "Error: file not found: $1" >&2; exit 2; }

if command -v jq >/dev/null 2>&1; then formatter=(jq .)
elif command -v python3 >/dev/null 2>&1; then formatter=(python3 -m json.tool)
else echo "Error: install jq or python3." >&2; exit 1; fi

if [[ $# -eq 2 ]]; then "${formatter[@]}" "$1" > "$2"; echo "Formatted JSON written to: $2"
else "${formatter[@]}" "$1"; fi
