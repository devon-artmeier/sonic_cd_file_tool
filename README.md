# Sonic CD File Tool

[![Build Status](https://github.com/devon-artmeier/sonic_cd_file_tool/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/devon-artmeier/sonic_cd_file_tool/actions/workflows/cmake-multi-platform.yml)

This is a tool to check and patch files for the Sonic CD disassembly to ensure bit-perfectness.

## Usage

    Usage: sonic_cd_file_tool -r [region] -i [ip] -s [sp] -p [patches] [folder]
               -r [region]  - Region setting (Japan/USA/Europe)
               -i [ip]      - Initial program file
               -s [sp]      - System program file
               -p [patches] - Patches folder
               [folder]     - Folder to scan
