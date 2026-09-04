#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 [threshold-percent]  # Default: 80"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
threshold="${1:-80}"
if ! [[ "$threshold" =~ ^[0-9]+$ ]] || (( threshold < 1 || threshold > 100 )); then
  echo "Error: threshold must be an integer from 1 to 100." >&2; exit 2
fi

found=0
while read -r filesystem percent mountpoint; do
  used="${percent%%%}"
  if (( used >= threshold )); then
    printf 'WARNING: %s is %s full (mounted at %s)\n' "$filesystem" "$percent" "$mountpoint"
    found=1
  fi
done < <(df -P -x tmpfs -x devtmpfs | awk 'NR > 1 {print $1, $5, $6}')
(( found == 1 )) || echo "OK: no filesystem is at or above ${threshold}% usage."
