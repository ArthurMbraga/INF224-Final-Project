#ifndef PHOTO_H
#define PHOTO_H

#include <memory>

#include "Factory.h"
#include "Multimedia.h"

/**
 * @class Photo
 * @brief Represents a photo object derived from the Multimedia base class.
 * 
 * The Photo class stores information about a photo, including its name, path, latitude, and longitude.
 * It provides methods to get and set the latitude and longitude, as well as display the photo's information
 * and play the photo using the "imagej" command.
 */
class Photo : public Multimedia {

private:
  friend class Factory;

  double latitude{};
  double longitude{};

protected:
  Photo(){};
  Photo(std::string name, std::string path, double latitude, double longitude)
      : Multimedia(name, path), latitude(latitude), longitude(longitude) {}

public:
  /**
   * @brief Get the latitude of the photo.
   * @return The latitude value.
   */
  double getLatitude() const { return latitude; };

  /**
   * @brief Set the latitude of the photo.
   * @param latitude The latitude value to set.
   */
  void setLatitude(double latitude) { this->latitude = latitude; };

  /**
   * @brief Get the longitude of the photo.
   * @return The longitude value.
   */
  double getLongitude() const { return longitude; };

  /**
   * @brief Set the longitude of the photo.
   * @param longitude The longitude value to set.
   */
  void setLongitude(double longitude) { this->longitude = longitude; };

  /**
   * @brief Display the photo's information.
   * @param stream The output stream to display the information to.
   */
  virtual void display(std::ostream &stream) const override {
    Multimedia::display(stream);
    stream << "Latitude: " << latitude << "; ";
    stream << "Longitude: " << longitude << "; ";
  };

  /**
   * @brief Play the photo using the "imagej" command.
   */
  virtual void play() const override {
    std::string command = "imagej " + getPath() + " &";
    system(command.c_str());
  };
};

#endif // PHOTO_H
