{
  description = "ChUrlOS flake for development shell";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  inputs.flake-utils.url = "github:numtide/flake-utils";
  inputs.devshell.url = "github:numtide/devshell";

  outputs = { self, nixpkgs, flake-utils, devshell }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          config.allowUnfree = true; # For clion
          overlays = [ devshell.overlays.default ];
        };

        # bintools with multilib
        bintools_multi = pkgs.wrapBintoolsWith {
          bintools = pkgs.bintools.bintools; # Get the unwrapped bintools from the wrapper
          libc = pkgs.glibc_multi;
        };

        # gcc12 with multilib
        gcc12_multi = pkgs.hiPrio (pkgs.wrapCCWith {
          cc = pkgs.gcc12.cc; # Get the unwrapped gcc from the wrapper
          libc = pkgs.glibc_multi;
          bintools = bintools_multi;
        });

        # clang14 with multilib for clang-tools
        clang14_multi = pkgs.wrapCCWith {
          cc = pkgs.clang_14.cc;
          libc = pkgs.glibc_multi;
          bintools = bintools_multi;
        };

      in {
        # devShell = pkgs.devshell.mkShell ...
        devShell = pkgs.devshell.mkShell {
          name = "ChUrlOS";

          packages = with pkgs; [
            gcc12_multi
            bintools_multi
            clang14_multi

            # Native buildinputs
            nasm
            cmake
            gnumake
            # gnutar # should be in stdenv
            # findutils
            # dosfstools
            # mtools # Generate floppy0.img etc.
            # grub2
            # xorriso
            # util-linux

            qemu # Start os in virtual machine
            gdb
            cling # To try out my bullshit implementations
            # doxygen # Generate docs + graphs
          ];

          commands = [
            {
              name = "ide";
              help = "Run clion for project";
              command = "clion &>/dev/null ./ &";
            }
            {
              name = "cpuinfo";
              help = "Show qemu i386 architecture information";
              command = "qemu-system-i386 -cpu help";
            }
          ];
        };
      });
}
