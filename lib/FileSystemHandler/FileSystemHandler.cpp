#include "FileSystemHandler.h"

bool FileSystemHandler::begin()
{
    if (!LittleFS.begin())
    {
        Serial.println("Failed to mount LittleFS");
        return false;
    }
    Serial.println("LittleFS mounted successfully");
    return true;
}
