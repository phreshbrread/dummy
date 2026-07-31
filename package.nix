{ lib,
  stdenv,
  fetchFromGitHub,
  ncurses,
  gnumake
}:

stdenv.mkDerivation (finalAttrs: {
  pname   = "dummy";
  version = "1.0.0";

  # Get source from GitHub repo
  src = fetchFromGitHub {
    owner = "phreshbrread";
    repo  = "dummy";
    rev   = "v${finalAttrs.version}";
  };

  nativeBuildInputs = [
    gnumake
  ];

  buildInputs = [
  ];

  buildPhase = ''
    runHook preBuild

    make

    runHook postBuild
  '';

  installPhase = ''
    runHook preInstall

    mkdir -p $out/bin
    cp bin/dummy $out/bin/

    runHook postInstall
  '';

  meta = with lib; {
    description = "Command-line tool for creating dummy files";
    homepage = "https://github.com/phreshbrread/dummy";
    license = licenses.mit;
    maintainers = with maintainers; [ phreshbrread ];
    platforms = platforms.linux;
    mainProgram = "dummy";
  };
})
