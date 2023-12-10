#ifndef LAB3_ENTITYEXCEPTIONS_H
#define LAB3_ENTITYEXCEPTIONS_H

#include <exception>
#include <string>

namespace entity_errors {
    class entity_exception : public std::exception {
    private:
        std::string message;
    public:
        entity_exception(const std::string message) : message(message) {}

        const char *what() const noexcept override {
            return message.c_str();
        }
    };

    class already_dead_exception : public entity_exception{
    private:
        std::string message;
    public:
        already_dead_exception(const std::string message) : entity_exception(message) {}

        const char *what() const noexcept override {
            return message.c_str();
        }
    };
}
#endif //LAB3_ENTITYEXCEPTIONS_H
