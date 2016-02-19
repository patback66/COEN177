
/*
Matthew Koken
COEN 177 Lab 3
LFU
The least frequently used algorithm keeps track of the usage of a page.
When a page is referenced, the reference bit for it's number of uses is incremented.
When the cache is full, the algorithm seeks out the page with the lowest number of uses to remove.
When a page is referenced again, it is moved to the head and its number of uses is incremented.
This keeps an order of most recently used. If two pages have the same number of uses, the least recently used will be purged.
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

#define MAXINT 2147483647

using namespace std;

struct Page {
  int pageNum;
  int uses;
};


int main (int argc, char *argv[]) {
  if(argc < 2) {
      printf("ERROR: NOT ENOUGH PARAMETERS");
      return 1;
  }

  //use a deque to store the cache
  deque<Page> deck;

  int pageFaults = 0;
  int cacheSize = atoi(argv[1]);
  deck.resize(cacheSize);
  char str[255]; //character read buffer
  int numRead = 0;
  int num;
  int dCurSize = 0;

  //reset the deck
  Page dummyPage;
  dummyPage.uses=0;
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
          n.uses = 1;

          if(index!=-1) {
              //page is in cache, so update its uses, move to front
              n.uses=deck[index].uses+1;
              deck.erase(deck.begin() + index);
              deck.push_front(n); //keep most recent use order to break ties
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
                int leastUsedIndex = -1;
                int minUse = MAXINT;
                for(int i = 0; i < dCurSize; i++) {
                  //check for the min used. The highest index (LRU) determines ties
                  if(deck[i].uses<=minUse) {
                    //update index, least uses
                    leastUsedIndex = i;
                    minUse = deck[i].uses;
                  }
                }
                //remove the LFU
                deck.erase(deck.begin() + leastUsedIndex);
                //add to the front
                deck.push_front(n);
              }
          }
	    }

  }
  //Total pages read:
  cout << numRead << endl;
  //Total page faults:
  cerr << pageFaults << endl;
  return 0;
}
