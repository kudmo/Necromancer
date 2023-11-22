#ifndef LAB3_ENEMYEXCEPTIONS_H
#define LAB3_ENEMYEXCEPTIONS_H

#include <exception>
#include <string>
#include "../../../Entity/include/Exceptions/EntityExceptions.h"

namespace enemy_errors {
    class enemy_exception : public entity_errors::entity_exception {
    private:
        std::string message;
    public:
        enemy_exception(const std::string message): entity_errors::entity_exception(message) {}
    };

    class invalid_type_error : public enemy_exception {
    public:
        invalid_type_error(const std::string message): enemy_exception(message) {}
    };
}


#endif //LAB3_ENEMYEXCEPTIONS_H
