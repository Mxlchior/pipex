*This project has been created as part of the 42 curriculum by megrelli.*

💡 Description

Pipex is a C programming project whose goal is to recreate the exact behavior of the shell pipe operator | combined with file redirections.

This project introduces important concepts such as:

- Process creation (fork)
- File descriptors and redirections (open, close, dup2)
- Inter-process communication (pipe)
- Program execution and environment variables (execve, access)
- Process status and error handling (waitpid, perror)

The program must:

- Behave exactly like the shell command: < infile cmd1 | cmd2 > outfile
- Parse commands and their arguments accurately, natively respecting single (' ') and double (" ") quotes
- Manage errors and exit codes exactly like Bash (e.g., returning 127 for "command not found")
- Handle absolute and relative paths for executables
- Manage memory correctly without leaks and ensure all file descriptors are properly closed to prevent deadlocks

🚀 Instructions

Compile the project using the provided Makefile:
make

To execute the program, it requires exactly 4 arguments:
./pipex infile "cmd1" "cmd2" outfile

Example:
./pipex infile "ls -l" "wc -l" outfile
(This is strictly equivalent to: < infile ls -l | wc -l > outfile)

📚 Resources

    "Unix Processes in C" Video playlist by CodeVault : https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY

    Linux Programmer's Manual (man pages) for pipe, fork, dup2, execve, waitpid, and access.

    AI (Gemini pro 3.1) was used as an interactive tutor for conceptual clarification (e.g., decoding waitpid status macros, understanding zombie processes) and structuration of this README.md file.