# Usage
Place you rom inside one of these directories. If you hack fire red, name it BPRE.gba; if you hack emerald, BPEE.gba.  
Then modify the "main.s" file to specify the addres it will be inserted, and run either "make bpre" or "make bpee".  
A new rom will appear, named "build/\[ROM CODE\]/rom.gba".

# Dependencies
- DevkitARM
- Armips
- Cygwin (on Windows)
