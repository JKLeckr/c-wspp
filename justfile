# justfile

set windows-shell := ["powershell.exe", "-NoLogo", "-Command"]

proj_name := 'c-wspp'

default:
    @just --list

win64-setup:
    conan install . --profile:all profiles/msvc-windows-static --output-folder=build --build=missing

win32-setup:
    conan install . --profile:all profiles/msvc-windows-x86-static --output-folder=build --build=missing
