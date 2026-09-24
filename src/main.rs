mod output;

use crate::output::OutputFile;
use dummy::*;

fn main() {
    let args = parse_cli_args();
    dbg!(&args);

    let s = args.size;
    let u = args.unit.to_ascii_lowercase();
    match u {
        'b' | 'k' | 'm' | 'g' | 't' => (),
        _ => panic!(),
    };

    let out_file = OutputFile::new(s, u, args.destination);
    dbg!(&out_file);

    match OutputFile::write(out_file) {
        Ok(_) => println!("Success"),
        Err(e) => println!("Failed: {:}", e),
    };
}
