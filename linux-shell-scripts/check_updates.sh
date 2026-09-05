#!/usr/bin/env bash
set -euo pipefail

[[ "${1:-}" == "--help" ]] && { echo "Usage: $0  # Check for updates without installing"; exit 0; }
if command -v apt >/dev/null 2>&1; then
  apt list --upgradable 2>/dev/null
elif command -v dnf >/dev/null 2>&1; then
  dnf check-update || status=$?; [[ "${status:-0}" -eq 100 ]] || exit "${status:-0}"
elif command -v yum >/dev/null 2>&1; then
  yum check-update || status=$?; [[ "${status:-0}" -eq 100 ]] || exit "${status:-0}"
elif command -v pacman >/dev/null 2>&1; then
  pacman -Qu
elif command -v zypper >/dev/null 2>&1; then
  zypper list-updates
else
  echo "Error: no supported package manager was found." >&2; exit 1
fi
