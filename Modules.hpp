#pragma once

bool COPY(const char* fileSrc, const char* fileDest, char mode = 'w');
void _displayProcessBar(size_t percent);
long long _fileSize(const char* filename);
