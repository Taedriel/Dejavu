#ifndef FOLLOW_LINE_H
#define FOLLOW_LINE_H

/**
 * Position on a map (integer coordinates)
 */
typedef struct {
  int x;
  int y;
} Pos2Dint;

/**
 * Position with floating point coordinates
 */
typedef struct {
  float x;
  float y;
} Pos2Dfloat;

/**
 * Dicrete line traversal information
 */
typedef struct {
  Pos2Dint start;
  Pos2Dint end;
  Pos2Dfloat currentPosition;
  Pos2Dfloat delta; /*< Shift vector */
  int len;          /*< Length along the main axis */
  int pos;          /*< Reference position on the line */
} InfoLine;

/**
 * Initialize an InfoLine data structure
 */
void initLine(int x1, int y1, int x2, int y2, InfoLine * infoLine);

/**
 * @brief nextPoint Move a point along a line in one direction
 *
 * @param infoLine Line traversal information
 * @param point current/next position
 * @param direction (+1 forward, -1 backward)
 * @return 1 if point is a new point in the line, otherwise -1 (info is
 *         already at the end point)
 */
int nextPoint(InfoLine * infoLine, Pos2Dint * point, int direction);

#endif
