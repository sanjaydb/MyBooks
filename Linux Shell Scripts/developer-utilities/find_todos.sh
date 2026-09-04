#!/usr/bin/env bash
set -euo pipefail

[[ "${1:-}" == "--help" ]] && { echo "Usage: $0 [directory]"; exit 0; }
directory="${1:-.}"
[[ -d "$directory" ]] || { echo "Error: directory not found: $directory" >&2; exit 2; }

if command -v rg >/dev/null 2>&1; then
  rg --line-number --color=auto --glob '!.git/**' 'TODO|FIXME|HACK' "$directory" || true
else
  grep -RInE --exclude-dir=.git 'TODO|FIXME|HACK' "$directory" || true
fi
