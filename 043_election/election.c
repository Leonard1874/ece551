#include "election.h"
//include any other headers you need here...
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

int checkerror(const char * line, int i1, int i2, int len) {
  if (i2 - i1 <= 1 || i1 == 0 || i2 == len - 1) {
    printf("missing content!\n");
    return 0;
  }

  int countspc = 0;

  if (isspace(line[0]) || isspace(line[i1 - 1])) {
    printf("the first/last letter of the first part cannot be space!");
    return 0;
  }

  for (int j1 = 0; j1 < i1; j1++) {
    if (!(isspace(line[j1])) && !(isalpha(line[j1]))) {
      printf("the first part contains wrong character!\n");
      return 0;
    }

    else {
      if (isspace(line[j1])) {
        countspc++;
      }
    }
  }
  if (countspc == i1) {
    printf("the first part only has space!\n");
    return 0;
  }

  for (int j2 = i1 + 1; j2 < i2; j2++) {
    if (!(isdigit(line[j2]))) {
      printf("the second part contains wrong character!\n");
      return 0;
    }
  }
  for (int j3 = i2 + 1; j3 < len; j3++) {
    if (!(isdigit(line[j3]))) {
      printf("the third part contains wrong character!\n");
      return 0;
    }
  }
  if (atoi(line + i1 + 1) <= 0) {
    printf("the second part's number is too small!\n");
    return 0;
  }

  if (atoi(line + i2 + 1) <= 0) {
    printf("the third part's number is too small!\n");
    return 0;
  }
  //???
  // if(atoi(line + i2 +1) > UINT_MAX)
  // is(atoi(line + i1 +1) > INT_MAX)
  return 1;
}

state_t parseLine(const char * line) {
  //STEP 1: write me
  //if line is empty, error
  int len = 0;
  if ((len = strlen(line)) == 0) {
    printf("empty!\n");
    exit(EXIT_FAILURE);
  }
  //if there are more or less than 2 ':', error
  //get the indexes of two ':', save in in1, in2
  int i1 = 0;
  int i2 = 0;
  int count = 0;
  for (int i = 0; i < len; i++) {
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
    exit(EXIT_FAILURE);
  }

  if (count < 2) {
    printf("too few ':'!\n");
    exit(EXIT_FAILURE);
  }

  if (i1 >= 64) {
    printf("the first part is too long!\n");
    exit(EXIT_FAILURE);
  }

  //check other errors
  if (!(checkerror(line, i1, i2, len))) {
    exit(EXIT_FAILURE);
  }

  state_t st;

  /* for (int j = 0; j < MAX_STATE_NAME_LENGTH; j++) {
    st.name[j] = '0';
  }*/

  //load state name
  for (int k = 0; k < i1; k++) {
    st.name[k] = line[k];
  }

  st.name[i1] = '\0';

  //load population

  uint64_t pop = atoi(line + i1 + 1);
  st.population = pop;

  //load electoralvotes

  unsigned int ev = atoi(line + i2 + 1);
  st.electoralVotes = ev;

  return st;
}

double countpercent(state_t state, uint64_t votecount) {
  double all = 0.0;
  double vote = 0.0;
  double percent = 0.0;
  all = state.population;
  vote = votecount;
  // printf("%ld, %f\n", votecount, vote);
  if (vote > all || vote < 0 || votecount < 0 || votecount > state.population) {
    printf("invalid vote counts!\n");
    return -1;
  }
  percent = vote / all;
  return percent;
}

unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  //STEP 2: write me

  unsigned int sum = 0;
  double percent = 0.0;
  for (size_t i = 0; i < nStates; i++) {
    if ((percent = countpercent(stateData[i], voteCounts[i])) < 0) {
      exit(EXIT_FAILURE);
    }
    /* printf("for %s : %ld / %ld = %f\n",
           stateData[i].name,
           voteCounts[i],
           stateData[i].population,
           percent); */
    if (percent > 0.5) {
      sum += stateData[i].electoralVotes;
    }
    percent = 0.0;
  }

  return sum;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  double percent = 0.0;

  for (size_t i = 0; i < nStates; i++) {
    if ((percent = countpercent(stateData[i], voteCounts[i])) < 0) {
      exit(EXIT_FAILURE);
    }
    if (percent >= 0.495 && percent <= 0.505) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             percent * 100);
    }
    percent = 0.0;
  }

  return;
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  double percent = 0.0;

  for (size_t i = 0; i < nStates; i++) {
    if ((percent = countpercent(stateData[i], voteCounts[i])) < 0) {
      exit(EXIT_FAILURE);
    }
    if (percent > 0.505) {
      printf("Candidate A won %s with %.2f%% of the vote\n",
             stateData[i].name,
             percent * 100);
    }
    percent = 0.0;
  }
}
