#ifndef LAB3_SKILLEXCEPTION_H
#define LAB3_SKILLEXCEPTION_H

#include <exception>
#include <string>

namespace skill_errors {
    class skill_exception : public std::exception {
    private:
        std::string message;
    public:
        skill_exception(const std::string message) : message(message) {}

        const char *what() const

        noexcept override{
                return message.c_str();
        }
    };

    class invalid_skill_level : public skill_exception {
    public:
        invalid_skill_level(const std::string message) : skill_exception(message) {};
    };

    class invalid_skill_user : public skill_exception {
    public:
        invalid_skill_user(const std::string message) : skill_exception(message) {};
    };

    class invalid_skill_target : public skill_exception {
    public:
        invalid_skill_target(const std::string message) : skill_exception(message) {};
    };

    class invalid_subskill_error : public skill_exception {
    public:
        invalid_subskill_error(const std::string message) : skill_exception(message) {};
    };

    class invalid_subskill_type_error : public skill_exception {
    public:
        invalid_subskill_type_error(const std::string message) : skill_exception(message) {};
    };




    class skill_table_exception : public std::exception {
    private:
        std::string message;
    public:
        skill_table_exception(const std::string message) : message(message) {}

        const char *what() const

        noexcept override{
                return message.c_str();
        }
    };

    class skill_table_no_skill_error : public skill_table_exception {
    public:
        skill_table_no_skill_error(const std::string message) : skill_table_exception(message) {};
    };
}
#endif //LAB3_SKILLEXCEPTION_H
