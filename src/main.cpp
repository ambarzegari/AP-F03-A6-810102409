#include "UTaste.hpp"

int main(int argc, char *argv[])
{
    UTaste utaste;
    utaste.GetDataFromDistrictsFile(argv[2]);
    utaste.GetDataFromResturantsFile(argv[1]);
    utaste.GetDataFromDiscountsFile(argv[3]);
    utaste.IoHandler();
    return 0;
}