#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "argparse.h"

int main(int argc, const char** argv)
{
    // These notes are optional (can be NULL) and are printed as part of describing usage
    const char usage[] = "test_argparse [options] [inputs]";
    const char description[] = "Use this executable to test James' argparse library";
    const char epilog[] = "Thanks for playing!";
    
    // Command line options will be stored in these values; they are initially set to default values
    bool starts_false = false;
    bool starts_true = true;
    int integer = 1;
    int alsointeger = 2;
    size_t big_positive_number = SIZE_MAX / 2;
    double floatingpoint = 2.0;
    double sinking_point = 3.0;
    char* string = "default string";
    
    ArgumentOption options[] =
    {
            // the OPT_HELP macro maps automatically to -h / --help
            OPT_HELP("print usage and exit"),
            OPT_BOOLEAN('b', "starts_false", &starts_false, "the first test boolean with default false value"),
            OPT_BOOLEAN('c', "starts_true", &starts_true, "the second test boolean with default true value"),
            OPT_INTEGER('i', "integer", &integer, "a test integer"),
            OPT_INTEGER('j', NULL, &alsointeger, "a second test integer, without a long version"),
            OPT_SIZE('z', "unsignedlong", &big_positive_number, "size_t: an integer that can be bigger but not negative!"),
            OPT_DOUBLE('d', "double", &floatingpoint, "a test floating point value"),
            OPT_DOUBLE(0, "doubletwo", &sinking_point, "a second test floating point value, without a short version"),
            OPT_STRING('s', "string", &string, "a test string"),
            OPT_END()
    };
    
    ArgParseInfo argParseInfo = { options, usage, description, epilog };
    
    // Inputs gives the number of command line tokens that were not part of an option or its value. See the for loop below.
    int inputs = do_argparse(&argParseInfo, argc, argv);
    // This is also printed if an OPT_HELP / ArgParseOptionType.ARGPARSE_OPT_HELP option is encountered; in that case the program immediately quits
    print_usage(&argParseInfo);
    // print_state is useful for providing the user with a summary of the values of all options, regardless of whether the defaults were changed
    print_state(&argParseInfo);
    
    // argv is re-arranged so that the entries up to inputs (from above) are set to the remaining command line tokens.
    printf("\n%d inputs detected:\n", inputs);
    for(size_t i = 0; i < inputs; i++)
        printf("\t\"%s\"\n", argv[i]);
    
    return 0;
}
