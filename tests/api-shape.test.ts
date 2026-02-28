import { describe, expect, it } from 'vitest';
import {
  LF_MODIFY_DISTORTION,
  LF_MODIFY_GEOMETRY,
  LF_SEARCH_SORT_AND_UNIQUIFY,
  createLensfun
} from '../src/index';

describe('public constants', () => {
  it('exposes expected lensfun flags', () => {
    expect(LF_SEARCH_SORT_AND_UNIQUIFY).toBe(2);
    expect(LF_MODIFY_DISTORTION).toBe(0x00000008);
    expect(LF_MODIFY_GEOMETRY).toBe(0x00000010);
  });
});

describe('createLensfun', () => {
  it('throws when no module factory can be resolved', async () => {
    await expect(createLensfun({ autoInitDb: false })).rejects.toThrow(/module factory not found/i);
  });
});
