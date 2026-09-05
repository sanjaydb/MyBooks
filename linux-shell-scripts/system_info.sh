#!/usr/bin/env bash
set -euo pipefail

[[ "${1:-}" == "--help" ]] && { echo "Usage: $0  # Show system health information"; exit 0; }

echo "Hostname:         $(hostname)"
echo "Operating system: $(. /etc/os-release 2>/dev/null && echo "${PRETTY_NAME:-Unknown}" || echo "Unknown")"
echo "Kernel:           $(uname -r)"
echo "Architecture:     $(uname -m)"
echo "Uptime:           $(uptime -p 2>/dev/null || uptime)"
echo "Load average:     $(awk '{print $1, $2, $3}' /proc/loadavg)"
echo
free -h
echo
df -h --output=source,size,used,avail,pcent,target -x tmpfs -x devtmpfs
