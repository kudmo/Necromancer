#ifndef LAB3_DUNGEONEXCEPTIONS_H
#define LAB3_DUNGEONEXCEPTIONS_H

#include <exception>
#include <string>

namespace dungeon_errors {
    class dungeon_exception : public std::exception {
    private:
        std::string message;
    public:
        dungeon_exception(const std::string message): message(message) {}
        const char * what() const noexcept override {
                return message.c_str();
        }
    };

    class invalid_interaction_error : public dungeon_exception {
    public:
        invalid_interaction_error(const std::string message): dungeon_exception(message) {};
    };

    class invalid_position_error : public dungeon_exception {
    public:
        invalid_position_error(const std::string message): dungeon_exception(message) {};
    };
}

#endif //LAB3_DUNGEONEXCEPTIONS_H
