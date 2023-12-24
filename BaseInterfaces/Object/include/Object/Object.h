#ifndef LAB3_OBJECT_H
#define LAB3_OBJECT_H

#include <utility>

#include "../../../Interfaces/IPosisionable.h"

#include <Floor/Floor.h>
#include <Field/Field.h>

class Floor;
class Field;
/*!
 * @brief Base class for all objects
 */
class Object : public IPositionable {
private:
    Floor *floor;
    std::pair<size_t,size_t> coord;
public:
    Object(Floor& f, std::pair<size_t,size_t> coord): floor(&f), coord(coord) {}

    /*!
     * @return The name of this object
     */
    virtual const std::string getNaming() const = 0;
    /*!
     * @brief Getting brief information about the object
     * @return string in JSON-format
     */
    virtual const std::string getInfo() const = 0;
    /*!
     * @brief Getting all the information about the object
     * @return String in JSON-format
     */
    virtual const std::string getFullInfo() const = 0;
    /*!
     * @return The floor at which the object is located
     */
    Floor & getFloor() override;
    /*!
     * @return The floor at which the object is located
     */
    const Floor & getFloor() const override;
    /*!
     * @brief Sets the floor at which the object is located
     * @param floor new floor
     */
    void setFloor(Floor& floor) override;
    /*!
     * @return The field where the object is located
     */
    Field & getPosition() override;
    /*!
     * @return The field where the object is located
     */
    const Field& getPosition() const override;

    /*!
     * @return Coordinates of the object
     */
    std::pair<size_t, size_t> getCoordinates() const override;
    /*!
     * @brief Moves the object along the specified coordinates
     * @param coordinates Specified coordinates
     */
    void setCoordinates(std::pair<size_t, size_t> coordinates) override;

    virtual ~Object() = default;
};

#endif //LAB3_OBJECT_H