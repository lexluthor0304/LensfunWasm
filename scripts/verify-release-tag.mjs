#!/usr/bin/env node

import fs from 'node:fs';
import path from 'node:path';
import process from 'node:process';

const root = process.cwd();
const packageJsonPath = path.join(root, 'package.json');

if (!fs.existsSync(packageJsonPath)) {
  console.error('[release] package.json not found in current directory');
  process.exit(1);
}

const pkg = JSON.parse(fs.readFileSync(packageJsonPath, 'utf8'));
const version = pkg.version;
const tagArg = process.argv[2] || process.env.GITHUB_REF_NAME || '';

if (!version || typeof version !== 'string') {
  console.error('[release] package.json version is missing or invalid');
  process.exit(1);
}

if (!tagArg) {
  console.error('[release] missing tag argument. Usage: node scripts/verify-release-tag.mjs vX.Y.Z');
  process.exit(1);
}

if (!tagArg.startsWith('v')) {
  console.error(`[release] invalid tag "${tagArg}". Tag must start with "v".`);
  process.exit(1);
}

const tagVersion = tagArg.slice(1);

if (tagVersion !== version) {
  console.error(`[release] tag/version mismatch: tag=${tagArg}, package.json=${version}`);
  process.exit(1);
}

console.log(`[release] tag/version check passed: ${tagArg} == ${version}`);
