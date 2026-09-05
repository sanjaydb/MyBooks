#!/usr/bin/env bash
set -euo pipefail

[[ "${1:-}" == "--help" ]] && { echo "Usage: $0  # Show listening TCP and UDP ports"; exit 0; }
if command -v ss >/dev/null 2>&1; then
  ss -tulnp
elif command -v netstat >/dev/null 2>&1; then
  netstat -tulnp
else
  echo "Error: install iproute2 (ss) or net-tools (netstat)." >&2; exit 1
fi
