#[macro_use]
extern crate lazy_static;

use base64::{decode_config, encode_config};
use hashbrown::HashMap;
use hex;
use rayon::prelude::*;
use std::fs;
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
        challenge6_set1();
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
    let key = find_single_char_xor_key(&text);
    let result = hex_to_ascii(single_char_xor(&text, key));
    println!("{}", result);
    println!("Key: {}", key as char);
}

fn challenge4_set1() {
    let lines = lines_from_file("4.txt");

    let decrypted: Vec<String> = lines
        .into_par_iter()
        .map(|line| hex::decode(line).unwrap())
        .map(|text| hex_to_ascii(single_char_xor(&text, find_single_char_xor_key(&text))))
        .collect();

    let english_text = decrypted
        .into_iter()
        .min_by_key(|x| eval_letter_frequency(x))
        .unwrap();

    println!("{}", english_text);
}

fn challenge5_set1() {
    let string = b"Burning 'em, if you ain't quick and nimble
I go crazy when I hear a cymbal"
        .to_vec();
    let key = b"ICE".to_vec();
    println!("{}", hex::encode(repeating_key_xor(&string, &key)));
}

fn challenge6_set1() {
    let input = fs::read_to_string("6.txt").unwrap().replace('\n', "");
    let text = decode_config(&input, base64::STANDARD).unwrap();
    let key_size = estimate_key_size(2, 40, &text);
    let key = (0..key_size)
        .into_par_iter()
        .map(|position| find_single_char_xor_key(&chunks(position, key_size, &text)))
        .collect();
    let decrypted = repeating_key_xor(&text, &key);

    println!("{}", hex_to_ascii(decrypted));
    println!("Key: {}", hex_to_ascii(key));
}

fn lines_from_file(filename: impl AsRef<Path>) -> Vec<String> {
    let file = File::open(filename).expect("No such file");
    let buf = BufReader::new(file);
    buf.lines().map(|l| l.unwrap()).collect()
}

fn find_single_char_xor_key(text: &Vec<u8>) -> u8 {
    (0..=255)
        .min_by_key(|key| eval_letter_frequency(&hex_to_ascii(single_char_xor(&text, *key as u8))))
        .unwrap()
}

fn single_char_xor(text: &Vec<u8>, key: u8) -> Vec<u8> {
    xor(&text, &vec![key; text.len()])
}

fn repeating_key_xor(text: &Vec<u8>, key: &Vec<u8>) -> Vec<u8> {
    let repeated_key = (0..text.len()).map(|x| key[x % key.len()]).collect();

    xor(&text, &repeated_key)
}

fn xor(hex1: &Vec<u8>, hex2: &Vec<u8>) -> Vec<u8> {
    hex1.iter().zip(hex2.iter()).map(|(x, y)| x ^ y).collect()
}

fn chunks(position: usize, key_size: usize, text: &Vec<u8>) -> Vec<u8> {
    text.clone()
        .into_iter()
        .skip(position)
        .step_by(key_size)
        .collect()
}

fn estimate_key_size(lower_bound: usize, upper_bound: usize, text: &Vec<u8>) -> usize {
    (lower_bound..=upper_bound)
        .min_by_key(|&key_size| normalized_hamming(&text, key_size))
        .unwrap()
}

fn normalized_hamming(text: &Vec<u8>, key_size: usize) -> u32 {
    let chunks: Vec<Vec<u8>> = (0..text.len() / key_size)
        .map(|x| text[x * key_size..(x + 1) * key_size].to_vec())
        .collect();

    let hamming = (0..chunks.len() - chunks.len() % 2)
        .step_by(2)
        .map(|x| hamming_distance(&chunks[x], &chunks[x + 1]));

    let len = hamming.len() as f64;
    let sum = hamming.sum::<u32>() as f64;
    (sum / len * 1000000.0 / key_size as f64) as u32
}

fn hex_to_ascii(hex: Vec<u8>) -> String {
    hex.iter().map(|&x| x as char).collect()
}

fn eval_letter_frequency(text: &String) -> u32 {
    let mut letter_count = HashMap::with_capacity(LETTER_FREQUENCY.len());

    text.to_lowercase()
        .chars()
        .for_each(|c| *letter_count.entry(c).or_insert(0.0) += 1.0);

    (LETTER_FREQUENCY
        .keys()
        .map(|key| {
            *letter_count.entry(*key).or_default() / text.len() as f64 - LETTER_FREQUENCY[&key]
        })
        .sum::<f64>()
        .abs()
        * 1000000.0) as u32 //Convert to u32 for sorting purposes
}

fn hamming_distance(bytes1: &Vec<u8>, bytes2: &Vec<u8>) -> u32 {
    bytes1
        .iter()
        .zip(bytes2.iter())
        .map(|(x, y)| (x ^ y).count_ones())
        .sum()
}
