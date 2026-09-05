#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 PROCESS_NAME"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
[[ $# -eq 1 ]] || { usage >&2; exit 2; }
if ! pgrep -a -i -- "$1"; then echo "No matching process found."; fi
