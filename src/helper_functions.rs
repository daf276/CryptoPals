fn encode_base64(input: Vec<u8>) -> String{
    let mut output = String::new();

    for i in (0..(input.len()-2)).step_by(3){
        let current_bytes: u32 = (input[i] as u32) << 16 | (input[i + 1] as u32) << 8 | input[i + 2] as u32;

        output.push(byte_to_base64((current_bytes >> 18 & 0b00111111) as u8));
        output.push(byte_to_base64((current_bytes >> 12 & 0b00111111) as u8));
        output.push(byte_to_base64((current_bytes >> 6 & 0b00111111) as u8));
        output.push(byte_to_base64((current_bytes & 0b00111111) as u8));
    }

    output
}

fn byte_to_base64(number: u8) -> char {
    //Converts one byte to one base64 character
    //Not that only the lowest 6 bits should ever be non-zero
    return match number {
        0..=25 => (number + 65) as char,
        26..=51 => (number + 71) as char,
        52..=61 => (number - 4) as char,
        62 => (number - 19) as char,
        63 => (number - 16) as char,
        _ => unreachable!(),
    }
}