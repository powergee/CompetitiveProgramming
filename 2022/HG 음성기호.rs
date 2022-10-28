fn main() {
    let stdin = std::io::stdin();
    let mut line = String::new();
    stdin.read_line(&mut line).unwrap();
    if let Some(result) = decode(&line.trim()) {
        println!("It's HG!\n{result}");
    } else {
        println!("ERROR!");
    }
}

const CODE_TABLE: &[(char, &str); 26] = &[
    ('a', "aespa"),
    ('b', "baekjoon"),
    ('c', "cau"),
    ('d', "debug"),
    ('e', "edge"),
    ('f', "firefox"),
    ('g', "golang"),
    ('h', "haegang"),
    ('i', "iu"),
    ('j', "java"),
    ('k', "kotlin"),
    ('l', "lol"),
    ('m', "mips"),
    ('n', "null"),
    ('o', "os"),
    ('p', "python"),
    ('q', "query"),
    ('r', "roka"),
    ('s', "solvedac"),
    ('t', "tod"),
    ('u', "unix"),
    ('v', "virus"),
    ('w', "whale"),
    ('x', "xcode"),
    ('y', "yahoo"),
    ('z', "zebra"),
];

fn decode(code: &str) -> Option<String> {
    let code = code.as_bytes();
    let mut i = 0;
    let mut result = String::new();

    while i < code.len() {
        let target_idx = code[i] - ('a' as u8);
        let target = CODE_TABLE[target_idx as usize].1.as_bytes();
        if target.len() > code.len() - i {
            return None;
        }
        for j in 0..target.len() {
            if target[j] != code[i+j] {
                return None;
            }
        }
        result.push((target_idx + ('a' as u8)) as char);
        i += target.len();
    }

    Some(result)
}