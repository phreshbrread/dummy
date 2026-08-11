mod out;

enum InvalidArgType {
    InvalidCount,
    InvalidSize,
    InvalidUnit,
    InvalidPath,
}

fn main() {
    let args: Vec<String> = std::env::args().collect();
    dbg!(&args);
    println!();

    if args.len() != 4 {
        show_help(InvalidArgType::InvalidCount);
    }

    let s: u128 = match args[1].parse() {
        Ok(o) => o,
        Err(_) => show_help(InvalidArgType::InvalidSize),
    };

    let u: char = match args[2].to_lowercase().parse() {
        Ok(o) => match o {
            'b' => 'b',
            'k' => 'k',
            'm' => 'm',
            'g' => 'g',
            't' => 't',
            _ => show_help(InvalidArgType::InvalidUnit),
        },
        Err(_) => show_help(InvalidArgType::InvalidUnit),
    };

    let out_file = out::OutputFile::new(s, u, &args[3]);
    dbg!(&out_file);

    match out::OutputFile::write(out_file) {
        Ok(_) => println!("Success"),
        Err(e) => println!("Failed: {:}", e),
    };
}

fn show_help(ivt: InvalidArgType) -> ! {
    match ivt {
        InvalidArgType::InvalidCount => println!("Incorrect argument count."),
        InvalidArgType::InvalidUnit  => println!("Invalid unit."),
        InvalidArgType::InvalidSize  => println!("Invalid size."),
        InvalidArgType::InvalidPath  => println!("Invalid path."),
    };

    println!("Usage: dummy [size] [unit] [destination]");
    std::process::exit(1);
}
