#ifndef LAB3_EXCEPTIONS_H
#define LAB3_EXCEPTIONS_H

#include <exception>
#include <string>
#include "../../BaseInterfaces/Entity/include/Exceptions/EntityExceptions.h"

namespace player_errors {
    class player_exception : public entity_errors::entity_exception {
    public:
        player_exception(const std::string message): entity_errors::entity_exception(message) {}
    };

    class invalid_upgrade_error : public player_exception {
    public:
        invalid_upgrade_error(const std::string message): player_exception(message) {}
    };

}

#endif //LAB3_EXCEPTIONS_H
