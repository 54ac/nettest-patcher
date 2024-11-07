## The Half-Life CD Check Patcher

### What is this?

This is a small C program that patches early versions of Half-Life to remove the CD check. It also removes the timebomb and CD check from the Net Test betas. The offsets were found using x64dbg.

### How do I use this?

Place `hl-cd-patcher.exe` in the same folder as `hl.exe` and run it. The original file will be backed up as `hl.bak`.

### How does this work?

- The boolean result of the CD check function is evaluated with a `jnz` instruction. By changing the instruction to `jmp` (or `jns` in versions where a far jump is required, to keep the patch within one byte), the game always treats the check as successful. This approach differs from e.g. the warez release by CLASS, where the function is instead modified to always return true, altering several bytes in the executable.
- The timebomb check is simply jumped over.

### How do I compile this myself?

This program was compiled using TCC (Tiny C Compiler) as a 32-bit application with the command `tcc -m32 hl-cd-patcher.c db.c` to ensure compatibility with the 32-bit systems of the time.

### Additional notes

- This patcher only works with early versions of Half-Life, from the Net Test betas through all retail versions up to 1.1.0.1, after which the CD check was removed.
- The CD key check is not affected; the aim of the tool is to allow owners of the game to experience early versions of Half-Life without having to keep old CDs or optical drives.
- These versions of the game use CD audio to play music, so if you don't own the original CD, you won't hear any music. But if you do own an optical drive, the game will play audio tracks from any mixed mode/audio CD at the appropriate cues.
