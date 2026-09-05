#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 COMMAND [COMMAND ...]  # Example: $0 git make gcc"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
[[ $# -gt 0 ]] || { usage >&2; exit 2; }

missing=0
for dependency in "$@"; do
  if command -v "$dependency" >/dev/null 2>&1; then printf 'FOUND    %-20s %s\n' "$dependency" "$(command -v "$dependency")"
  else printf 'MISSING  %s\n' "$dependency"; missing=1; fi
done
exit "$missing"
