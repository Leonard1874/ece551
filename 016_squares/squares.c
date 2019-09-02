int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

int check(int x, int y, int b1, int b2, int e1, int e2) {
  int res = 0;
  int a = 0;
  int b = 0;
  if (x >= b1 && x < b2) {
    a = 1;
  }
  if (y == e1 || y == e2) {
    b = 1;
  }
  res = a & b;
  return res;
}

int check2(int x, int y, int l, int e1, int e2) {
  int res = 0;
  int a = 0;
  int b = 0;
  if (x < l) {
    a = 1;
  }
  if (y == e1 || y == e2) {
    b = 1;
  }
  res = a & b;
  return res;
}

void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, (x_offset + size2));
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, (y_offset + size2));
  //count from 0 to h. Call the number you count with y
  for (int y = 0; y < h; y++) {
    //count from 0 to w. Call the number you count with x
    for (int x = 0; x < w; x++) {
      int i = 0;
      int j = 0;
      //check if  EITHER
      //    ((x is between x_offset  and x_offset +size2) AND
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      //  OR
      //    ((y is between y_offset and y_offset + size2) AND
      //     x is equal to either x_offset OR x_offset + size2 -1)
      i = check(x, y, x_offset, (x_offset + size2), y_offset, (y_offset + size2 - 1));
      j = check(y, x, y_offset, (y_offset + size2), x_offset, (x_offset + size2 - 1));
      // if so, print a *
      if (i == 1 || j == 1) {
        printf("*");
      }
      //if not,
      else {
        i = 0;
        j = 0;
        // check if EITHER
        //    x is less than size1 AND (y is either 0 or size1-1)
        // OR
        //    y is less than size1 AND (x is either 0 or size1-1)
        i = check2(x, y, size1, 0, (size1 - 1));
        j = check2(y, x, size1, 0, (size1 - 1));
        //if so, print a #
        if (i == 1 || j == 1) {
          printf("#");
        }
        //else print a space
        else {
          printf(" ");
        }
        //when you finish counting x from 0 to w,
      }
    }
    //print a newline
    printf("\n");
  }
}
