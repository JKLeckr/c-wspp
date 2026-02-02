# justfile

set windows-shell := ["powershell.exe", "-NoLogo", "-Command"]

proj_name := 'c-wspp'

default:
    @just --list

setup:
    conan install . --profile:all profiles/clang-windows-static --output-folder=build --build=missing
