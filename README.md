# ArgParse
A simple C library to parse flags and values from command line input and provide human-understandable feedback about usage.

## Bevavior and Features
* Command line options can have short (single character preceded by '-') and/or long (string preceeded by '--') forms. Only one is required. Each option has a description, which can be displayed (e.g., when something goes wrong or the user passes `--help`).
* Options can be boolean flags or require a value. The value can be a string, an int, an unsigned int (size_t) or double -- see the `enum ArgumentType` in `argparse.h` for all possible options.
* Values for options are parsed from either the next token (short or long form of the option) or can appear in the --long-form=value notation.
* Tokens that are not options are assumed to be the main program arguments and are left in argv for the program to sort out.

## Example implementation
From `test_argparse.c`
```C
int main(int argc, const char** argv)
{
    
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
    // This is also printed if an OPT_HELP / ArgumentType.ARGPARSE_OPT_HELP option is encountered; in that case the program immediately quits
    print_usage(&argParseInfo);
    // print_state is useful for providing the user with a summary of the values of all options, regardless of whether the defaults were changed
    print_state(&argParseInfo);
    
    // argv is re-arranged so that the entries up to inputs (from above) are set to the remaining command line tokens.
    printf("\n%d inputs detected:\n", inputs);
    for(size_t i = 0; i < inputs; i++)
        printf("\t\"%s\"\n", argv[i]);
    
    return 0;
}
```

## Credits
The spirit of this project was very much inspired by having used the [Python language's argument parser](https://docs.python.org/3/library/argparse.html) and perusing [GitHub user cofyc's argparse implementation](https://github.com/cofyc/argparse). The latter's use of an array of macros to create the options list was too good not to imitate.
