use std::{
    fs::File,
    io,
    path::{Path, PathBuf},
};

#[derive(Debug)]
pub struct OutputFile {
    size: u128,
    unit: char,
    path: PathBuf,
}

impl OutputFile {
    pub fn new(s: u128, u: char, p: PathBuf) -> Self {
        let of = OutputFile {
            size: s,
            unit: u,
            path: p,
        };

        return of;
    }

    // TODO: Set size properly based on unit

    pub fn write(of: OutputFile) -> Result<(), io::Error> {
        let mut file = File::create(of.path)?;
        file.set_len(of.size as u64)?;
        return Ok(());
    }
}
