use std::path::{Path, PathBuf};

#[derive(Debug)]
pub struct OutputFile {
    path: PathBuf,
    size: u128,
}

impl OutputFile {
    pub fn new(p: &str, s: u128) -> Self {
        let of = OutputFile {
            path: p.into(),
            size: s,
        };

        return of;
    }
}
