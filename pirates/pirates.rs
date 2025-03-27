use std::io::{self, Write};
use std::thread;
use std::time::Duration;
use std::fs::{self, File};
use std::io::prelude::*;
use rand::seq::SliceRandom;
use termion::{clear, cursor};

const SAVE_FILE: &str = "pirate_latitudes_save.json";

#[derive(Debug, serde::Serialize, serde::Deserialize)]
struct GameState {
    current_scene: String,
    name: String,
    inventory: Vec<String>,
    health: i32,
    skills: Skills,
    reputation: i32,
    achievements: Vec<String>,
    story_log: Vec<String>,
}

#[derive(Debug, serde::Serialize, serde::Deserialize)]
struct Skills {
    combat: i32,
    negotiation: i32,
    puzzle: i32,
}

impl Default for GameState {
    fn default() -> Self {
        Self {
            current_scene: "intro".to_string(),
            name: "Captain Anonymous".to_string(),
            inventory: vec![],
            health: 100,
            skills: Skills { combat: 5, negotiation: 3, puzzle: 4 },
            reputation: 0,
            achievements: vec![],
            story_log: vec![],
        }
    }
}

fn save_game(game_state: &GameState) {
    let save_data = serde_json::to_string(game_state).expect("Failed to serialize game state");
    fs::write(SAVE_FILE, save_data).expect("Failed to write save file");
    println!("Game saved successfully!");
}

fn load_game() -> GameState {
    if let Ok(save_data) = fs::read_to_string(SAVE_FILE) {
        if let Ok(game_state) = serde_json::from_str(&save_data) {
            println!("Game loaded successfully!");
            return game_state;
        }
    }
    println!("No save file found, starting a new game.");
    GameState::default()
}

fn slow_print(text: &str, delay: Duration) {
    for ch in text.chars() {
        print!("{}", ch);
        io::stdout().flush().unwrap();
        thread::sleep(delay);
    }
    println!();
}

fn get_input(prompt: &str) -> String {
    print!("{}", prompt);
    io::stdout().flush().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}

fn ascii_intro_movie() {
    let frames = vec![
        "\n   _____  _           _        _      _\n  |  __ \\| |         | |      | |    | |\n  | |__) | |__   __ _| |_ __ _| | ___| |\n  |  ___/| '_ \\ / _` | __/ _` | |/ _ \\ |\n  | |    | | | | (_| | || (_| | |  __/_|\n  |_|    |_| |_|\\__,_|\\__\\__,_|_|\\___(_)\n\n         ~  ~  ~  ~  ~  ~  ~  ~  ~  ~ \n       ~       PIRATE LATITUDES        ~\n         ~  ~  ~  ~  ~  ~  ~  ~  ~  ~ \n",
    ];
    for frame in frames {
        print!("{}{}", clear::All, cursor::Goto(1, 1));
        slow_print(frame, Duration::from_millis(50));
        thread::sleep(Duration::from_secs(2));
    }
}

fn main() {
    let mut game_state = load_game();
    ascii_intro_movie();
    println!("Welcome to Pirate Latitudes, {}!", game_state.name);
    loop {
        let command = get_input(" >> ");
        match command.as_str() {
            "look" => println!("You observe your surroundings..."),
            "save" => save_game(&game_state),
            "quit" => break,
            _ => println!("Command not recognized. Try 'look', 'save', or 'quit'."),
        }
    }
    println!("Farewell, brave pirate!");
}
