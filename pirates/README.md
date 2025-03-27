Pirate Latitudes: Ultimate Curses Enhanced Epic Adventure with ASCII Movies, Extended UI, and Unit Tests
Inspired by *Pirate Latitudes* by Michael Crichton.
All rights to the original text and story belong to Michael Crichton and his estate.

This version uses curses to provide:
  - A full-screen ASCII intro movie.
  - A full-screen main menu using stdscr.
  - A multi-panel UI (header, main, sidebar, input, footer) for gameplay.
  - A cancellable ASCII ending movie.
  - Auto-complete of dialog animations if any key is pressed.
  
It also includes a unit test suite that verifies (for example) that the command parser
and journal functions work as expected.

Usage:
    python3 pirates.py        # to run the game
    python3 pirates.py test   # to run the unit tests
