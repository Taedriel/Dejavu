#include "follow_line.h"


void initLine(int x1, int y1, int x2, int y2, InfoLine * infoLine)
{
  int adxi, adyi, dxi, dyi;
  infoLine->start.x = x1;
  infoLine->start.y = y1;
  infoLine->currentPosition.x = x1 + 0.5;
  infoLine->currentPosition.y = y1 + 0.5;
  infoLine->end.x = x2;
  infoLine->end.y = y2;

  adxi = dxi = x2 - x1;
  adyi = dyi = y2 - y1;
  if (adxi < 0)  {
    adxi = -dxi;
  }
  if (adyi < 0) {
    adyi = -dyi;
  }
  infoLine->pos = 0;
  infoLine->len = adxi;
  if (adyi > adxi) {
    infoLine->len = adyi;
  }
  infoLine->delta.x = ((float)dxi) / infoLine->len;
  infoLine->delta.y = ((float)dyi) / infoLine->len;
}

int nextPoint(InfoLine * infoLine, Pos2Dint * point, int direction)
{
  if (direction > 0) {
    if (infoLine->pos == infoLine->len) {
      point->x = infoLine->end.x;
      point->y = infoLine->end.y;
      return -1; /* End of the line */
    }
    infoLine->currentPosition.x += infoLine->delta.x;
    infoLine->currentPosition.y += infoLine->delta.y;
    point->x = ((int)infoLine->currentPosition.x);
    point->y = ((int)infoLine->currentPosition.y);
    infoLine->pos++;
    return 1;   /* a new point is found */
  }
  if (direction < 0) {
    if (infoLine->pos == 0) {
      point->x = infoLine->start.x;
      point->y = infoLine->start.y;
      return -1; /* End of the line */
    }
    infoLine->currentPosition.x -= infoLine->delta.x;
    infoLine->currentPosition.y -= infoLine->delta.y;
    point->x = ((int)infoLine->currentPosition.x);
    point->y = ((int)infoLine->currentPosition.y);
    infoLine->pos--;

    return 1; /* a new point is found */
  }
  return 1; /* direction == 0 => no motion */
}

