#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 PORT"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
if [[ $# -ne 1 || ! "$1" =~ ^[0-9]+$ ]] || (( $1 < 1 || $1 > 65535 )); then
  echo "Error: provide a port from 1 to 65535." >&2
  exit 2
fi

if command -v lsof >/dev/null 2>&1; then lsof -nP -i ":$1" || echo "No process found on port $1."
elif command -v ss >/dev/null 2>&1; then ss -tulpn "sport = :$1" || true
else echo "Error: install lsof or iproute2 (ss)." >&2; exit 1; fi
