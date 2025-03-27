/*=====================================================================
  Ternary Calculator: A Minimalist Ternary Arithmetic Evaluator in Rust
  Version: 1.0-RS
  Author: Grok (inspired by Copyleft Systems)
  Date: Mar 3 2025

  This literate program implements a simple Rust-based tool that evaluates
  ternary arithmetic expressions (base-3 digits: 0, 1, 2) from standard input
  and outputs the result in ternary format to standard output. Following Linux's
  tradition of "doing one thing well," it focuses solely on expression evaluation,
  omitting extraneous features like matrix operations or interactive modes.
  It supports addition, subtraction, multiplication, division, and parentheses,
  with robust error handling. Designed for pipeline use (e.g., `echo "12+21" | ternary`),
  it’s portable, safe, and adheres to Unix philosophy.
=====================================================================*/

/*=====================================================================
  Rust Main Module: main.rs
  This file defines the `ternary` tool, a single-purpose ternary arithmetic calculator.
  It reads one line from stdin, parses it as a ternary expression, evaluates it,
  and writes the ternary result to stdout. Errors are reported to stderr with an
  exit code, making it script-friendly.
=====================================================================*/
@* Rust Main Module: main.rs
@o main.rs
@c
// Import standard library modules for I/O and process control.
use std::io::{self, BufRead, Write};
use std::process;

// Enum for ternary parsing errors, ensuring precise feedback.
#[derive(Debug)]
enum ParseError {
    /// Indicates an invalid digit (not 0, 1, or 2).
    InvalidDigit(char),
    /// Signals an unexpected character in the expression.
    UnexpectedChar(char),
    /// Occurs when a closing parenthesis is missing.
    MissingClosingParen,
    /// Triggered by division by zero.
    DivisionByZero,
    /// Reported if the input is empty.
    EmptyInput,
}

// Implement Display for ParseError to provide clear error messages.
impl std::fmt::Display for ParseError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            ParseError::InvalidDigit(c) => write!(f, "invalid digit '{}': expected 0, 1, or 2", c),
            ParseError::UnexpectedChar(c) => write!(f, "unexpected character '{}'", c),
            ParseError::MissingClosingParen => write!(f, "missing closing parenthesis"),
            ParseError::DivisionByZero => write!(f, "division by zero"),
            ParseError::EmptyInput => write!(f, "empty input"),
        }
    }
}

/// Evaluates a ternary arithmetic expression from a string.
/// Returns the result as an i32 or a ParseError if invalid.
fn evaluate_ternary(expr: &str) -> Result<i32, ParseError> {
    let expr = expr.trim(); // Remove leading/trailing whitespace.
    if expr.is_empty() {
        return Err(ParseError::EmptyInput);
    }
    let chars: Vec<char> = expr.chars().collect(); // Convert to char vector for indexing.
    let mut pos = 0; // Position tracker for parsing.
    let result = parse_expr(&chars, &mut pos)?; // Start parsing with expression level.
    // Ensure no trailing non-whitespace characters remain.
    while pos < chars.len() {
        if !chars[pos].is_whitespace() {
            return Err(ParseError::UnexpectedChar(chars[pos]));
        }
        pos += 1;
    }
    Ok(result)
}

/// Parses an expression with addition and subtraction.
/// Supports left-to-right evaluation of '+' and '-'.
fn parse_expr(chars: &[char], pos: &mut usize) -> Result<i32, ParseError> {
    let mut value = parse_term(chars, pos)?; // Start with a term (handles * and /).
    while *pos < chars.len() {
        skip_whitespace(chars, pos);
        match chars.get(*pos) {
            Some('+') => {
                *pos += 1; // Consume '+'.
                value += parse_term(chars, pos)?; // Add next term.
            }
            Some('-') => {
                *pos += 1; // Consume '-'.
                value -= parse_term(chars, pos)?; // Subtract next term.
            }
            _ => break, // No more operators at this level.
        }
    }
    Ok(value)
}

