## The Net Test Patcher

### What is this?

This is a small C program that patches Half-Life Net Test betas to remove the CD check and timebomb. The patches were found using x64dbg.

### How do I compile this myself?

I used TCC (Tiny C) to compile this program with the command `tcc -m32 nettest-patcher.c` (for compatibility with the 32-bit systems of the time).

### How do I use this?

Put `nettest-patcher.exe` in the same folder as `hl.exe` and run it. The original file is saved as `hl.old`.
