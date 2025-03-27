#!/bin/bash
# Clean up nested Git repositories inside current folder

echo "🔍 Searching for nested .git folders..."
find . -type d -name ".git" -not -path "./.git" | while read gitdir; do
  echo "🧹 Removing $gitdir"
  rm -rf "$gitdir"
done

echo "✅ All nested .git folders removed."

