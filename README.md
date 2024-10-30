# Sonic CD File Tool

[![Build Status](https://github.com/devon-artmeier/sonic_cd_file_tool/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/devon-artmeier/sonic_cd_file_tool/actions/workflows/cmake-multi-platform.yml)

This is a tool to check and patch files for the Sonic CD disassembly.

## Usage

Copy the patches folder to where your built executable is located.

    Usage: sonic_cd_file_tool -r [region] -i [ip] -s [sp] [folder]
               -r [region] - Region setting (Japan/USA/Europe)
               -i [ip]     - Initial program file
               -s [sp]     - System program file
               [folder]    - Folder to scan
