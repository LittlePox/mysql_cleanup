#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

const char* unwanted_token[] = {"\n", "DROP", "LOCK", "UNLOCK", "--", "/*!"};

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "%s", "No input file.");
        return 0;
    }
    if (strstr(argv[1], "_") == NULL)
    {
        fprintf(stderr, "%s", "File name does not contain \'_\'.");
        return 0;
    }
    FILE *fin = fopen(argv[1], "r");
    char *outfile = strstr(argv[1], "_") + 1;
    FILE *fout = fopen(outfile, "w");
    char line[1000000];
    while (fgets(line, 1000000, fin) != NULL)
    {
        bool unwanted = false;
        for (char *token : unwanted_token)
        {
            if (strstr(line, token) == line)
            {
                unwanted = true;
                break;
            }
        }
        if (unwanted)
        {
            continue;
        }
        fprintf(fout, "%s", line);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

