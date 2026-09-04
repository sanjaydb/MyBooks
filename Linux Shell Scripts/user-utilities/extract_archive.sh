#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 ARCHIVE [destination]"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
[[ $# -ge 1 && $# -le 2 ]] || { usage >&2; exit 2; }
archive="$1"; destination="${2:-.}"
[[ -f "$archive" ]] || { echo "Error: archive not found: $archive" >&2; exit 2; }
mkdir -p "$destination"
case "$archive" in
  *.tar.gz|*.tgz) tar -xzf "$archive" -C "$destination" ;;
  *.tar.bz2|*.tbz2) tar -xjf "$archive" -C "$destination" ;;
  *.tar.xz|*.txz) tar -xJf "$archive" -C "$destination" ;;
  *.tar) tar -xf "$archive" -C "$destination" ;;
  *.zip) command -v unzip >/dev/null || { echo "Error: unzip is not installed." >&2; exit 1; }; unzip "$archive" -d "$destination" ;;
  *.gz) gzip -dc "$archive" > "$destination/$(basename "${archive%.gz}")" ;;
  *.bz2) bzip2 -dc "$archive" > "$destination/$(basename "${archive%.bz2}")" ;;
  *) echo "Error: unsupported archive format." >&2; exit 2 ;;
esac
echo "Extracted to: $destination"
