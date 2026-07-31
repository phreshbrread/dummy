mod out;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    dbg!(&args);

    if args.len() != 4 {
        invalid_args();
    }

    let of = out::OutputFile::new("Test", 4);

    dbg!(&of);
}

fn invalid_args() -> ! {
    println!("Usage: dummy [size] [unit] [destination]");
    std::process::exit(1);
}
