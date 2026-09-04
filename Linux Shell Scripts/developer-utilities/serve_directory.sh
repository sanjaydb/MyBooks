#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 [directory] [port]  # Defaults: current directory, port 8000"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
directory="${1:-.}"; port="${2:-8000}"
[[ -d "$directory" ]] || { echo "Error: directory not found: $directory" >&2; exit 2; }
[[ "$port" =~ ^[0-9]+$ ]] && (( port >= 1 && port <= 65535 )) || {
  echo "Error: port must be from 1 to 65535." >&2; exit 2
}
command -v python3 >/dev/null 2>&1 || { echo "Error: python3 is not installed." >&2; exit 1; }
echo "Serving $directory at http://127.0.0.1:$port (press Ctrl+C to stop)"
python3 -m http.server "$port" --bind 127.0.0.1 --directory "$directory"
