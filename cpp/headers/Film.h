#ifndef FILM_H
#define FILM_H

#include "Video.h"

/**
 * @class Film
 * @brief Represents a film, which is a type of video with chapters.
 * @details The `Film` class inherits from the `Video` class and adds the functionality to store and retrieve chapters.
 */
class Film : public Video {
private:
  int *chapters = nullptr; /**< Pointer to an array of chapter durations */
  int numberOfChapters{}; /**< Number of chapters in the film */

public:
  /**
   * @brief Constructs a `Film` object with the given name, path, and duration.
   * @param name The name of the film.
   * @param path The path of the film.
   * @param duration The duration of the film in seconds.
   */
  Film(std::string name, std::string path, int duration)
      : Video(name, path, duration){};

  /**
   * @brief Copy constructor for the `Film` class.
   * @param film The `Film` object to be copied.
   */
  Film(const Film &film) : Video(film) {
    setChapters(film.chapters, film.numberOfChapters);
  }

  /**
   * @brief Gets a copy of the chapters array.
   * @return A pointer to a new array containing the chapter durations.
   */
  int *getChapters() const {
    int *chaptersCopy = new int[numberOfChapters];
    for (int i = 0; i < numberOfChapters; i++) {
      chaptersCopy[i] = chapters[i];
    }

    return chaptersCopy;
  }

  /**
   * @brief Sets the chapters array and the number of chapters.
   * @param chapters Pointer to an array of chapter durations.
   * @param numberOfChapters The number of chapters in the film.
   */
  void setChapters(int *chapters, int numberOfChapters) {
    this->numberOfChapters = numberOfChapters;

    delete[] this->chapters;
    this->chapters = new int[numberOfChapters];

    for (int i = 0; i < numberOfChapters; i++) {
      this->chapters[i] = chapters[i];
    }
  }

  /**
   * @brief Gets the number of chapters in the film.
   * @return The number of chapters.
   */
  int getNumberOfChapters() const { return numberOfChapters; };

  /**
   * @brief Displays the film information to the given output stream.
   * @param stream The output stream to display the information to.
   */
  virtual void display(std::ostream &stream) const override {
    Video::display(stream);

    int *chapters = getChapters();

    stream << "Chapters durations: ";
    for (int i = 0; i < getNumberOfChapters(); i++) {
      stream << chapters[i];
      if (i != getNumberOfChapters() - 1)
        stream << ", ";
    }
    stream << "; ";

    delete[] chapters;
  };

  /**
   * @brief Destructor for the `Film` class.
   * @details Frees the memory allocated for the chapters array.
   */
  ~Film() { delete[] chapters; };
};

#endif // FILM_H