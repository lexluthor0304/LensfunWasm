#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SUBMODULE_DIR="${ROOT_DIR}/third_party/lensfun"

if [[ ! -d "${SUBMODULE_DIR}" ]]; then
  echo "[sync-upstream] lensfun submodule not found at ${SUBMODULE_DIR}" >&2
  exit 1
fi

pushd "${SUBMODULE_DIR}" >/dev/null

git fetch origin
TARGET="${1:-origin/master}"
git checkout "${TARGET}"

NEW_COMMIT="$(git rev-parse HEAD)"
NEW_SUBJECT="$(git log -1 --format=%s)"

popd >/dev/null

echo "[sync-upstream] lensfun updated to ${NEW_COMMIT}"
echo "[sync-upstream] ${NEW_SUBJECT}"
echo "[sync-upstream] run tests and update UPSTREAM.md before committing"
