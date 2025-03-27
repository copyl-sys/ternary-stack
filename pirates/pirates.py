#!/usr/bin/env python3
"""
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
"""

import curses
import time
import json
import os
import random
import re
import sys
import signal
import unittest

SAVE_FILE = "pirate_latitudes_save.json"

# Global game state
game_state = {
    "current_scene": "intro",
    "name": "Captain Anonymous",
    "inventory": [],
    "health": 100,
    "skills": {"combat": 5, "negotiation": 3, "puzzle": 4},
    "reputation": 0,
    "achievements": [],
    "story_log": []
}

# Random pirate phrases for empty input
PIRATE_EMPTY_MESSAGES = [
    "Arr, speak up, matey!",
    "Shiver me timbers, where be your words?",
    "Avast, ye silent landlubber!",
    "Yo-ho-ho, say something, ye scallywag!"
]

############################
# Curses UI Layout Setup
############################

def init_windows(stdscr):
    """Divide the screen into header, main, sidebar, input, and footer windows."""
    height, width = stdscr.getmaxyx()
    header_height = 3
    input_height = 3
    footer_height = 1
    sidebar_width = 40

    main_height = height - header_height - input_height - footer_height
    main_width = width - sidebar_width

    header_win = curses.newwin(header_height, width, 0, 0)
    main_win = curses.newwin(main_height, main_width, header_height, 0)
    sidebar_win = curses.newwin(main_height, sidebar_width, header_height, main_width)
    input_win = curses.newwin(input_height, width, header_height + main_height, 0)
    footer_win = curses.newwin(footer_height, width, height - footer_height, 0)

    main_win.scrollok(True)
    return header_win, main_win, sidebar_win, input_win, footer_win

def update_header(header_win):
    """Update the header bar with game title and status info."""
    header_win.clear()
    title = "Pirate Latitudes: Ultimate Epic Adventure"
    status = f"Health: {game_state['health']}  Reputation: {game_state['reputation']}"
    header_win.addstr(0, 2, title, curses.A_BOLD)
    header_win.addstr(1, 2, status)
    header_win.hline(2, 0, curses.ACS_HLINE, header_win.getmaxyx()[1])
    header_win.refresh()

def update_footer(footer_win):
    """Update the footer bar (for hints or extra info)."""
    footer_win.clear()
    footer_win.addstr(0, 2, "Type 'help' for commands.")
    footer_win.refresh()

def update_sidebar(sidebar_win):
    """Display an ASCII map in the sidebar window."""
    sidebar_win.clear()
    ascii_map = (
        " ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
        " |         SEA OF MYSTERY        |\n"
        " |   [Ship Deck] --- [Open Sea]    |\n"
        " |         |                     |\n"
        " |   [Below Deck] --- [Crew Qtrs]  |\n"
        " |                             |\n"
        " |  [Island Approach] --- [Jungle]|\n"
        " |                             |\n"
        " |   [Fortress] --- [Treasure]   |\n"
        " ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
    )
    sidebar_win.addstr(0, 0, ascii_map)
    sidebar_win.box()
    sidebar_win.refresh()

############################
# Enhanced Slow Print with Auto-Complete
############################

def curses_slow_print(win, text, delay=0.05):
    """
    Print text slowly (character-by-character) in the given window.
    If any key is pressed during printing, auto-complete the rest of the text immediately.
    """
    # Set window to non-blocking mode
    win.nodelay(True)
    for i, ch in enumerate(text):
        try:
            win.addstr(ch)
        except curses.error:
            pass
        win.refresh()
        # Check if a key was pressed; if so, print the remainder instantly.
        if win.getch() != -1:
            remaining = text[i+1:]
            try:
                win.addstr(remaining)
            except curses.error:
                pass
            win.refresh()
            break
        time.sleep(delay)
    win.addstr("\n")
    win.refresh()
    win.nodelay(False)

