# COEN 177 Operating Systems Final Review

## Memory - Memory Management

    Page Replacement Algorithms
      - How do you choose what to remove from memory?
      - Handle TLB misses

      Optimal
        - Replace the page that will be used furthest in the future
        - Not possible
        - Requires foresight

      Not Recently Used
        - Reference and dirty bit
          - 0 not referenced; not dirty
          - 1 not referenced; dirty
          - 2 referenced; not dirty
          - 3 referenced; dirty
        - Clear bits periodically
        - Remove a page from the lowest non-empty class

      Fifo
        - Maintain linked list of pages
        - Page at front replaced
        - Fast
        - But page in memmory may be used often

      Second Chance
        - FIFO, but throw out unused pages
        - Reference bit
          - 0 unreferenced
          - 1 referenced
          - Can start at 0 or 1

        - Work through list, mark all you go through as unreferenced until you reach an already unreferenced. Evict the unreferenced

      Clock
        - Same functionality as Second Chance
        - Clock hand points to current page
        - Advance hand looking for unreferenced page

      Least Recently Used
        - Keep order in the list
        - Move a page to the front when referenced
        - Evict from the rear

      Aging
        - Counter keeps track of age
        - Decrement every so often
        - Remove lowest counter value
        - On tick, shift all counters right 1 bit
        - On reference, set leftmost bit to 1

      Belady's Anomaly
        - Symptom: adding more memory resulted in more faults
        - FIFO

      Local vs. Global allocation policies
        - What is the pool o fpages eligible to be replaced?
          - Pages belonging to the process needing a new page
          - All pages in the system
        - Local allocation: replace a page from this process
          - may be more "fair": penalize processes that replace many pages
          - can lead to poor performance: some processes need more pages than others
        - Global allocation: replace a page from any process

      Page fault rate vs. Allocated frames
        - Local allocation may be more "fair"
          - don't penalize other processes for high page fault rate
        - Global allocation is better for overall system performance
          - Take page frames from processes that don't need them as much
          - Reduce the overall page fault rate (even though rate for a single process may go)

      Control overall page fault rate
        - Despite good designs, system may still thrash
        - Most (or all) processes have high page fault rate
          - Some processes need more memory
          - But no processes need less memory (and could give some up)
        - Problem: now way to reduce page fault rate
          - Solution
            - Reduce number of processes competing for memory
            - Swap one or more to disk, ddivide up pages they held
            - reconsider degree of multiprogramming

      How big should a page be?
        - Smaller pages have advantages
          - Less internal fragmentation
          - Better fit for various data structures, code sections
          - Less unused physical memory (some pages have 20 useful bytes and the rest isn't needed currently)
        - Larger pages are better because
          - Less overhead to keep track of them
            - Smaller page tables
            - TLB can point to more memory (same number of pages, but more memory per page)
            - Faster paging algorithms (fewer table entries to look through)
          - More efficient

## I/O

    Goals
      - Device independence
      - Uniform naming
      - Error handling
      - Synchronous vs. asynchronous transfers
      - Buffering
      - Sharable vs dedicated drives

    I/O using DMA
      - code run by system call
      - code run at interrupt time -> efficient

## Filesytems

## Security

## Review Session

    RAID
        - Not always redundant or reliable
        - Parity, striping
        - RAID 4 has parity calculation so that you can recover data -> parity of remainder
        - Sometimes for performance, don't read/write to the same disk all the time

    Files
        - Memory mapped I/O
            - No difference in storage/how it looks
            - Changes how you open/access it
        - Update in memory
            - Will have to writeback
            - Changes need to propogate from file cache to disk
        - The lie of virtual memory is helpful here
