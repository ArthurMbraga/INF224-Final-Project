#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <memory>
#include <sstream>

#include "Film.h"
#include "Group.h"
#include "Multimedia.h"
#include "Photo.h"
#include "Video.h"

typedef std::shared_ptr<Photo> PhotoPtr;
typedef std::shared_ptr<Film> FilmPtr;
typedef std::shared_ptr<Video> VideoPtr;
typedef std::shared_ptr<Multimedia> MultimediaPtr;
typedef std::shared_ptr<Group> GroupPtr;

/**
 * @class Factory
 * @brief A class that represents a factory for creating and managing multimedia objects and groups.
 *
 * The Factory class provides methods for creating photos, videos, films, and groups. It also allows
 * searching, playing, and removing multimedia objects and groups.
 */
class Factory {
private:
  std::map<std::string, MultimediaPtr> multimediaMap;
  std::map<std::string, GroupPtr> groupMap;

public:
  PhotoPtr createPhoto(std::string name, std::string path, double latitude,
                       double longitude) {
    PhotoPtr photo(new Photo(name, path, latitude, longitude));
    multimediaMap[name] = photo;
    return photo;
  }

  VideoPtr createVideo(std::string name, std::string path, int duration) {
    VideoPtr video(new Video(name, path, duration));
    multimediaMap[name] = video;
    return video;
  }

  FilmPtr createFilm(std::string name, std::string path, int duration) {
    FilmPtr film(new Film(name, path, duration));
    multimediaMap[name] = film;
    return film;
  }

  GroupPtr createGroup(std::string name) {
    GroupPtr group(new Group(name));
    groupMap[name] = group;
    return group;
  }

  std::string findMultimedia(const std::string &name) {
    auto multimedia = multimediaMap.find(name);
    std::stringstream output;

    if (multimedia != multimediaMap.end()) {
      multimedia->second->display(output);
    } else {
      output << "Multimedia not found";
    }

    return output.str();
  }

  std::string playMultimedia(const std::string &name) {
    auto multimedia = multimediaMap.find(name);
    std::stringstream output;

    if (multimedia != multimediaMap.end()) {
      multimedia->second->play();
      output << "Playing multimedia";
    } else {
      output << "Multimedia not found";
    }

    return output.str();
  }

  std::string removeMultimedia(const std::string &name) {
    auto multimedia = multimediaMap.find(name);
    std::stringstream output;

    if (multimedia != multimediaMap.end()) {
      multimediaMap.erase(multimedia);

      for (auto group : groupMap)
        for (auto multimedia : *group.second)
          if (multimedia->getName() == name)
            group.second->remove(multimedia);

      output << "Multimedia removed";
    } else {
      output << "Multimedia not found";
    }

    return output.str();
  }

  std::string findGroup(const std::string &name) {
    auto group = groupMap.find(name);
    std::stringstream output;

    if (group != groupMap.end()) {
      group->second->display(output);
    } else {
      output << "Group not found";
    }

    return output.str();
  }

  std::string removeGroup(const std::string &name) {
    auto group = groupMap.find(name);
    std::stringstream output;

    if (group != groupMap.end()) {
      groupMap.erase(group);
      output << "Group removed";
    } else {
      output << "Group not found";
    }

    return output.str();
  }
};

#endif // FACTORY_H