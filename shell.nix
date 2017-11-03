with import <nixpkgs> {};

(python.withPackages (ps: [ps.pyserial])).env