def curses_get_input(win, prompt=">> "):
    """
    Clear the input window, display a prompt, and get user input.
    If the user presses Enter with no input, return a random pirate phrase.
    """
    win.clear()
    win.addstr(0, 0, prompt)
    win.refresh()
    curses.echo()
    inp = win.getstr().decode("utf-8").strip()
    curses.noecho()
    if not inp:
        return random.choice(PIRATE_EMPTY_MESSAGES)
    return inp

############################
# ASCII Intro Movie
############################

def ascii_intro_movie(stdscr):
    """Display a series of ASCII art frames as an intro movie."""
    frames = [
r"""
   _____  _           _        _      _ 
  |  __ \| |         | |      | |    | |
  | |__) | |__   __ _| |_ __ _| | ___| |
  |  ___/| '_ \ / _` | __/ _` | |/ _ \ |
  | |    | | | | (_| | || (_| | |  __/_|
  |_|    |_| |_|\__,_|\__\__,_|_|\___(_)

         ~  ~  ~  ~  ~  ~  ~  ~  ~  ~ 
       ~       PIRATE LATITUDES        ~
         ~  ~  ~  ~  ~  ~  ~  ~  ~  ~ 
""",
r"""
         _________
        /         \
       /  PIRATE   \
      |  LATITUDES  |
       \           /
        \_________/
    
         ~  ~  ~  ~  ~  ~ 
       ~  Welcome Aboard  ~
         ~  ~  ~  ~  ~  ~ 
""",
r"""
              |    |    |
             )_)  )_)  )_)
            )___))___))___)\
           )____)____)_____)\\
         _____|____|____|____\\\__
---------\                   /---------
  ^^^^^ ^^^^^^^^^^^^^^^^^^^^^
"""
    ]
    stdscr.clear()
    height, width = stdscr.getmaxyx()
    for frame in frames:
        stdscr.clear()
        lines = frame.splitlines()
        start_y = (height - len(lines)) // 2
        for i, line in enumerate(lines):
            x = max((width - len(line)) // 2, 0)
            try:
                stdscr.addstr(start_y + i, x, line)
            except curses.error:
                pass
        stdscr.refresh()
        time.sleep(2)
    stdscr.clear()
    stdscr.refresh()

############################
# ASCII Ending Movie (Cancellable)
############################

def ascii_ending_movie(stdscr):
    """
    Display a series of ASCII art frames as an ending movie.
    If any key is pressed during the animation, end the movie early.
    """
    frames = [
r"""
          _______
         /       \
        |  THE    |
        |  END    |
         \_______/
""",
r"""
        ~~~~~~~~~~~~~~~~~~~~
       ~   Farewell, brave   ~
       ~       pirate!       ~
        ~~~~~~~~~~~~~~~~~~~~
""",
r"""
        ~  ~  ~  ~  ~  ~  ~  ~
     ~                       ~
   ~  THE JOURNEY LIVES ON!    ~
     ~                       ~
        ~  ~  ~  ~  ~  ~  ~  ~
"""
    ]
    stdscr.nodelay(True)  # Enable non-blocking input
    stdscr.clear()
    height, width = stdscr.getmaxyx()
    for frame in frames:
        stdscr.clear()
        lines = frame.splitlines()
        start_y = (height - len(lines)) // 2
        for i, line in enumerate(lines):
            x = max((width - len(line)) // 2, 0)
            try:
                stdscr.addstr(start_y + i, x, line)
            except curses.error:
                pass
        stdscr.refresh()
        # Wait for 2 seconds or break early if any key is pressed.
        for _ in range(20):
            if stdscr.getch() != -1:
                stdscr.nodelay(False)
                return
            time.sleep(0.1)
    stdscr.nodelay(False)
    stdscr.clear()
    try:
        stdscr.addstr(height//2, (width-20)//2, "Thank you for playing!")
    except curses.error:
        pass
    stdscr.refresh()
    time.sleep(3)

############################
# Save/Load Functions
############################

def save_game():
    try:
        with open(SAVE_FILE, "w") as f:
            json.dump(game_state, f)
        return "Game saved successfully!"
    except Exception as e:
        return f"Failed to save game: {e}"

def load_game():
    global game_state
    if os.path.exists(SAVE_FILE):
        try:
            with open(SAVE_FILE, "r") as f:
                game_state = json.load(f)
            return "Game loaded successfully!"
        except Exception as e:
            return f"Failed to load game: {e}"
    else:
        return "No save file found."

############################
# Updated Command Parser with Natural Language Support
############################

def parse_command(user_input):
    """
    Parse a natural language command by checking for command synonyms anywhere in the input.
    Special cases ("read map", "take map") are handled first.
    """
    user_input = user_input.lower().strip()
    if not user_input:
        return ""
    
    # Special multi-word commands for map.
    if re.search(r'\b(read|take)\s+map\b', user_input):
        return "map"
    
    # Ordered list: higher priority commands come first.
    ordered_commands = [
        ("map", ["map", "show map"]),
        ("journal", ["journal", "codex"]),
        ("look", ["look", "examine", "view"]),
        ("sail", ["sail", "navigate", "set course"]),
        ("board", ["board", "enter"]),
        ("search", ["search", "investigate", "read"]),
        ("fight", ["fight", "attack", "duel"]),
        ("negotiate", ["negotiate", "talk", "parley"]),
        ("unlock", ["unlock", "open"]),
        ("help", ["help", "commands"]),
        ("quit", ["quit", "exit"]),
        ("save", ["save"]),
        ("load", ["load"])
    ]
    for command, synonyms in ordered_commands:
        for synonym in synonyms:
            pattern = r'\b' + re.escape(synonym) + r'\b'
            if re.search(pattern, user_input):
                return command
    # Fallback: return the first word.
    parts = user_input.split()
    return parts[0] if parts else ""

############################
# In-Game Journal Functions
############################

def add_event(event):
    game_state["story_log"].append(event)

def display_journal(main_win):
    main_win.clear()
    main_win.addstr("=== In-Game Journal ===\n", curses.A_BOLD)
    if game_state["story_log"]:
        for event in game_state["story_log"]:
            main_win.addstr(f" * {event}\n")
    else:
        main_win.addstr("No events logged yet.\n")
    main_win.addstr("\nPress any key to continue...")
    main_win.refresh()
    main_win.getch()

############################
# Sample Scene Functions
############################

def scene_ship_deck(header_win, main_win, sidebar_win, input_win, footer_win):
    game_state["current_scene"] = "ship_deck"
    add_event("Arrived at the Ship's Deck.")
    main_win.clear()
    curses_slow_print(main_win, f"{game_state['name']}, you stand on the weather-beaten deck of 'The Black Meridian'.")
    curses_slow_print(main_win, "A tattered map and a captain's log hint at secrets of a hidden island fortress.")
    update_sidebar(sidebar_win)
    update_header(header_win)
    update_footer(footer_win)
    
    while True:
        user_input = curses_get_input(input_win)
        cmd = parse_command(user_input)
        if cmd == "look":
            curses_slow_print(main_win, "You see a bustling deck with crew members and a mysterious map.")
        elif cmd == "sail":
            curses_slow_print(main_win, "You command the helmsman to set sail into the deep blue.")
            scene_open_sea(header_win, main_win, sidebar_win, input_win, footer_win)
            break
        elif cmd == "board":
            curses_slow_print(main_win, "You venture below deck, where whispered secrets abound.")
            scene_below_deck(header_win, main_win, sidebar_win, input_win, footer_win)
            break
        elif cmd == "map":
            update_sidebar(sidebar_win)
        elif cmd == "save":
            msg = save_game()
            curses_slow_print(main_win, msg)
        elif cmd == "load":
            msg = load_game()
            curses_slow_print(main_win, msg)
        elif cmd == "journal":
            display_journal(main_win)
        elif cmd == "quit":
            curses_slow_print(main_win, "The tides recede as you exit the adventure. Farewell!")
            exit(0)
        elif cmd == "help":
            display_help_menu(main_win, input_win)
        else:
            curses_slow_print(main_win, "Command not recognized. Try 'help'.")

def scene_below_deck(header_win, main_win, sidebar_win, input_win, footer_win):
    game_state["current_scene"] = "below_deck"
    add_event("Exploring Below Deck.")
    main_win.clear()
    curses_slow_print(main_win, "In the cramped corridors beneath the ship, dim lanterns reveal a weathered journal.")
    update_sidebar(sidebar_win)
    update_header(header_win)
    update_footer(footer_win)
    
    while True:
        user_input = curses_get_input(input_win)
        cmd = parse_command(user_input)
        if cmd == "look":
            curses_slow_print(main_win, "The journal details hidden coves and mysterious symbols.")
        elif cmd == "search":
            curses_slow_print(main_win, "Decoding the entries, you learn of an island fortress with untold treasures.")
            add_event("Learned about secret island.")
            scene_ship_deck(header_win, main_win, sidebar_win, input_win, footer_win)
            break
        elif cmd == "sail":
            curses_slow_print(main_win, "Believing the clues suffice, you return to the deck to set sail.")
            scene_ship_deck(header_win, main_win, sidebar_win, input_win, footer_win)
            break
        elif cmd == "map":
            update_sidebar(sidebar_win)
        elif cmd == "save":
            msg = save_game()
            curses_slow_print(main_win, msg)
        elif cmd == "load":
            msg = load_game()
            curses_slow_print(main_win, msg)
        elif cmd == "journal":
            display_journal(main_win)
        elif cmd == "quit":
            curses_slow_print(main_win, "Retreating from below deck, you end your adventure. Farewell!")
            exit(0)
        elif cmd == "help":
            display_help_menu(main_win, input_win)
        else:
            curses_slow_print(main_win, "Command not recognized. Try 'help'.")

def scene_open_sea(header_win, main_win, sidebar_win, input_win, footer_win):
    game_state["current_scene"] = "open_sea"
    add_event("Sailing on the Open Sea.")
    main_win.clear()
    curses_slow_print(main_win, "The ship cuts through restless waves as dark clouds gather overhead.")
    update_sidebar(sidebar_win)
    update_header(header_win)
    update_footer(footer_win)
    
    while True:
        user_input = curses_get_input(input_win)
        cmd = parse_command(user_input)
        if cmd == "look":
            curses_slow_print(main_win, "Turbulent waves and flashes of lightning mirror your inner turmoil.")
        elif cmd == "sail":
            curses_slow_print(main_win, "You steer the ship into the heart of the storm. The winds howl!")
            scene_storm_at_sea(header_win, main_win, sidebar_win, input_win, footer_win)
            break
        elif cmd == "map":
            update_sidebar(sidebar_win)
        elif cmd == "save":
            msg = save_game()
            curses_slow_print(main_win, msg)
        elif cmd == "load":
            msg = load_game()
            curses_slow_print(main_win, msg)
        elif cmd == "journal":
            display_journal(main_win)
        elif cmd == "quit":
            curses_slow_print(main_win, "Unable to face the storm, you abandon your quest. Farewell!")
            exit(0)
        elif cmd == "help":
            display_help_menu(main_win, input_win)
        else:
            curses_slow_print(main_win, "Command not recognized. Try 'help'.")

def scene_storm_at_sea(header_win, main_win, sidebar_win, input_win, footer_win):
    game_state["current_scene"] = "storm_at_sea"
    add_event("Endured the Storm at Sea.")
    main_win.clear()
    curses_slow_print(main_win, "Rain lashes the deck and thunder shakes the ship. The storm is fierce!")
    update_sidebar(sidebar_win)
    update_header(header_win)
    update_footer(footer_win)
    
    while True:
        user_input = curses_get_input(input_win)
        cmd = parse_command(user_input)
        if cmd == "look":
            curses_slow_print(main_win, "The deck is slippery and the crew scrambles in the tempest.")
        elif cmd == "fight":
            curses_slow_print(main_win, "You rally your crew to secure the ship.")
            if game_state["skills"]["combat"] + random.randint(0, 3) > 6:
                curses_slow_print(main_win, "Your skill prevails! The storm begins to subside.")
                add_event("Conquered the storm.")
                scene_island_approach(header_win, main_win, sidebar_win, input_win, footer_win)
                break
            else:
                curses_slow_print(main_win, "The storm takes its toll. You lose 15 health.")
                game_state["health"] -= 15
                if game_state["health"] <= 0:
                    curses_slow_print(main_win, "You have succumbed to the storm...")
                    exit(0)
                scene_island_approach(header_win, main_win, sidebar_win, input_win, footer_win)
                break
        elif cmd == "negotiate":
            curses_slow_print(main_win, "You shout orders and inspire your crew with a rousing shanty. The tempest abates.")
            scene_island_approach(header_win, main_win, sidebar_win, input_win, footer_win)
            break
        elif cmd == "map":
            update_sidebar(sidebar_win)
        elif cmd == "save":
            msg = save_game()
            curses_slow_print(main_win, msg)
        elif cmd == "load":
            msg = load_game()
            curses_slow_print(main_win, msg)
        elif cmd == "quit":
            curses_slow_print(main_win, "The storm overwhelms you, and you abandon ship. Farewell!")
            exit(0)
        elif cmd == "help":
            display_help_menu(main_win, input_win)
        else:
            curses_slow_print(main_win, "Command not recognized. Act swiftly!")

def scene_island_approach(header_win, main_win, sidebar_win, input_win, footer_win):
    game_state["current_scene"] = "island_approach"
    add_event("Approaching the Secret Island.")
    main_win.clear()
    curses_slow_print(main_win, "After the storm, a blood‑red sunset reveals a rugged island with hidden fortifications.")
    update_sidebar(sidebar_win)
    update_header(header_win)
    update_footer(footer_win)
    
    while True:
        user_input = curses_get_input(input_win)
        cmd = parse_command(user_input)
        if cmd == "look":
            curses_slow_print(main_win, "From the deck, you see cannons, watchtowers, and secret coves carved into the rocks.")
        elif cmd == "board":
            curses_slow_print(main_win, "You lower the boats and prepare a landing party.")
            scene_ship_deck(header_win, main_win, sidebar_win, input_win, footer_win)
            break
        elif cmd == "map":
            update_sidebar(sidebar_win)
        elif cmd == "save":
            msg = save_game()
            curses_slow_print(main_win, msg)
        elif cmd == "load":
            msg = load_game()
            curses_slow_print(main_win, msg)
        elif cmd == "quit":
            curses_slow_print(main_win, "Fearing the island's perils, you retreat. Farewell!")
            exit(0)
        elif cmd == "help":
            display_help_menu(main_win, input_win)
        else:
            curses_slow_print(main_win, "Command not recognized. Try 'help'.")

############################
# Help Menu Display
############################

def display_help_menu(main_win, input_win):
    help_text = (
        "Help / Commands:\n"
        "  look/examine/view      - Observe your surroundings\n"
        "  sail/navigate/set course - Set sail to a new destination\n"
        "  board/enter             - Board a ship or enter a location\n"
        "  search/read/investigate - Look for clues or treasure\n"
        "  fight/attack/duel       - Engage in battle\n"
        "  negotiate/talk/parley   - Parley with others\n"
        "  unlock/open             - Open a locked door\n"
        "  map/show map            - Display the ASCII map\n"
        "  journal/codex           - Show your in-game journal\n"
        "  save                    - Save your progress\n"
        "  load                    - Load your progress\n"
        "  help/commands           - Show this help menu\n"
        "  quit/exit               - Exit the adventure\n\n"
        "Press any key to return..."
    )
    main_win.clear()
    curses_slow_print(main_win, help_text, delay=0.02)
    input_win.clear()
    input_win.addstr(0, 0, "Press any key to continue...")
    input_win.refresh()
    input_win.getch()

############################
# Character Customization
############################

def character_customization(stdscr):
    stdscr.clear()
    curses.curs_set(1)
    curses.echo()
    stdscr.addstr(2, 2, "Enter your pirate name: ")
    name = stdscr.getstr().decode("utf-8").strip()
    if name:
        game_state["name"] = name
    else:
        game_state["name"] = "Captain Anonymous"
    stdscr.addstr(4, 2, f"Welcome, {game_state['name']}!")
    stdscr.addstr(6, 2, "Allocate 10 skill points among Combat, Negotiation, and Puzzle skills (e.g., 4 3 3): ")
    while True:
        try:
            points = stdscr.getstr().decode("utf-8").strip().split()
            points = list(map(int, points))
            if len(points) != 3 or sum(points) != 10:
                stdscr.addstr(8, 2, "Please allocate exactly 10 points. Try again: ")
                stdscr.clrtoeol()
                continue
            game_state["skills"]["combat"] = points[0]
            game_state["skills"]["negotiation"] = points[1]
            game_state["skills"]["puzzle"] = points[2]
            break
        except Exception:
            stdscr.addstr(8, 2, "Invalid input. Try again: ")
            stdscr.clrtoeol()
    curses.noecho()
    add_event(f"Character created: {game_state['name']} with skills {game_state['skills']}")
    stdscr.addstr(10, 2, "Press any key to continue...")
    stdscr.getch()

############################
# Main Curses Function
############################

def curses_main(stdscr):
    curses.curs_set(0)
    stdscr.clear()
    
    # Show ASCII Intro Movie
    ascii_intro_movie(stdscr)
    
    # Full-screen main menu using stdscr
    stdscr.clear()
    height, width = stdscr.getmaxyx()
    menu_items = ["New Game", "Load Game", "Help", "Quit"]
    current_selection = 0
    while True:
        stdscr.clear()
        title = "Pirate Latitudes: Ultimate Epic Adventure"
        stdscr.addstr(2, (width - len(title)) // 2, title, curses.A_BOLD)
        for idx, item in enumerate(menu_items):
            x = (width - len(item)) // 2
            y = 4 + idx
            if idx == current_selection:
                stdscr.attron(curses.A_REVERSE)
                stdscr.addstr(y, x, item)
                stdscr.attroff(curses.A_REVERSE)
            else:
                stdscr.addstr(y, x, item)
        stdscr.refresh()
        key = stdscr.getch()
        if key == curses.KEY_UP:
            current_selection = (current_selection - 1) % len(menu_items)
        elif key == curses.KEY_DOWN:
            current_selection = (current_selection + 1) % len(menu_items)
        elif key in [10, 13]:
            break

    choice = menu_items[current_selection]
    if choice == "New Game":
        character_customization(stdscr)
    elif choice == "Load Game":
        msg = load_game()
        stdscr.clear()
        stdscr.addstr(2, 2, msg)
        stdscr.addstr(4, 2, "Press any key to continue...")
        stdscr.refresh()
        stdscr.getch()
    elif choice == "Help":
        help_text = (
            "Help / Commands:\n"
            "  look/examine/view      - Observe your surroundings\n"
            "  sail/navigate/set course - Set sail to a new destination\n"
            "  board/enter             - Board a ship or enter a location\n"
            "  search/read/investigate - Look for clues or treasure\n"
            "  fight/attack/duel       - Engage in battle\n"
            "  negotiate/talk/parley   - Parley with others\n"
            "  unlock/open             - Open a locked door\n"
            "  map/show map            - Display the ASCII map\n"
            "  journal/codex           - Show your in-game journal\n"
            "  save                    - Save your progress\n"
            "  load                    - Load your progress\n"
            "  help/commands           - Show this help menu\n"
            "  quit/exit               - Exit the adventure\n\n"
            "Press any key to return..."
        )
        stdscr.clear()
        stdscr.addstr(2, 2, help_text)
        stdscr.refresh()
        stdscr.getch()
        curses_main(stdscr)
        return
    elif choice == "Quit":
        stdscr.clear()
        stdscr.addstr(height//2, (width - 20) // 2, "Farewell, brave pirate!")
        stdscr.refresh()
        time.sleep(2)
        return

    # After main menu, initialize game panels.
    header_win, main_win, sidebar_win, input_win, footer_win = init_windows(stdscr)
    
    # Start the game at the ship deck.
    scene_ship_deck(header_win, main_win, sidebar_win, input_win, footer_win)
    
    # (Game loop would continue through scenes...)
    
    # When game ends, show the ASCII Ending Movie.
    ascii_ending_movie(stdscr)

############################
# Unit Tests
############################

class TestCommandParser(unittest.TestCase):
    def test_empty_input(self):
        self.assertEqual(parse_command(""), "")
    
    def test_look_commands(self):
        self.assertEqual(parse_command("look around"), "look")
        self.assertEqual(parse_command("examine the map"), "look")
        self.assertEqual(parse_command("view"), "look")
    
    def test_sail_commands(self):
        self.assertEqual(parse_command("sail north"), "sail")
        self.assertEqual(parse_command("navigate quickly"), "sail")
    
    def test_board_commands(self):
        self.assertEqual(parse_command("board the ship"), "board")
        self.assertEqual(parse_command("enter cabin"), "board")
    
    def test_search_commands(self):
        self.assertEqual(parse_command("search for clues"), "search")
        self.assertEqual(parse_command("read journal"), "search")
    
    def test_fight_commands(self):
        self.assertEqual(parse_command("fight them"), "fight")
        self.assertEqual(parse_command("attack enemy"), "fight")
    
    def test_negotiate_commands(self):
        self.assertEqual(parse_command("negotiate peace"), "negotiate")
        self.assertEqual(parse_command("talk to captain"), "negotiate")
    
    def test_unlock_commands(self):
        self.assertEqual(parse_command("unlock door"), "unlock")
        self.assertEqual(parse_command("open chest"), "unlock")
    
    def test_map_commands(self):
        self.assertEqual(parse_command("map"), "map")
        self.assertEqual(parse_command("show map please"), "map")
        self.assertEqual(parse_command("read map"), "map")
        self.assertEqual(parse_command("take map"), "map")
        self.assertEqual(parse_command("I want to see the map"), "map")
    
    def test_journal_commands(self):
        self.assertEqual(parse_command("journal"), "journal")
        self.assertEqual(parse_command("codex entries"), "journal")
    
    def test_help_commands(self):
        self.assertEqual(parse_command("help"), "help")
        self.assertEqual(parse_command("commands"), "help")
    
    def test_quit_commands(self):
        self.assertEqual(parse_command("quit"), "quit")
        self.assertEqual(parse_command("exit now"), "quit")
    
    def test_save_commands(self):
        self.assertEqual(parse_command("save game"), "save")
    
    def test_load_commands(self):
        self.assertEqual(parse_command("load game"), "load")
    
    def test_unknown_command(self):
        self.assertEqual(parse_command("foobar test"), "foobar")

class TestJournalFunctions(unittest.TestCase):
    def test_add_event(self):
        initial_len = len(game_state["story_log"])
        add_event("Test Event")
        self.assertEqual(len(game_state["story_log"]), initial_len + 1)
        self.assertEqual(game_state["story_log"][-1], "Test Event")

############################
# Main Entry Point
############################

if __name__ == "__main__":
    # If "test" is passed as an argument, run the unit tests.
    if len(sys.argv) > 1 and sys.argv[1] == "test":
        sys.argv.pop(1)
        unittest.main()
    else:
        curses.wrapper(curses_main)
