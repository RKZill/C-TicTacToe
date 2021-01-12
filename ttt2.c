#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>
int findmin(struct BoardNode node );
int findmax(struct BoardNode node );
void init_boards(){
  int i;
  for (i=0;i<=HSIZE;i++){ //initalize the board of size hsize
    htable[i].init = 0; //set to 0
  }
}

int depth(Board board){ // finds how many peices are played
  int i; // loop var
  int count=0; //count
  for (i=0;i<9;i++){ //loops through ll possibel locations
    if (board[pos2idx[i]]=='X'||board[pos2idx[i]]=='O'){ //if occupied
      count++; //increase count
    }
  }
  return count; //return count
}

char winner(Board board){ //finds the winner
  int n=0;
  int m=0;
  int i;
  int j;
  for (i=0;i<=7;i++){ //loop to go through all 8 win conditions
    n=0;
    m=0;
    for (j=0;j<=2;j++){ //going though each wi condition
      if (board[pos2idx[WINS[i][j]]]=='X'){ //check for math in wins array
        n++; //if found, add 1 to n
      }
      if (board[pos2idx[WINS[i][j]]]=='O'){ //same thing for O
        m++;
      }
    }
    if (n==3){ //if 3 X'sn in a row, x wins
      return 'X';
    }
    if (m==3){ //if 3 os, O wins
      return 'O';
    }
  }
  n=0;
  for (i=0;i<9;i++){ //loop through
    if (board[pos2idx[i]]>='0'&&board[pos2idx[i]]<='9'){ //if non occupied space
      return '?'; //return a ?
      n++;
    }


  }

  return '-'; //if no other conditions are met it must be a tie
}

char turn(Board board){
  int i;
  int n=0;
  if (winner(board)=='X'||winner(board)=='O'||winner(board)=='-'){ //if winner, no more turns
    return '-';
  }
  for (i=0;i<=8;i++){ //count the number of peices on board
    if (board[pos2idx[i]]=='X'||board[pos2idx[i]]=='O'){
      n++;
    }
  }
  if (n==9){ //if 9, and no winner, its a tie
    return '-';
  }
  if (depth(board)%2==0){ //x goes first
    return 'X';
  }
  else{
    return 'O'; //o goes second
  }
}

void init_board(Board board){ //init voard

  int hashidx = board_hash(board); //find hash val

  htable[hashidx].init  = 1; //set to 1

  htable[hashidx].turn  = turn(board); //bla bla bla initaizes everything

  htable[hashidx].depth = depth(board);

  strcpy(htable[hashidx].board , board);

  htable[hashidx].winner = winner(board);

}

void compute_score(){ //find score

  /*
  for (i=0;i<HSIZE;i++){ //find score for each node
    if (htable[i].init==1){ //but only if its initalized
      if (winner(htable[i].board)=='X'){ //x wins
        htable[i].score=1;
      }
      else if (winner(htable[i].board)=='O'){ //no
        htable[i].score=-1;
      }
      else if (winner(htable[i].board)=='-'){ //tie
        htable[i].score=0;
      }
      if (turn(htable[i].board)=='X'){ //if it is x's turn
        temp = 0; //
        for (j=9;j>=0;j--){ //i dont know why we have to count down
          if (htable[i].move[j]>temp){ //but we do
            temp=htable[i].move[j];
          }
        }
        htable[i].score=temp; //temp is temp is temp is not temp? maybe. but maybe not.
      }
      if (turn(htable[i].board)=='O'){ //same as above
        temp = 99999999;
        for (j=9;j>=0;j--){
          if (htable[i].move[j]<temp&&htable[i].move[j]!=-1){ //dont incude the invalid bpoards
            temp=htable[i].move[j];
          }
        }
        htable[i].score=temp; //make it equal to temp
      }
    }
  }
  */
  int i;
  int temp;
  int num=0;
  for (i=HSIZE;i>=0;i--){
    if (htable[i].init==1){

      if (winner(htable[i].board)=='X'){ //x wins
        htable[i].score=1;
      }
      else if (htable[i].depth==0){
        htable[i].score=0;
      }
      else if (winner(htable[i].board)=='O'){ //o wins
        htable[i].score=-1;
      }
      else if (winner(htable[i].board)=='-'){ //tie
        htable[i].score=0;
      }
      else if (turn(htable[i].board)=='X'){
        temp = -1;
          num = findmax(htable[i]);
          if (temp<num){
            temp=num;
          }
          htable[i].score=temp;
        }


      else if (turn(htable[i].board)=='O'){
        temp=2;
          num = findmin(htable[i]);
          if (num<temp){
            temp=num;
          }

        htable[i].score=temp;
      }

    }
  }
}

