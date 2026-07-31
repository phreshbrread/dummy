{
  description = "Command-line tool for creating dummy files";

  inputs.nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    packages.${system} = rec {
      dummy = pkgs.callPackage ./package.nix {};
      default = dummy;
    };

    devShells.${system}.default = pkgs.mkShell {
      # Grab dependencies from package.nix
      inputsFrom = [ self.packages.${system}.dummy ];

      # Extra tools just for dev environment
      nativeBuildInputs = with pkgs; [
        gdb
      ];
    };
  };
}
