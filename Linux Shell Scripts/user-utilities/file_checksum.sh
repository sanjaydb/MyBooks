#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 FILE [EXPECTED_SHA256]"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
[[ $# -ge 1 && $# -le 2 ]] || { usage >&2; exit 2; }
[[ -f "$1" ]] || { echo "Error: file not found: $1" >&2; exit 2; }
actual="$(sha256sum "$1" | awk '{print $1}')"
if [[ $# -eq 1 ]]; then echo "$actual  $1"; exit 0; fi
if [[ "${actual,,}" == "${2,,}" ]]; then echo "OK: checksum matches.";
else echo "FAILED: checksum does not match." >&2; echo "Actual: $actual" >&2; exit 1; fi
