use std::{
    fs::File,
    io,
    path::PathBuf,
};

#[derive(Debug)]
pub struct OutputFile {
    size: u64,
    unit: char,
    path: PathBuf,
}

impl OutputFile {
    pub fn new(s: u64, u: char, p: PathBuf) -> Self {
        let of = OutputFile {
            size: s,
            unit: u,
            path: p,
        };

        return of;
    }

    pub fn write(of: OutputFile) -> Result<(), io::Error> {
        let file = File::create(of.path)?;

        let final_size: u64 = of.size * match of.unit {
            'b' => 1,
            'k' => 1024,
            'm' => 1024_u64.pow(2),
            'g' => 1024_u64.pow(3),
            't' => 1024_u64.pow(4),
            _ => 0, // Unit validity check is done before calling this function
        };

        file.set_len(final_size)?;

        return Ok(());
    }
}

