import { defineConfig } from 'tsup';

export default defineConfig([
  {
    entry: { index: 'src/index.ts' },
    clean: true,
    format: ['esm'],
    outDir: 'dist/esm',
    sourcemap: true,
    target: 'es2020'
  },
  {
    entry: { index: 'src/index.ts' },
    clean: false,
    format: ['iife'],
    globalName: 'LensfunWasm',
    outDir: 'dist/umd',
    outExtension: () => ({ js: '.iife.js' }),
    sourcemap: true,
    target: 'es2020',
    platform: 'browser'
  }
]);
