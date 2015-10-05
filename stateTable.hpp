#pragma once

#include <map>

#define STATE_TABLE_HEIGHT            24
#define STATE_TABLE_WIDTH             32

enum FinalState {
  fsStr = 1000, fsVar, fsInt1, fsHex, fsLim1, fsOp1, fsOp2,
  fsOp3, fsLim2, fsComment1, fsInt2, fsChar, fsComment2, fsReal1, fsReal2,
  fsBadCC, fsNoCC, fsNoHex, fsNoFract, fsNoExp, fsBadChar, fsBadEOF,
  fsBadNL, fsUnexpEOF
};

enum FinalStateType {
  fstError, fstUnexpEOF, fstStr, fstVar, fstInt, fstHex, fstLim, fstOp,
  fstComment, fstChar, fstReal
};

extern int stateTable[STATE_TABLE_HEIGHT][STATE_TABLE_WIDTH];
extern std::map<int, int> charMap;
extern std::map<int, std::pair<int, int>> finalStateMap;