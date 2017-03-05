#ifndef MAP_HPP
#define MAP_HPP

#include "Entity.hpp"

void start();

class Map : public Entity {
public:
    Map();
    Map(const Map& orig);
    virtual ~Map();
private:

};

#endif /* MAP_HPP */

