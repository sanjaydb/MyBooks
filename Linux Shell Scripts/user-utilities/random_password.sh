#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 [length]  # Default: 20, minimum: 8"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
length="${1:-20}"
[[ "$length" =~ ^[0-9]+$ ]] && (( length >= 8 )) || { echo "Error: length must be at least 8." >&2; exit 2; }
LC_ALL=C tr -dc 'A-Za-z0-9!@#%_=+-' < /dev/urandom | head -c "$length" || true
echo
