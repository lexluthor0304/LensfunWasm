# Upstream Tracking

## Source of truth

- Upstream repo: https://github.com/lensfun/lensfun.git
- Integration mode: git submodule (`third_party/lensfun`)
- Current pinned commit: `655a9c4e3e53c25bc04843c853e7e7a0121359e7`
- Commit date: `2026-02-28`
- Commit subject: `Add tca data for Meike SL 35mm F1.8 STM PRO`

## Update policy

- Pin exact commits.
- Upgrade manually via PR.
- Run full build/test after each bump.

## Update steps

1. `scripts/sync-upstream.sh origin/master`
2. Review upstream diff impact (API, DB changes, compile behavior)
3. Rebuild wasm assets
4. Run tests
5. Update this file with new commit metadata
