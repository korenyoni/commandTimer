#include <iostream>
#include <cstdio>
#include <string>
#include <ctime>
#include <chrono>

/* program that will give an average elapsed time for the execution of two commands
 * for the specified amount of iterations*/
const std::string USAGE("Usage: commandTimer \"command 1\" \"command 2\" [number of iterations]");
const char DOUBLE_QUOTE = '\"';
int numberIterations = 0;
typedef std::chrono::high_resolution_clock Clock;
std::string commandsArray[2];
/* returns time, in seconds, that it took to execute the specified command */
double getTime(std::string command)
{
    auto timer = Clock::now();
    std::system(command.c_str());
    auto timeTaken = Clock::now() - timer;
    double time = double(timeTaken.count() / 1000000) / 1000;
    // std::chrono::high_resolution_clock::now() returns a number in nanoseconds since the epoch.
    // this number, as a floating point, is represented as a power. So we should convert the number
    // to miliseconds, (divide it by 1000000) then divide it by 1000 to represent it as a number of seconds.
    return time;
}
/* returns the average time for each command as a pair, in order */
std::pair<double,double> timeCommands(std::string commandOne, std::string commandTwo, int numberIterations)
{
    double commandOneAverageTime = 0;
    double commandTwoAverageTime = 0;
    for (int i = 0; i < numberIterations; i++)
    {
        commandOneAverageTime += getTime(commandOne);
        commandTwoAverageTime += getTime(commandTwo);
    }
    commandOneAverageTime /= numberIterations;
    commandTwoAverageTime /= numberIterations;
    return std::pair<double,double>(commandOneAverageTime,commandTwoAverageTime);
}
/* pass argc and argv[] to parse the commands entered by the user */
// also delegate this function in order to specify invalid input
// returns true if the program should continue
// returns false otherwise
bool handleAruments(int argc, char * argv[])
{
    bool abortProgram = false;
    if (argc < 4)
        // if the user executed the command without arguments
        // print a string explaining how to use the program
    {
        std::cout << USAGE << std::endl;
        abortProgram = true;
    }
    else
    {
        commandsArray[0] = argv[1];
        commandsArray[1] = argv[2];
        try
        {
            numberIterations = std::stoi(argv[3]);
        }
        catch (std::invalid_argument)
        {
            std::cout << USAGE << std::endl;
            abortProgram = true;
        }
    }
    return !abortProgram;
}
/* MAIN */
int main(int argc, char * argv[])
{
    if (handleAruments(argc, argv))
    {
        std::pair<double,double> commandsAverageTimesPair = timeCommands(commandsArray[0], commandsArray[1], numberIterations);
        std::cout << "Command one average time (seconds): " << commandsAverageTimesPair.first << std::endl
        << "Command two average time (seconds): " << commandsAverageTimesPair.second << std::endl;
    }
}
