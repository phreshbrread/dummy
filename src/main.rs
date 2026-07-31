mod out;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    dbg!(&args);

    if args.len() != 4 {
        invalid_args();
    }

    let s: u128 = args[1].parse().unwrap();
    let u: char = args[2].parse().unwrap();

    let of = out::OutputFile::new(s, u, &args[3]);
    dbg!(&of);

    match out::OutputFile::write(of) {
        Ok(_) => println!("Success"),
        Err(e) => println!("Failed: {:}", e),
    };
}

fn invalid_args() -> ! {
    println!("Usage: dummy [size] [unit] [destination]");
    std::process::exit(1);
}
