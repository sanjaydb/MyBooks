#!/usr/bin/env bash
set -euo pipefail

[[ "${1:-}" == "--help" ]] && { echo "Usage: $0  # Show memory and swap usage"; exit 0; }
read -r total available < <(awk '/MemTotal:/ {t=$2} /MemAvailable:/ {a=$2} END {print t, a}' /proc/meminfo)
used=$((total - available))
echo "Memory used: $((used * 100 / total))%"
free -h
