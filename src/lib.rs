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
    pub size: u128,
    pub unit: char,
    pub destination: PathBuf,
}

pub fn parse_cli_args() -> Args {
    return Args::parse();
}

