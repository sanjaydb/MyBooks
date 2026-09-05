#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 [directory]  # Count common source-code files and lines"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
directory="${1:-.}"
[[ -d "$directory" ]] || { echo "Error: directory not found: $directory" >&2; exit 2; }

printf '%-12s %8s %10s\n' "EXTENSION" "FILES" "LINES"
for extension in sh c h cpp hpp py js ts java go rs html css; do
  mapfile -d '' files < <(find "$directory" -type f -name "*.${extension}" -not -path '*/.git/*' -print0 2>/dev/null)
  if (( ${#files[@]} > 0 )); then
    lines="$(wc -l -- "${files[@]}" | awk 'END {print $1}')"
    printf '%-12s %8d %10d\n' ".$extension" "${#files[@]}" "$lines"
  fi
done
