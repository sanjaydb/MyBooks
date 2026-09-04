#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 SOURCE_DIRECTORY [DESTINATION_DIRECTORY]"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
[[ $# -ge 1 && $# -le 2 ]] || { usage >&2; exit 2; }
source_dir="${1%/}"
destination="${2:-.}"
[[ -d "$source_dir" ]] || { echo "Error: source not found: $source_dir" >&2; exit 2; }
[[ -d "$destination" ]] || { echo "Error: destination not found: $destination" >&2; exit 2; }

source_parent="$(dirname "$source_dir")"
source_name="$(basename "$source_dir")"
archive="$destination/${source_name}_$(date +'%Y%m%d_%H%M%S').tar.gz"
tar -czf "$archive" -C "$source_parent" "$source_name"
echo "Backup created: $archive"
