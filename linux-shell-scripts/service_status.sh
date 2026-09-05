#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 SERVICE  # Example: $0 sshd"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
[[ $# -eq 1 ]] || { usage >&2; exit 2; }
command -v systemctl >/dev/null 2>&1 || { echo "Error: systemctl is unavailable." >&2; exit 1; }

active="$(systemctl is-active "$1" 2>/dev/null || true)"
enabled="$(systemctl is-enabled "$1" 2>/dev/null || true)"
echo "Service: $1"
echo "Active:  ${active:-unknown}"
echo "Enabled: ${enabled:-unknown}"
[[ "$active" == "active" ]]
