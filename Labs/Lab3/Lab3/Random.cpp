
/*
Matthew Koken
COEN 177 Lab 3
Second Chance Algorithm (Like CLOCK) WITH A RANDOM TWIST.
This algorithm gives uses a reference bit to see if a page
has been recently used. If there is room, the page will be added to the head with a reference bit of 1. If there
is no room, the algorithm will look for an unreferenced page. AT A RANDOM SPOT,
marking any it passes by to 0 unless it finds one already at 0. In that case, the
marked page will be removed and the new page will be added in its place. Starts with
no chances, and given a chance if it is referenced again after initial insertion.

This version of second chance uses start at 1 in contrast to the other, which
uses start at 0.
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

struct Page {
  int pageNum;
  int chances;
};


int main (int argc, char *argv[]) {
  if(argc < 2) {
      printf("ERROR: NOT ENOUGH PARAMETERS");
      return 1;
  }

  /* initialize random seed: */
  srand (time(NULL));

  //use a deque to store the cache
  deque<Page> deck;

  int pageFaults = 0;
  int cacheSize = atoi(argv[1]);
  deck.resize(cacheSize);
  char str[255]; //character read buffer
  int numRead = 0;
  int num;
  int dCurSize = 0;
  int hand = -1;

  //reset the deck
  Page dummyPage;
  dummyPage.chances=0;
  dummyPage.pageNum=-1;
  for(int i = 0; i < cacheSize; i++) {
    deck.push_front(dummyPage);
  }


  while(fgets(str, sizeof(str), stdin)) { //read until EOF
      if(!(isdigit((int)(str[0])))) //only take numbers
		    continue;

      numRead++; //Read a line, increment number of lines read

      sscanf(str, "%d", &num); //scan in a num
	    {
          //check if the page is in the cache
          int index=-1;
          for(int i = 0; i < dCurSize; i++) {
              if(deck[i].pageNum == num) {
                  index = i;
                  break;
              }
          }

          Page n;
          n.pageNum = num;
          n.chances = 1;

          if(index!=-1) {
              //page is in cache, so make sure it has a second chance
              deck[index].chances=1;
          } else {
              //else the page is not in the cache
              //WE HAD A PAGE FAULT! IT"S THE END OF THE WORLD!

              pageFaults++;
              //Page Fault:
              cerr<< num << endl;

              //if there is room, add to the head
              if(dCurSize<cacheSize) {
                  //there's room, add to the head
                  deck.push_front(n);
                  dCurSize++;
                  //make sure to keep track of size
              } else {
              //else there is no room
                //now find room
                int lastChanceIndex = -1;
                bool done = false;
                while(!done) {
                  //give them a chance
                  if(deck[hand].chances==1) {
                    deck[hand].chances--;
                  } else {
                    //this index has no remaining chances, it will be purged
                    deck.erase(deck.begin() + hand);
                    deck.insert(deck.begin() + hand, n);
                    done = true;
                  }
                }
              }
          }
          //Set a new radom hand location
          hand = rand() % dCurSize;
	    }

  }
  //Total pages read:
  cout << numRead << endl;
  //Total page faults:
  cout << pageFaults << endl;
  return 0;
}
