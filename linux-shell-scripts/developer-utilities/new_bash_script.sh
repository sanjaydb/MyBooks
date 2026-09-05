#!/usr/bin/env bash
set -euo pipefail

usage() { echo "Usage: $0 SCRIPT_NAME"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
[[ $# -eq 1 ]] || { usage >&2; exit 2; }
output="$1"; [[ "$output" == *.sh ]] || output="${output}.sh"
[[ ! -e "$output" ]] || { echo "Error: file already exists: $output" >&2; exit 1; }

printf '%s\n' '#!/usr/bin/env bash' 'set -euo pipefail' '' '# Add your code here.' > "$output"
chmod +x "$output"
echo "Created executable script: $output"