int findmax(struct BoardNode node ){
  int j=0;
  int i;
  if (j==0){};
  if (node.winner=='X'){
    return 1;
  }

    if (node.winner=='O'){
      return -1;
    }
    if (node.winner=='-'){
      return 0;
    }

    for (i=0;i<9;i++){
      struct BoardNode child = htable[node.move[i]];
      if (child.init==1){
        if (child.winner=='?'){
          j = findmax(child);
        }
        else if (child.winner=='X'){
          return 1;
        }
      }
    }

  return 0;
}
int findmin(struct BoardNode node ){
  int j=0;
  int i;
  if (j==0){}

  if (node.winner=='O'){
    return -1;
  }
  if (node.winner=='X'){
    return 1;
  }
  if (node.winner=='-'){
    return 0;
  }

  for (i=0;i<9;i++){
    struct BoardNode child = htable[node.move[i]];
    if (child.init==1){
      if (child.winner=='?'){
        j = findmin(child);
      }
      else if (child.winner=='O'){
        return -1;
      }
    }
  }

  return 0;
}

int best_move(int board){ //THE BEST MOVES MONEY CAN BUY FOR ONLY 6.99$ + tax!
  int j;
  int temp;
  Board copy; //make a copy to use as the board
  strcpy(copy,htable[board].board);
  /*
  for (i=0;i<9;i++){
    if (copy[pos2idx[i]]!='X'&&copy[pos2idx[i]]!='O'){
      return i;
    }
  }
  */

  if (turn(copy) == 'X'){ //if x turn
    temp = 0; //temp is 0
    for (j=8;j>=0;j--){ //loop through array of moves
      int cur = htable[board].move[j]; //make current node
      if (cur!=-1){ //if current node is valid
        if (htable[cur].score>temp){
          temp = htable[cur].score; //make temp the score
        }
      }
    }
    for (j=8;j>=0;j--){ //loop through again
      int cur = htable[board].move[j]; //another current node
      if (cur!=-1){
        if (htable[cur].score == temp){ //if the score exist in one fo these nodes return that position
          return j;
        }
      }
    }
  }

  if (turn(copy) == 'O'){ //exact same for 0
    temp = 999999;
    for (j=8;j>=0;j--){ //we set temp high because we wnt to look for the smaller values
      int cur = htable[board].move[j];
      if (cur!=-1){ //yeah
        if (htable[cur].score<temp){ //exact same but flip the >
          temp = htable[cur].score;
        }
      }
    }
    for (j=8;j>=0;j--){ //haha
      int cur = htable[board].move[j];
      if (cur!=-1){ //woah
        if (htable[cur].score == temp){ //hehehe
          return j;
        }
      }
    }
  }
  return 1; //reutrn a 1 as a failsafe lets PRAY it never gets to this point cuz it will surely most definitely mess things up
}

void join_graph(Board board){ //joins grapbhs
  int i=0;
  if (winner(board)=='X'||winner(board)=='O'){ //if theres a winner dont join nything{
    return;
  }
  int hashidx = board_hash(board); //find hash id

  for (i=0;i<9;i++){ //loop through entire moves
    if (board[pos2idx[i]]=='X'||board[pos2idx[i]] =='O'){
      htable[hashidx].move[i] = -1; //make move illegal if there is something in its spot
    }
    else{ //if not illegal
      Board copy; //make copy
      strcpy(copy,board);
      copy[pos2idx[i]] = turn(board); //copy turn
      int newHashidx = board_hash(copy); //make new hash index
      htable[hashidx].move[i] = newHashidx; //put that into move
      if (htable[newHashidx].init!=0){ //if it is occupied move to next spot
      }
      else{ //if not initalize the board and recursively call joingraphs
        init_board(copy); //////hehe
        join_graph(copy);
      }

    }
  }
}
