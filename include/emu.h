#ifndef EMU_H
#define EMU_H

/******
 * Get the size of a program array using the END instruction as the last one.
 * 
 * @param prog An array containing a program.
 * 
 * @return the size of the program (from array index 0 until the first appearance of END) as an integer (int).
 ******/
int getProgSize(int *prog);

/******
 * Run a program.
 * 
 * @param prog An array containing a program.
 ******/
void run(int *prog);

/******
 * Read and run a program from a file.
 * 
 * @param filename The path to the file. can be only the file name if it's in the current directory.
 ******/
void run_from_file(const char *filename);

#endif // EMU_H
