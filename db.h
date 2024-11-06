#ifndef DB_H
#define DB_H

typedef enum {
  CD_CHECK,
  TIMEBOMB
} PatchType;
extern const char *patchTypes[];

typedef struct {
  const char *name;
  int buildNumber;
  int filesize;
  int checksum;
  PatchType patchTypeIndex;
  int offset;
  unsigned char oldByte;
  unsigned char newByte;
} Database;
extern const Database patches[];
extern const int patchesCount;

#endif