/// Parses a term with multiplication and division.
/// Handles '*' and '/' with higher precedence than '+' and '-'.
fn parse_term(chars: &[char], pos: &mut usize) -> Result<i32, ParseError> {
    let mut value = parse_factor(chars, pos)?; // Start with a factor (number or parens).
    while *pos < chars.len() {
        skip_whitespace(chars, pos);
        match chars.get(*pos) {
            Some('*') => {
                *pos += 1; // Consume '*'.
                value *= parse_factor(chars, pos)?; // Multiply by next factor.
            }
            Some('/') => {
                *pos += 1; // Consume '/'.
                let next = parse_factor(chars, pos)?;
                if next == 0 {
                    return Err(ParseError::DivisionByZero);
                }
                value /= next; // Divide by next factor.
            }
            _ => break, // No more operators at this level.
        }
    }
    Ok(value)
}

/// Parses a factor: either a ternary number or a parenthesized expression.
/// Supports nested expressions with proper precedence.
fn parse_factor(chars: &[char], pos: &mut usize) -> Result<i32, ParseError> {
    skip_whitespace(chars, pos);
    if *pos >= chars.len() {
        return Err(ParseError::UnexpectedChar('\0')); // Unexpected end of input.
    }
    if chars[*pos] == '(' {
        *pos += 1; // Consume opening parenthesis.
        let value = parse_expr(chars, pos)?; // Recursively parse inside parens.
        skip_whitespace(chars, pos);
        if *pos >= chars.len() || chars[*pos] != ')' {
            return Err(ParseError::MissingClosingParen);
        }
        *pos += 1; // Consume closing parenthesis.
        Ok(value)
    } else {
        parse_number(chars, pos) // Parse a standalone ternary number.
    }
}

/// Parses a sequence of ternary digits (0, 1, 2) into an integer.
/// Accumulates value in base-3.
fn parse_number(chars: &[char], pos: &mut usize) -> Result<i32, ParseError> {
    skip_whitespace(chars, pos);
    if *pos >= chars.len() {
        return Err(ParseError::UnexpectedChar('\0'));
    }
    let mut value = 0;
    let mut has_digits = false;
    while *pos < chars.len() {
        let c = chars[*pos];
        if c >= '0' && c <= '2' {
            value = value * 3 + (c as i32 - '0' as i32); // Base-3 accumulation.
            has_digits = true;
            *pos += 1;
        } else {
            break; // Stop at non-digit.
        }
    }
    if !has_digits {
        return Err(ParseError::InvalidDigit(chars[*pos]));
    }
    Ok(value)
}

/// Advances the position past any whitespace characters.
/// Ensures parsing aligns with the next meaningful token.
fn skip_whitespace(chars: &[char], pos: &mut usize) {
    while *pos < chars.len() && chars[*pos].is_whitespace() {
        *pos += 1;
    }
}

/// Converts an integer to its ternary string representation.
/// Outputs digits 0-2, with a leading '-' for negative numbers.
fn int_to_ternary(n: i32) -> String {
    if n == 0 {
        return "0".to_string(); // Special case for zero.
    }
    let mut digits = Vec::new();
    let mut num = n.abs(); // Work with absolute value.
    while num > 0 {
        digits.push((num % 3) as u8 + b'0'); // Extract ternary digits.
        num /= 3;
    }
    if n < 0 {
        digits.push(b'-'); // Prepend negative sign if needed.
    }
    String::from_utf8(digits.into_iter().rev().collect()).unwrap() // Reverse and build string.
}

/// Main entry point for the ternary calculator.
/// Reads one line from stdin, evaluates it, and outputs the result or an error.
fn main() {
    // Lock stdin for reading one line efficiently.
    let stdin = io::stdin();
    let mut input = String::new();
    if let Err(e) = stdin.lock().read_line(&mut input) {
        eprintln!("error: failed to read input: {}", e);
        process::exit(1);
    }

    // Evaluate the ternary expression.
    match evaluate_ternary(&input) {
        Ok(result) => {
            // Write result in ternary format to stdout with a newline.
            if let Err(e) = writeln!(io::stdout(), "{}", int_to_ternary(result)) {
                eprintln!("error: failed to write output: {}", e);
                process::exit(1);
            }
        }
        Err(e) => {
            // Write error message to stderr and exit with failure code.
            eprintln!("error: {}", e);
            process::exit(1);
        }
    }
}
@*/

/*=====================================================================
  End of Ternary Calculator CWEB Document
=====================================================================*/
