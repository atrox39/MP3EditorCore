#pragma once
#ifndef MP3_EXPORTS
#define MP3_EXPORTS
#include<iostream>
#include<fstream>
#include<string>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#endif

#define HEADER_LOCATION_V1 128
#define TITLE_LOCATION_V1 125
#define ARTIST_LOCATION_V1 95
#define ALBUM_LOCATION_V1 65
#define YEAR_LOCATION_V1 35
#define COMMENT_LOCATION_V1 31
#define TRACK_LOCATION_V1 29
#define TRACK_LOCATION_V2 2
#define GENRE_LOCATION_V1 1

struct MP3Tag {
  std::string Artist;
  std::string Title;
  std::string Album;
  int Year;
  std::string Comment;
  int Track;
  int Genre;
};

int GetMP3Size(FILE *file);
bool CheckMP3(std::string fileName);
std::string ReadThirty(FILE *file);
std::string ID3V2Header(FILE *file);
std::string Header(FILE *file);
int Year(FILE *file);
int Track(FILE *file);
int Genre(FILE *file);
void ReadMP3(FILE *file, MP3Tag &tag);
void WriteArtist(FILE *file, const std::string &artist);
void WriteTitle(FILE *file, const std::string &title);
void WriteAlbum(FILE *file, const std::string &album);
void WriteYear(FILE *file, const int &year);
void WriteComment(FILE *file, const std::string &comment);
void WriteTrack(FILE *file, const int &track);
void WriteGenre(FILE *file, const int &genre);

#ifdef __EMSCRIPTEN__
extern "C" {
  EMSCRIPTEN_KEEPALIVE
  char* ReadMP3_EM(const uint8_t* data, size_t dataSize);
}
#endif

#endif
