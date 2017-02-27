/*
 */

/* 
 * File:   Entity.hpp
 * Author: cedric
 *
 * Created on February 27, 2017, 3:38 PM
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity {
public:
    virtual ~Entity(); //Destructeur virtuel 
    virtual void OverrideMe() = 0; //
    
private:

};

#endif /* ENTITY_HPP */

