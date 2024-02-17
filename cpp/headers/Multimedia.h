#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <iostream>
#include <string>

#include "Factory.h"

/**
 * @class Multimedia
 * @brief The Multimedia class represents a generic multimedia object.
 * 
 * This class provides a base implementation for multimedia objects, such as images, videos, and audio files.
 * It contains common attributes and methods that can be inherited by specific multimedia types.
 */
class Multimedia {
private:
  friend class Factory;

  std::string name{};
  std::string path{};

protected:
  Multimedia(){};
  Multimedia(std::string name, std::string path) : name(name), path(path) {}

public:
  virtual ~Multimedia() {
    std::cout << "Multimedia object " << name << " deleted" << std::endl;
  };

  std::string getName() const { return name; };
  void setName(std::string name) { this->name = name; };

  std::string getPath() const { return path; };
  void setPath(std::string path) { this->path = path; };

  virtual void display(std::ostream &stream) const {
    stream << "Name: " << name << "; ";
    stream << "Path: " << path << "; ";
  };

  virtual void play() const = 0;
};

#endif // MULTIMEDIA_H
