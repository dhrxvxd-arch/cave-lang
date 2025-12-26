#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <linux/limits.h>

struct str_optional
{
    union
    {
        char *str;
        void *nullopt;
    };
    enum optional_state
    {
        PRESENT,
        ABSENT
    } state;
};

struct command_data
{
    bool verbose;
    char *input_path;
    struct str_optional output;
};

void readbuf(const char *path, char **buf, size_t *size)
{
    FILE *file = fopen(path, "rb");
    if (!file)
        return;

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    rewind(file);

    *buf = malloc(*size);
    if (!*buf)
    {
        fclose(file);
        return;
    }

    fread(*buf, 1, *size, file);
    fclose(file);
}

bool check_flags(char *argv[], int argc)
{
    bool has_flag = false;
    bool has_input = false;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            has_flag = true;
            if (strchr(argv[i], 'i'))
                has_input = true;
        }
    }

    return has_flag && has_input;
}

struct command_data parse_flags(char *argv[], int argc)
{
    struct command_data data = {0};
    data.output.state = ABSENT;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
            continue;

        char *p = argv[i] + 1;
        while (*p)
        {
            switch (*p)
            {
            case 'v':
                data.verbose = true;
                break;
            case 'o':
                if (*(p + 1))
                {
                    data.output.str = p + 1;
                    data.output.state = PRESENT;
                    p += strlen(p + 1);
                }
                else if (i + 1 < argc)
                {
                    data.output.str = argv[++i];
                    data.output.state = PRESENT;
                }
                break;
            case 'i':
                if (*(p + 1))
                {
                    data.input_path = p + 1;
                    p += strlen(p + 1);
                }
                else if (i + 1 < argc)
                {
                    data.input_path = argv[++i];
                }
                break;
            default:
                break;
            }
            p++;
        }
    }

    return data;
}

int main(int argc, char *argv[])
{
    char *buffer = NULL;
    size_t size = 0;

    if (argc < 2)
        return EXIT_FAILURE;

    if (!check_flags(argv, argc))
        return EXIT_FAILURE;

    struct command_data data = parse_flags(argv, argc);
    if (!data.input_path)
        return EXIT_FAILURE;

    readbuf(data.input_path, &buffer, &size);

    free(buffer);
    return EXIT_SUCCESS;
}
