#include "election.h"
//include any other headers you need here...
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

/*This function is used to check if the string has the format "XXX:XXX:XXX" 
If the format is roght, modify the value i1,i2,len in parseline*/

int check_genral_format(const char * line,
                        size_t * index1,
                        size_t * index2,
                        size_t * length) {
  //check if the string is empty
  size_t len = 0;
  if ((len = strlen(line)) == 0) {
    printf("empty!\n");
    return EXIT_FAILURE;
  }

  //check the number of ':' and locate the first two ':'s
  int count = 0;
  size_t i1 = 0;
  size_t i2 = 0;

  for (size_t i = 0; i < len; i++) {
    if (line[i] == ':') {
      if (count == 0) {
        i1 = i;
      }
      if (count == 1) {
        i2 = i;
      }
      count += 1;
    }
  }
  if (count > 2) {
    printf("too many ':'!\n ");
    return EXIT_FAILURE;
  }

  if (count < 2) {
    printf("too few ':'!\n");
    return EXIT_FAILURE;
  }

  if (i1 >= 64) {
    printf("the first part is too long!\n");
    return EXIT_FAILURE;
  }

  //check if the first, seond, third part is empty
  if (i2 - i1 <= 1 || i1 == 0 || i2 == len - 1) {
    printf("missing content!\n");
    return EXIT_FAILURE;
  }

  *length = len;
  *index1 = i1;
  *index2 = i2;

  return EXIT_SUCCESS;
}

/*This funtion is used to check if the second and the third part of the
string only contain numbers*/

int check_num_format(const char * line, size_t i1, size_t i2, size_t len) {
  //check errors in the second part
  for (size_t j = i1 + 1; j < i2; j++) {
    if (j == i1 + 1 && line[j] == '0') {
      printf("the first number cannot be 0!\n");
      return EXIT_FAILURE;
    }

    if (!(isdigit(line[j]))) {
      printf("the second part contains wrong character!\n");
      return EXIT_FAILURE;
    }
  }

  //check errors in the thrid part
  for (size_t k = i2 + 1; k < len; k++) {
    if (k == i1 + 1 && line[k] == '0') {
      printf("the first number cannot be 0!\n");
      return EXIT_FAILURE;
    }

    if (!(isdigit(line[k]))) {
      printf("the third part contains wrong character!\n");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

/*This function is used to check if the number in the thrid part is too large
for the given type, if not, extract it */

int check_extract_ev(const char * line, size_t i2, size_t len, unsigned int * ev) {
  //start with 0?? test!
  //first, check if the number is longer than UINT32_MAX, if longer, then larger
  if ((len - 1 - i2 - 1) > 10) {
    printf("the third part number is too large!\n");
    return EXIT_FAILURE;
  }

  //if not, store it in a larger type (without overflow), and compare it to UINT32_MAX
  char * end2;
  uint64_t evt = 0;
  if ((evt = strtoul(line + i2 + 1, &end2, 10)) > UINT32_MAX) {
    printf("the third part number is too large!!\n");
    return EXIT_FAILURE;
  }

  *ev = evt;
  return EXIT_SUCCESS;
}

/*This function is used to check if the number in the thrid part is too large
for the given type, if not, extract it */

int check_extract_pop(const char * line, size_t i1, size_t i2, uint64_t * pop) {
  //check length
  if ((i2 - i1 - 1) > 20) {
    printf("the second part number is too large!\n");
    return EXIT_FAILURE;
  }

  //if length is equal to the length of UINT64_MAX save the most significant bit and
  //other bits separately, then determine if the number is larger than UINT64_MAX (18446744073709551615)
  char * end1;
  if ((i2 - i1 - 1) == 20) {
    char high[] = {"0"};
    uint64_t popt1 = 0;
    popt1 = strtoul(line + i1 + 2, &end1, 10);
    high[0] = line[i1 + 1];
    if (atoi(high) > 1) {
      printf("the second part is too large!!\n");
      return EXIT_FAILURE;
    }
    if (popt1 > 8446744073709551615) {
      printf("the second part is too large!!!\n");
      return EXIT_FAILURE;
    }
  }

  *pop = strtoul(line + i1 + 1, &end1, 10);
  return EXIT_SUCCESS;
}

state_t parseLine(const char * line) {
  //STEP 1: write me
  size_t i1 = 0;
  size_t i2 = 0;
  size_t len = 0;

  if (check_genral_format(line, &i1, &i2, &len)) {
    exit(EXIT_FAILURE);
  }

  if (check_num_format(line, i1, i2, len)) {
    exit(EXIT_FAILURE);
  }

  state_t st;

  //load state name
  for (size_t k = 0; k < i1; k++) {
    st.name[k] = line[k];
  }

  //add '\0' at the end, to initialize unsued space
  st.name[i1] = '\0';

  //load population and eletoral votes
  uint64_t pop = 0;
  unsigned int ev = 0;

  if (check_extract_ev(line, i2, len, &ev)) {
    exit(EXIT_FAILURE);
  }

  if (check_extract_pop(line, i1, i2, &pop)) {
    exit(EXIT_FAILURE);
  }

  st.population = pop;
  st.electoralVotes = ev;

  return st;
}

/*This function is used to count the percentage of vote for each state
and check if the votecount is valid*/

double countpercent(state_t state, uint64_t votecount, double * percent) {
  double all = 0.0;
  double vote = 0.0;
  all = state.population;
  vote = votecount;

  if (votecount < 0 || votecount > state.population) {
    printf("invalid vote counts!\n");
    return EXIT_FAILURE;
  }
  *percent = vote / all;
  return EXIT_SUCCESS;
}

unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  //STEP 2: write me
  unsigned int sum = 0;
  double percent = 0.0;

  for (size_t i = 0; i < nStates; i++) {
    //save the percent of vaote in percent, if error occurs in countpercent, exit
    if (countpercent(stateData[i], voteCounts[i], &percent)) {
      exit(EXIT_FAILURE);
    }
    if (percent > 0.5) {
      sum += stateData[i].electoralVotes;
    }
  }

  return sum;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  double percent = 0.0;

  for (size_t i = 0; i < nStates; i++) {
    //save the percent of vaote in percent, if error occurs in countpercent, exit
    if (countpercent(stateData[i], voteCounts[i], &percent)) {
      exit(EXIT_FAILURE);
    }

    if (percent >= 0.495 && percent <= 0.505) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             percent * 100);
    }
    percent = 0.0;
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  double percent = 0.0;
  double max = 0.0;
  size_t maxindex = 0;

  for (size_t i = 0; i < nStates; i++) {
    //save the percent of vaote in percent, if error occurs in countpercent, exit
    if (countpercent(stateData[i], voteCounts[i], &percent)) {
      exit(EXIT_FAILURE);
    }

    //if percent > 50% and no need for recount, win, then compare which is largest
    if (percent > 0.505) {
      if (percent > max) {
        max = percent;
        maxindex = i;
      }
    }
  }

  if (max == 0.0 && maxindex == 0) {
    printf("Sadly, our candidate doesn't win any state...\n");
  }
  else {
    printf("Candidate A won %s with %.2f%% of the vote\n",
           stateData[maxindex].name,
           max * 100);
  }
}
