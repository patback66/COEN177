/*
Matthew Koken
COEN 177 Lab 3
LRU

The deque (deck) holds all the pages. When a page is requested, if the
page is found, it is removed from the deck and pushed to the front (most recently used)
If it is not found in the deck, this is a page fault and it needs to be added.
If there is room, it can immediately be pushed to the front. If there is no room,
the back is popped (least recently used removed) and the page is pushed to the front.
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdlib.h>
#include <deque>
#include <ctype.h>
#include <iostream>
#include <cerrno>
#include <err.h>
#include <error.h>

using namespace std;


int main (int argc, char *argv[]) {
  if(argc < 2) {
      printf("ERROR: NOT ENOUGH PARAMETERS");
      return 1;
  }

  //use a deque to store the cache
  deque<int> deck;

  int pageFaults = 0;
  int cacheSize = atoi(argv[1]);
  deck.resize(cacheSize);
  char str[255]; //character read buffer
  int numRead = 0;
  int num;
  int dCurSize = 0;


  while(fgets(str, sizeof(str), stdin)) { //read until EOF
      if(!(isdigit((int)(str[0])))) //only take numbers
		    continue;

      numRead++; //Read a line, increment number of lines read

      sscanf(str, "%d", &num); //scan in a num
	    {
          //check if the page is in the cache
          int index=-1;
          for(int i = 0; i < dCurSize; i++) {
              if(deck[i] == num) {
                  index = i;
                  break;
              }
          }


          if(index!=-1) {
              //page is in cache, so move to head (most recently used)
              deck.erase(deck.begin() + index);
              deck.push_front(num);
          } else {
              //else the page is not in the cache
              //WE HAD A PAGE FAULT! IT"S THE END OF THE WORLD!

              pageFaults++;
              //Page Fault:
              cerr<< num << endl;

              //if there is room, add to head
              if(dCurSize<cacheSize) {
                  //there's room, add to the head
                  deck.push_front(num);
                  dCurSize++;
                  //make sure to keep track of size
              } else {
              //else there is no room
                  //pop from the back
                  //add to the head
                  deck.pop_back();
                  deck.push_front(num);
                  //deque size doesn't change so don't care about incrementing size
              }
          }
	}

  }
  //Total pages read:
  cout << numRead << endl;
  //Total page faults:
  cout << pageFaults << endl;
  return 0;
}
