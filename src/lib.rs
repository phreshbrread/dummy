use clap::Parser;
use std::path::PathBuf;

pub enum InvalidArgType {
    InvalidCount,
    InvalidSize,
    InvalidUnit,
    InvalidPath,
}

#[derive(Debug, Parser)]
pub struct Args {
    /// Enable to use decimal values instead of binary
    #[arg(short, long)]
    pub decimal: bool,
    /// Number of <UNIT>s the output file should be
    pub size: u64,
    /// Can be either (b)yte, (k)ilobyte, (m)egabyte, (g)igabyte or (t)erabyte
    pub unit: char,
    /// Path to where the file should be written. Example: "~/Downloads/dummy-test.txt"
    pub destination: PathBuf,
}

pub fn parse_cli_args() -> Args {
    return Args::parse();
}
