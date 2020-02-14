#[macro_use]
extern crate lazy_static;

use base64::encode_config;
use hashbrown::HashMap;
use hex;
use rayon::prelude::*;
use std::time::Instant;
use std::{
    fs::File,
    io::{prelude::*, BufReader},
    path::Path,
};

lazy_static! {
    static ref LETTER_FREQUENCY: HashMap<char, f64> = [
        ('a', 0.0651738),
        ('b', 0.0124248),
        ('c', 0.0217339),
        ('d', 0.0349835),
        ('e', 0.1041442),
        ('f', 0.0197881),
        ('g', 0.0158610),
        ('h', 0.0492888),
        ('i', 0.0558094),
        ('j', 0.0009033),
        ('k', 0.0050529),
        ('l', 0.0331490),
        ('m', 0.0202124),
        ('n', 0.0564513),
        ('o', 0.0596302),
        ('p', 0.0137645),
        ('q', 0.0008606),
        ('r', 0.0497563),
        ('s', 0.0515760),
        ('t', 0.0729357),
        ('u', 0.0225134),
        ('v', 0.0082903),
        ('w', 0.0171272),
        ('x', 0.0013692),
        ('y', 0.0145984),
        ('z', 0.0007836),
        (' ', 0.1918182),
    ]
    .iter()
    .copied()
    .collect();
}

fn main() {
    let before_cycle = Instant::now();
    for _ in 0..1 {
        challenge4_set1();
    }
    let time = before_cycle.elapsed().as_micros();
    println!("{}", time);
}

fn challenge1_set1() {
    let input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    let hex = hex::decode(input).unwrap();
    let base64 = encode_config(&hex, base64::STANDARD);
    println!("{}", base64);
}

fn challenge2_set1() {
    let hex1 = hex::decode("1c0111001f010100061a024b53535009181c").unwrap();
    let hex2 = hex::decode("686974207468652062756c6c277320657965").unwrap();
    println!("{}", hex::encode(xor(&hex1, &hex2)));
}

fn challenge3_set1() {
    let string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    let text = hex::decode(string).unwrap();
    let result = (0..=255)
        .into_par_iter()
        .map(|key| hex_to_ascii(single_char_xor(&text, key as u8)))
        .min_by_key(|x| (eval_letter_frequency(x) * 1000000.0) as u32)
        .unwrap();
    println!("{}", result);
}

fn challenge4_set1() {
    let lines = lines_from_file("4.txt");
    let mut results = Vec::new();
    for line in lines {
        let text = hex::decode(line).unwrap();
        let result = (0..=255)
            .into_par_iter()
            .map(|key| hex_to_ascii(single_char_xor(&text, key as u8)))
            .min_by_key(|x| (eval_letter_frequency(x) * 1000000.0) as u32)
            .unwrap();
        results.push(result);
    }

    println!(
        "{}",
        results
            .iter()
            .min_by_key(|x| (eval_letter_frequency(x) * 1000000.0) as u32)
            .unwrap()
    );
}

fn lines_from_file(filename: impl AsRef<Path>) -> Vec<String> {
    let file = File::open(filename).expect("No such file");
    let buf = BufReader::new(file);
    buf.lines().map(|l| l.unwrap()).collect()
}

fn hex_to_ascii(hex: Vec<u8>) -> String {
    hex.iter().map(|&x| x as char).collect()
}

fn single_char_xor(text: &Vec<u8>, key: u8) -> Vec<u8> {
    xor(&text, &vec![key; text.len()])
}

fn xor(hex1: &Vec<u8>, hex2: &Vec<u8>) -> Vec<u8> {
    hex1.iter().zip(hex2.iter()).map(|(x, y)| x ^ y).collect()
}

fn eval_letter_frequency(text: &String) -> f64 {
    let mut letter_count = HashMap::with_capacity(LETTER_FREQUENCY.len());

    text.to_lowercase()
        .chars()
        .for_each(|c| *letter_count.entry(c).or_insert(0.0) += 1.0);

    LETTER_FREQUENCY
        .keys()
        .map(|key| {
            *letter_count.entry(*key).or_default() / text.len() as f64 - LETTER_FREQUENCY[&key]
        })
        .sum::<f64>()
        .abs()
}
