#ifndef VIDEO_H
#define VIDEO_H

#include "Factory.h"
#include "Multimedia.h"

/**
 * @class Video
 * @brief Represents a video file.
 * 
 * The Video class is a derived class of the Multimedia class and represents a video file.
 * It provides methods to get and set the duration of the video, display information about the video,
 * and play the video using the mpv player.
 */
class Video : public Multimedia {
private:
  friend class Factory;
  int duration{};

protected:
  Video(){};
  Video(std::string name, std::string path, int duration)
      : Multimedia(name, path), duration(duration) {}

public:
  /**
   * @brief Get the duration of the video.
   * @return The duration of the video in seconds.
   */
  int getDuration() const { return duration; };

  /**
   * @brief Set the duration of the video.
   * @param duration The duration of the video in seconds.
   */
  void setDuration(int duration) { this->duration = duration; };

  /**
   * @brief Display information about the video.
   * @param stream The output stream to display the information.
   */
  virtual void display(std::ostream &stream) const override {
    Multimedia::display(stream);
    stream << "Duration: " << duration << "; ";
  };

  /**
   * @brief Play the video using the mpv player.
   */
  virtual void play() const override {
    std::string command = "mpv " + getPath() + " &";
    system(command.c_str());
  };
};

#endif // VIDEO_H
