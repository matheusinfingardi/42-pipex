
# PIPEX

Intro: This project is the discovery in detail and by programming of a UNIX mechanism that you already know.

Mandatory part: This project is about handling pipes.

The program is executed as follows:
./pipex file1 cmd1 cmd2 file2

It must take 4 arguments:
   * file1 and file2 are file names.
   * cmd1 and cmd2 are shell commands with their parameters.

It must behave exactly the same as the shell command below:
$> < file1 cmd1 | cmd2 > file2

**Example:**
$> ./pipex infile "ls -l" "wc -l" outfile

**Behave like:**
< infile ls -l | wc -l > outfile
