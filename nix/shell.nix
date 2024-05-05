{ pkgs ? import <nixpkgs> { } }:
with pkgs;
mkShell {
  buildInputs = [
    stdenv
    jflap
  ];

  shellHook = ''
    # ...
  '';
}
