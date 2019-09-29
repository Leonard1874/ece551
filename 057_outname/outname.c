#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * outputName = malloc((strlen(inputName) + 7 + 1) * sizeof(*outputName));
  strcpy(outputName, inputName);
  strcat(outputName, ".counts");
  return outputName;
}
