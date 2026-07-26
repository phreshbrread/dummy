{ lib,
  stdenv,
  fetchFromGitHub,
  ncurses,
  gnumake
}:

stdenv.mkDerivation (finalAttrs: {
  pname   = "dummy";
  version = "1.4.3";

  # Get source from GitHub repo
  src = fetchFromGitHub {
    owner = "phreshbrread";
    repo  = "dummy";
    rev   = "v${finalAttrs.version}";
    hash  = "sha256-15WGEhWHqDLcJNf9nmrQI+fmY2MtWgHb1FBwNaF2iSI=";
  };

  nativeBuildInputs = [
    gnumake
  ];

  buildInputs = [
    ncurses
  ];

  buildPhase = ''
    runHook preBuild

    make dummy

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
