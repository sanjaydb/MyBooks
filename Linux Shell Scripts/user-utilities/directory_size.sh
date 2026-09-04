#!/usr/bin/env bash
set -euo pipefail

[[ "${1:-}" == "--help" ]] && { echo "Usage: $0 [directory]  # Default: current directory"; exit 0; }
directory="${1:-.}"
[[ -d "$directory" ]] || { echo "Error: directory not found: $directory" >&2; exit 2; }
du -sh "$directory"
