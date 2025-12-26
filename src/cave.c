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

void readbuf(const char *path, char *buf, size_t *size)
{
    FILE *file = fopen(path, "rb");
    if (!file)
    {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    rewind(file);

    buf = (char *)malloc(*size);
    if (!buf)
    {
        perror("Failed to allocate memory");
        fclose(file);
        return;
    }

    fread(buf, 1, *size, file);
    fclose(file);
}

bool check_flags(char *argv[], int argc)
{
    bool has_flag = false;
    bool has_input = false;
    for (int i = 1; i < argc; i++)
    {
        for (char *p = argv[i]; *p != '\0'; p++)
        {
            if (*p == '-')
            {
                has_flag = true;
                if (*(p + 1) == 'i')
                {
                    has_input = true;
                }
                break;
            }
        }
    }
    return has_flag && has_input;
}

struct command_data parse_flags(char *argv[], int argc)
{
    struct command_data data;
    data.verbose = false;
    data.output.state = ABSENT;

    for (int i = 1; i < argc; i++)
    {
        for (char *p = argv[i]; *p != '\0'; p++)
        {
            if (*p == '-')
            {
                p++;
                switch (*p)
                {
                case 'v':
                    data.verbose = true;
                    break;
                case 'o':
                    if (*(p + 1) == '\0' && (i + 1) < argc)
                    {
                        data.output.str = argv[i + 1];
                        data.output.state = PRESENT;
                        i++;
                    }
                    else if (*(p + 1) != '\0')
                    {
                        data.output.str = p + 1;
                        data.output.state = PRESENT;
                    }
                    break;
                case 'i':
                    if (*(p + 1) == '\0' && (i + 1) < argc)
                    {
                        data.input_path = argv[i + 1];
                        i++;
                    }
                    else if (*(p + 1) != '\0')
                    {
                        data.input_path = p + 1;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    char file_path[PATH_MAX];
    char *buffer;
    size_t size;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s -i <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!check_flags(argv, argc))
    {
        fprintf(stderr, "Invalid flags provided.\n");
        return EXIT_FAILURE;
    }

    struct command_data data;
    parse_flags(argv, argc);

    file_path[PATH_MAX - 1] = '\0';
    readbuf(file_path, buffer, &size);
    return EXIT_SUCCESS;
}