#include <iostream>
#include <fstream>
#include <string.h>
#include <zip.h>

using namespace std;

char sourceFileName[10] = "input.txt";
char archiveFileName[14] = "input.txt.zip";

int main()
{
    // create the ZIP archive
    int err = 0;
    zip *z = zip_open(archiveFileName, ZIP_CREATE, &err);
    if(err)
    {
        cout << "Could not open or create archive" << endl;
        return -1;
    }
    cout << "Zip created" << endl;

    zip_source *source = zip_source_file(z, sourceFileName, 0, 0);
    cout << "Zip source created" << endl;

    zip_add(z, sourceFileName, source);
    cout << "Zip archive created" << endl;

    zip_close(z);

    return 0;
}

