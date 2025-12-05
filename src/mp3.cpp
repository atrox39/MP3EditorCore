#include "mp3.hpp"

int GetMP3Size(FILE *file) {
  int loc = ftell(file);
  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  fseek(file, loc, SEEK_SET);
  return size;
}

bool CheckMP3(std::string fileName) {
  int fileType = fileName.length() - 4;
  std::string fileTypeStr = fileName.substr(fileType, 4);
  if (fileTypeStr == ".mp3" || fileTypeStr == ".MP3") {
    return true;
  } else {
    return false;
  }
}

std::string ID3V2Header(FILE *file) {
  char magic[3];
  fseek(file, 0, SEEK_SET);
  fread(magic, 1, 3, file);
  return std::string(magic).substr(0, 3);
}

std::string Header(FILE *file) {
  int readloc = GetMP3Size(file) - HEADER_LOCATION_V1;
  char magic[4];
  fseek(file, readloc, SEEK_SET);
  fread(magic, 1, 4, file);
  std::string str(magic);
  std::string mag(str.substr(0, 3));
  return mag;
}

int Year(FILE *file) {
  int readloc = GetMP3Size(file) - YEAR_LOCATION_V1;
  char magic[4];
  fseek(file, readloc, SEEK_SET);
  fread(magic, 1, 4, file);
  std::string str(magic);
  std::string mag(str.substr(0, 4));
  return std::stoi(mag);
}

int Track(FILE *file) {
  std::string id3v2 = ID3V2Header(file);
  int readloc = GetMP3Size(file) - (id3v2 == "ID3" ? TRACK_LOCATION_V2 : TRACK_LOCATION_V1);
  unsigned char magic;
  fseek(file, readloc, SEEK_SET);
  fread(&magic, 1, 1, file);
  return static_cast<int>(magic);
}

int Genre(FILE *file) {
  int readloc = GetMP3Size(file) - 1;
  unsigned char magic;
  fseek(file, readloc, SEEK_SET);
  fread(&magic, 1, 1, file);
  return static_cast<int>(magic);
}

std::string ReadThirty(FILE *file, int readloc) {
  char magic[30];
  fseek(file, readloc, SEEK_SET);
  fread(magic, 1, 30, file);
  std::string str(magic);
  return str;
}

void ReadMP3(FILE *file, MP3Tag &tag) {
  int readloc = GetMP3Size(file);
  tag.Title = ReadThirty(file, readloc - TITLE_LOCATION_V1);
  tag.Artist = ReadThirty(file, readloc - ARTIST_LOCATION_V1);
  tag.Album = ReadThirty(file, readloc - ALBUM_LOCATION_V1);
  tag.Year = Year(file);
  tag.Comment = ReadThirty(file, readloc - COMMENT_LOCATION_V1);
  tag.Track = Track(file);
  tag.Genre = Genre(file);
}

#ifdef __EMSCRIPTEN__
char* ReadMP3_EM(const uint8_t* data, size_t dataSize) {
  FILE* file = fmemopen((void*)data, dataSize, "rb");
  MP3Tag tag;
  ReadMP3(file, tag);
  fclose(file);
  emscripten::val jsonTags = emscripten::val::object();
  jsonTags.set("artist", tag.Artist);
  jsonTags.set("title", tag.Title);
  jsonTags.set("album", tag.Album);
  jsonTags.set("year", tag.Year);
  jsonTags.set("comment", tag.Comment);
  jsonTags.set("track", tag.Track);
  jsonTags.set("genre", tag.Genre);
  std::string jsonString = emscripten::val::global("JSON").call<std::string>("stringify", jsonTags);
  char* result = (char*)malloc(jsonString.length() + 1);
  strcpy(result, jsonString.c_str());
  return result;
}
#endif
