#include "election.h"
//include any other headers you need here...
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

int checkerror(const char * line, size_t * index1, size_t * index2) {
  size_t len = 0;
  if ((len = strlen(line)) == 0) {
    printf("empty!\n");
    return 0;
  }

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
    return 0;
  }

  if (count < 2) {
    printf("too few ':'!\n");
    return 0;
  }

  if (i1 >= 64) {
    printf("the first part is too long!\n");
    return 0;
  }

  //check erros in the content of the first part
  if (i2 - i1 <= 1 || i1 == 0 || i2 == len - 1) {
    printf("missing content!\n");
    return 0;
  }

  /*
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
  */

  *index1 = i1;
  *index2 = i2;

  //check errors in the second part
  for (size_t j = i1 + 1; j < i2; j++) {
    if (!(isdigit(line[j]))) {
      printf("the second part contains wrong character!\n");
      return 0;
    }
  }
  for (size_t k = i2 + 1; k < len; k++) {
    if (!(isdigit(line[k]))) {
      printf("the third part contains wrong character!\n");
      return 0;
    }
  }

  return 1;
}

int extractnums(const char * line,
                size_t i1,
                size_t i2,
                uint64_t * pop,
                unsigned int * ev) {
  size_t len = strlen(line);

  if ((len - 1 - i2 - 1) > 10) {
    printf("the third part number is too large!\n");
    return 0;
  }

  char * end2;
  uint64_t evt = 0;
  if ((evt = strtoul(line + i2 + 1, &end2, 10)) > UINT32_MAX) {
    printf("the third part number is too large!!\n");
    return 0;
  }

  *ev = evt;

  if ((i2 - i1 - 1) > 20) {
    printf("the second part number is too large!\n");
    return 0;
  }

  char * end1;
  uint64_t popt = strtoul(line + i1 + 1, &end1, 10);
  if ((i2 - i1 - 1) == 20) {
    char high[] = {"0"};
    uint64_t popt1 = 0;
    popt1 = strtoul(line + i1 + 2, &end1, 10);
    high[0] = line[i1 + 1];
    if (atoi(high) > 1) {
      printf("the second part is too large!!\n");
      return 0;
    }
    if (popt1 > 8446744073709551615) {
      printf("the second part is too large!!!\n");
      return 0;
    }
  }
  *pop = popt;

  return 1;
}

state_t parseLine(const char * line) {
  //STEP 1: write me
  size_t i1 = 0;
  size_t i2 = 0;
  size_t * index1 = &i1;
  size_t * index2 = &i2;

  if (!checkerror(line, index1, index2)) {
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
  uint64_t * popp = &pop;
  unsigned int ev = 0;
  unsigned int * evp = &ev;

  if (!extractnums(line, i1, i2, popp, evp)) {
    exit(EXIT_FAILURE);
  }

  st.population = pop;
  st.electoralVotes = ev;

  return st;
}

//counting the percentage of vote
double countpercent(state_t state, uint64_t votecount) {
  double all = 0.0;
  double vote = 0.0;
  double percent = 0.0;
  all = state.population;
  vote = votecount;
  // printf("%ld, %f\n", votecount, vote);
  //check if 0 <= vote <= population
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
    //save the percent of vaote in percent, if error occurs in countpercent, exit
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
    //save the percent of vaote in percent, if error occurs in countpercent, exit
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
    //save the percent of vaote in percent, if error occurs in countpercent, exit
    if ((percent = countpercent(stateData[i], voteCounts[i])) < 0) {
      exit(EXIT_FAILURE);
    }

    //if percent > 50% and no need for recount, win
    if (percent > 0.505) {
      printf("Candidate A won %s with %.2f%% of the vote\n",
             stateData[i].name,
             percent * 100);
    }
    percent = 0.0;
  }
  return;
}
