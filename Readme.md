##Command Timer
Used to time the duration of commands, to get an average of duration from command execution to finish,
for the specified amount of iterations.
The execution of each command is alternated.
The result is in seconds.

I'm not sure if the results are 100% accurate in terms of real time elapsed between
execution and termination of a program, but they are very consistent with each other, and with the UNIX command *time*.

###Usage:
commandTimer "command 1" "command 2" [number of iterations]
