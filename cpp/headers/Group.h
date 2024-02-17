#ifndef GROUP_H
#define GROUP_H

#include <list>
#include <memory>

#include "Factory.h"
#include "Multimedia.h"

typedef std::shared_ptr<Multimedia> MultimediaPtr;

/**
 * @class Group
 * @brief Represents a group of multimedia objects.
 * 
 * This class inherits from std::list<MultimediaPtr> and provides additional functionality
 * for managing a group of multimedia objects. It allows adding, removing, and displaying
 * multimedia objects in the group.
 */
class Group : public std::list<MultimediaPtr> {

private:
  friend class Factory;
  std::string name{};

protected:
  /**
   * @brief Protected constructor for creating a Group object with a given name.
   * @param name The name of the group.
   */
  Group(std::string name) : std::list<MultimediaPtr>(), name(name) {}

public:
  /**
   * @brief Displays the group's name and the multimedia objects it contains.
   * @param stream The output stream to display the information.
   */
  void const display(std::ostream &stream) {
    stream << "Group name: " << name << "; ";

    for (const auto &multimedia : *this) {
      multimedia->display(stream);
    }
  }
};

#endif // GROUP_H