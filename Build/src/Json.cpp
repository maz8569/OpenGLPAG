#include "Json.h"

int GameEngine::Json::print()
{
    // 1. Parse a JSON text string to a document.
    const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    printf("Original JSON:\n %s\n", json);


    if (document.Parse(json).HasParseError())
        return 1;
    return 0;
}
