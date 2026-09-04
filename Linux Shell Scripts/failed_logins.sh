#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 [count]  # Default: 20"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
count="${1:-20}"
[[ "$count" =~ ^[1-9][0-9]*$ ]] || { echo "Error: count must be positive." >&2; exit 2; }
command -v lastb >/dev/null 2>&1 || { echo "Error: lastb is not installed." >&2; exit 1; }
lastb -n "$count" 2>/dev/null || { echo "Unable to read the log. Try sudo." >&2; exit 1; }
