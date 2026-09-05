#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 PROJECT_DIRECTORY [OUTPUT.tar.gz]"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
[[ $# -ge 1 && $# -le 2 ]] || { usage >&2; exit 2; }
project="${1%/}"
[[ -d "$project" ]] || { echo "Error: project not found: $project" >&2; exit 2; }
name="$(basename "$project")"
output="${2:-${name}_source_$(date +'%Y%m%d').tar.gz}"
tar --exclude='.git' --exclude='node_modules' --exclude='build' --exclude='dist' \
  --exclude='*.o' --exclude='*.pyc' -czf "$output" -C "$(dirname "$project")" "$name"
echo "Source archive created: $output"
