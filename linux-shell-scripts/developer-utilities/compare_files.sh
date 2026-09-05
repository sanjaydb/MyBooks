#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 FILE_A FILE_B"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
[[ $# -eq 2 ]] || { usage >&2; exit 2; }
[[ -f "$1" ]] || { echo "Error: file not found: $1" >&2; exit 2; }
[[ -f "$2" ]] || { echo "Error: file not found: $2" >&2; exit 2; }

status=0
if diff --help 2>&1 | grep -q -- '--color'; then
  diff -u --color=auto "$1" "$2" || status=$?
else
  diff -u "$1" "$2" || status=$?
fi
exit "$status"
