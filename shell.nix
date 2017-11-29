with import <nixpkgs> {};

(python.withPackages (ps: [ps.pyserial ps.matplotlib ps.numpy ps.wxPython])).env
