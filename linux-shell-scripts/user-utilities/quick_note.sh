#!/usr/bin/env bash
set -euo pipefail

notes_file="${XDG_DATA_HOME:-$HOME/.local/share}/quick-notes.txt"
usage() { echo "Usage: $0 add TEXT | list | search TEXT | clear"; }
[[ "${1:-}" == "--help" ]] && { usage; exit 0; }
command="${1:-}"
case "$command" in
  add)
    shift; [[ $# -gt 0 ]] || { usage >&2; exit 2; }
    mkdir -p "$(dirname "$notes_file")"
    printf '[%s] %s\n' "$(date +'%Y-%m-%d %H:%M')" "$*" >> "$notes_file"
    echo "Note added."
    ;;
  list) [[ -f "$notes_file" ]] && nl -ba "$notes_file" || echo "No notes yet." ;;
  search) shift; [[ $# -gt 0 ]] || { usage >&2; exit 2; }; [[ -f "$notes_file" ]] && grep -in -- "$*" "$notes_file" || echo "No matching notes." ;;
  clear) [[ -f "$notes_file" ]] && : > "$notes_file"; echo "Notes cleared." ;;
  *) usage >&2; exit 2 ;;
esac
