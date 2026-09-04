#!/usr/bin/env bash
set -euo pipefail

[[ "${1:-}" == "--help" ]] && { echo "Usage: $0 [directory]  # Default: current directory"; exit 0; }
directory="${1:-.}"
[[ -d "$directory" ]] || { echo "Error: directory not found: $directory" >&2; exit 2; }
files="$(find "$directory" -type f 2>/dev/null | wc -l)"
directories="$(find "$directory" -mindepth 1 -type d 2>/dev/null | wc -l)"
echo "Directory:   $(realpath "$directory")"
echo "Files:       $files"
echo "Subfolders:  $directories"
