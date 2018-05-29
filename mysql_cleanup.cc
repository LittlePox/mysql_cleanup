#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
using namespace std;

const char* unwanted_token[] = {"\n", "DROP", "LOCK", "UNLOCK", "--", "/*!"};

vector<string> find_all_sql();

int main(int argc, char** argv)
{
    vector<string> all_sql = find_all_sql();
    for (string &file : all_sql)
    {
        const char *infile = file.c_str();
        FILE *fin = fopen(infile, "r");
        const char *outfile = strstr(infile, "_") + 1;
        FILE *fout = fopen(outfile, "w");
        char line[1000000];
        while (fgets(line, 1000000, fin) != NULL)
        {
            bool unwanted = false;
            for (const char *token : unwanted_token)
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
        remove(infile);
    }
    return 0;
}

vector<string> find_all_sql()
{
    vector<string> res;
    namespace fs = boost::filesystem;
    fs::path full_path(fs::initial_path<fs::path>());
    fs::directory_iterator end_itr;
    for (fs::directory_iterator item(full_path); item != end_itr; item ++) {
        if (fs::is_regular_file(item->status())) {
            wstring filename_w = item->path().filename().native();
            string filename = string(filename_w.begin(), filename_w.end());
            if (filename.find("_")!= string::npos && filename.find(".sql") != string::npos)
            {
                res.push_back(filename);
            }
        }
    }
    return res;
}


