#!/usr/bin/env bash
set -euo pipefail

[[ "${1:-}" == "--help" ]] && { echo "Usage: $0 [repository]"; exit 0; }
repository="${1:-.}"
git -C "$repository" rev-parse --is-inside-work-tree >/dev/null 2>&1 || {
  echo "Error: not a Git repository: $repository" >&2; exit 2
}

echo "Repository: $(git -C "$repository" rev-parse --show-toplevel)"
echo "Branch:     $(git -C "$repository" branch --show-current)"
echo "Last commit:"
git -C "$repository" log -1 --format='  %h  %ad  %s' --date=short 2>/dev/null || echo "  No commits yet"
echo "Working tree:"
status="$(git -C "$repository" status --short)"
[[ -n "$status" ]] && printf '%s\n' "$status" || echo "  Clean"
