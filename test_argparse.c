#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "argparse.h"

int main(int argc, const char** argv)
{
    
    const char usage[] = "test_argparse [options] [inputs]";
    const char description[] = "Use this executable to test James' argparse library";
    const char epilog[] = "Thanks for playing!";
    
    
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
    
    ArgParseInfo argParseInfo = { options, usage, description, epilog};
    
    int inputs = do_argparse(&argParseInfo, argc, argv);
    print_usage(&argParseInfo);
    print_state(&argParseInfo);
    printf("\n%d inputs detected:\n", inputs);
    for(size_t i = 0; i < inputs; i++)
        printf("\t\"%s\"\n", argv[i]);
    
    return 0;
}
