//NAME: Abbas Shaikh
//NETID: ats16

This program provides an implementation of the frontend of an ILOC compiler.

To build this program, run `make build`. This will generate an executable, 412fe, which can be used to run the ILOC scanner and parser.

There are 4 command line arguments supported:
- `-h`: Prints a help menu.
- `-s <filename>`: Scans `<filename>` and prints all scanned tokens.
- `-p <filename>`: Scans and parses `<filename>` and prints number of parsed operations.
- `-r <filename>`: Scans and parses `<filename>` and prints the intermediate representation.

If no command line argument is provided, a filename must still be provided, and the behavior will default to that of the `-p` flag. 