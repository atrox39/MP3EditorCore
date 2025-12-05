#include "mp3.hpp"

int main() {
  std::string fileName = "demo/example.mp3";
  if (CheckMP3(fileName)) {
    FILE *file = fopen(fileName.c_str(), "rb");
    if (file) {
      MP3Tag tag;
      int size = GetMP3Size(file);
      std::cout << "MP3 file size: " << size << " bytes" << std::endl;
      std::string header = Header(file);
      std::string id3v2header = ID3V2Header(file);
      std::cout << "ID3v2 Header: " << id3v2header << std::endl;
      if (header == "TAG" || id3v2header == "ID3") {
        std::cout << "Valid MP3 file with ID3v1 tag." << std::endl;
        ReadMP3(file, tag);
        std::cout << "Artist: " << tag.Artist << std::endl;
        std::cout << "Title: " << tag.Title << std::endl;
        std::cout << "Album: " << tag.Album << std::endl;
        std::cout << "Year: " << tag.Year << std::endl;
        std::cout << "Comment: " << tag.Comment << std::endl;
        std::cout << "Track: " << tag.Track << std::endl;
        std::cout << "Genre: " << tag.Genre << std::endl;
      } else {
        std::cout << "No ID3v1 tag found." << std::endl;
      }
      fclose(file);
    } else {
      std::cerr << "Failed to open file: " << fileName << std::endl;
    }
  } else {
    std::cerr << "Invalid MP3 file: " << fileName << std::endl;
  }
  return 0;
}
