use std::env;
use std::process;

/// Supported bases for conversion (expanded as per request)
const SUPPORTED_BASES: &[u32] = &[
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 20, 24, 26, 32, 36, 60, 64, 81, 
    100, 256, 1024, 4096, 1_000_000
];

/// Convert a number from one base to another
fn convert_base(number: &str, from_base: u32, to_base: u32) -> Result<String, String> {
    if !SUPPORTED_BASES.contains(&from_base) || !SUPPORTED_BASES.contains(&to_base) {
        return Err(format!("Error: Unsupported base {} or {}", from_base, to_base));
    }

    let decimal_value = u128::from_str_radix(number, from_base)
        .map_err(|_| format!("Error: Invalid number for base {}", from_base))?;

    Ok(decimal_to_base(decimal_value, to_base))
}

/// Convert decimal to target base
fn decimal_to_base(mut decimal_value: u128, base: u32) -> String {
    if decimal_value == 0 {
        return "0".to_string();
    }

    let mut digits = Vec::new();
    while decimal_value > 0 {
        digits.push((decimal_value % base as u128) as u8);
        decimal_value /= base as u128;
    }

    digits
        .into_iter()
        .rev()
        .map(|d| char::from_digit(d as u32, base).unwrap_or('?'))
        .collect()
}

/// Perform arithmetic operations in a given base
fn perform_operation(num1: &str, num2: &str, base: u32, operation: char) -> Result<String, String> {
    if !SUPPORTED_BASES.contains(&base) {
        return Err(format!("Error: Unsupported base {}", base));
    }

    let num1_dec = u128::from_str_radix(num1, base).map_err(|_| "Error: Invalid number".to_string())?;
    let num2_dec = u128::from_str_radix(num2, base).map_err(|_| "Error: Invalid number".to_string())?;

    let result = match operation {
        '+' => num1_dec + num2_dec,
        '-' => num1_dec.saturating_sub(num2_dec),
        '*' => num1_dec * num2_dec,
        '/' => num1_dec / num2_dec,
        _ => return Err("Error: Invalid operation".to_string()),
    };

    Ok(decimal_to_base(result, base))
}

/// Uses Axion AI logic to suggest the best base for a given number
fn suggest_best_base(number: &str) -> u32 {
    let length = number.len();
    match length {
        0..=5 => 2,    // Small numbers work best in binary
        6..=10 => 10,  // Decimal for standard usage
        11..=15 => 16, // Hexadecimal for compact representation
        16..=30 => 60, // Base-60 for large numbers
        _ => 81,       // T81 optimization for AI/Big Data
    }
}

/// Print detailed help about supported bases
fn print_help() {
    println!("Usage: t81base <command> [options]\n");
    println!("Commands:");
    println!("  convert <num> <from_base> <to_base>  Convert number between bases");
    println!("  calc <num1> <op> <num2> <base>       Perform arithmetic in a base");
    println!("  suggest <num>                        Suggest optimal base");
    println!("  --help                               Show this help menu\n");
    
    println!("Supported Bases:");
    println!("  Base-2  (Binary)        - Digital computing, logic circuits");
    println!("  Base-3  (Ternary)       - Theoretical computing, AI optimizations");
    println!("  Base-4  (Quaternary)    - DNA sequencing, error correction");
    println!("  Base-5  (Quinary)       - Abacus, Mayan numeral system");
    println!("  Base-6  (Senary)        - Dice calculations, ancient cultures");
    println!("  Base-7  (Septenary)     - Cryptography, cultural numeral systems");
    println!("  Base-8  (Octal)         - Early computing, UNIX permissions");
    println!("  Base-9  (Nonary)        - Numerology, alternative representations");
    println!("  Base-10 (Decimal)       - Standard numeric system");
    println!("  Base-11 to Base-16      - Experimental and computing uses");
    println!("  Base-20, 24, 26, 32, 36 - Ancient systems, cryptography, encoding");
    println!("  Base-60 (Sexagesimal)   - Babylonian, time and angles");
    println!("  Base-64                 - Data encoding, email encryption");
    println!("  Base-81                 - AI and ternary computing");
    println!("  Base-100+               - Theoretical applications");
}

/// POSIX-compliant CLI entry point
fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        print_help();
        process::exit(1);
    }

    let command = args[1].as_str();

    match command {
        "convert" if args.len() == 5 => {
            let number = &args[2];
            let from_base: u32 = args[3].parse().unwrap_or(0);
            let to_base: u32 = args[4].parse().unwrap_or(0);

            match convert_base(number, from_base, to_base) {
                Ok(result) => println!("{}", result), // Machine-readable output
                Err(e) => eprintln!("{}", e),
            }
        }
        "calc" if args.len() == 6 => {
            let num1 = &args[2];
            let operation = args[3].chars().next().unwrap_or('+');
            let num2 = &args[4];
            let base: u32 = args[5].parse().unwrap_or(0);

            match perform_operation(num1, num2, base, operation) {
                Ok(result) => println!("{}", result),
                Err(e) => eprintln!("{}", e),
            }
        }
        "suggest" if args.len() == 3 => {
            let number = &args[2];
            println!("{}", suggest_best_base(number)); // Best base recommendation
        }
        "--help" | "-h" => {
            print_help();
        }
        _ => {
            print_help();
            process::exit(1);
        }
    }
}
