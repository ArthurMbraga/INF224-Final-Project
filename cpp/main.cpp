#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "headers/Factory.h"
#include "headers/Film.h"
#include "headers/Group.h"
#include "headers/Photo.h"
#include "headers/Video.h"
#include "tcpserver/tcpserver.h"

using namespace std;

typedef shared_ptr<Film> FilmPtr;

string imagePath = "./media/IMG_1091.jpg";
string videoPath = "./media/test.mp4";

const int PORT = 3331;

string trimString(const string &str) {
  size_t start = str.find_first_not_of(" \t");
  size_t end = str.find_last_not_of(" \t");
  if (start == string::npos || end == string::npos) {
    return "";
  }
  return str.substr(start, end - start + 1);
}

int main(int argc, char *argv[]) {
  Factory factory;

  auto photo1 = factory.createPhoto("Photo1", "./media/photo1.jpg", 2.0, 1.0);
  auto photo2 = factory.createPhoto("Photo2", "./media/photo2.jpg", 3.0, 2.0);
  auto photo3 = factory.createPhoto("Photo3", "./media/photo3.jpg", 4.0, 3.0);

  auto video = factory.createVideo("Video1", "./media/video1.mp4", 10);

  auto film = factory.createFilm("Film1", "./media/video2.mp4", 20);
  int chapters[] = {5, 10, 15};
  film->setChapters(chapters, 3);

  auto group1 = factory.createGroup("Group1");
  group1->push_back(photo1);
  group1->push_back(photo2);
  group1->push_back(photo3);

  auto group2 = factory.createGroup("Group2");
  group2->push_back(video);
  group2->push_back(film);

  map<string, function<string(const std::string &)>> serverCommands;

  serverCommands["find group"] = [&](string const &request) {
    return factory.findGroup(request);
  };

  serverCommands["find multimedia"] = [&](string const &request) {
    return factory.findMultimedia(request);
  };

  serverCommands["play multimedia"] = [&](string const &request) {
    return factory.playMultimedia(request);
  };

  TCPServer server([&](string const &request, string &response) {
    stringstream strStream(request);
    string command = "";

    while (true) {
      string token;
      strStream >> token;

      if (command.length())
        command += " ";
      command += token;

      auto commandIterator = serverCommands.find(command);

      if (commandIterator != serverCommands.end()) {
        auto commandFunction = commandIterator->second;

        string commandInput = "";
        getline(strStream, commandInput);

        response = commandFunction(trimString(commandInput));
        break;
      } else if (strStream.eof()) {
        response = "Invalid Command";
        break;
      }
    }

    // return false would close the connection with the client
    return true;
  });

  cout << "Starting Server on port " << PORT << endl;

  int status = server.run(PORT);

  if (status < 0) {
    cerr << "Could not start Server on port " << PORT << endl;
    return 1;
  }

  return 0;
}
