#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv){
  init_boards();
  init_board(START_BOARD);
  join_graph(START_BOARD);
  compute_score();

  int i;
  for (i=1;i<argc;i++){
    if (!isdigit(*argv[i])){
      fprintf(stderr, "Error, you have entered a non integer for the command line arguments\n");
      return 0;
    }
  }


  for (i=1;i<argc;i++){
    print_node(htable[ strtoll(argv[i] ,NULL , 10 ) ] );
  }
}
