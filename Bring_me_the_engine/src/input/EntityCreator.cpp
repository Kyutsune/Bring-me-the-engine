#include "input/EntityCreator.h"

namespace EntityCreator {
    void createEntity(TypeEntityCreated type, const double & x, const double & y){
        if(type == TypeEntityCreated::None) {
            return; 
        }
        if(type == TypeEntityCreated::Cube){
            createCube(x, y);
        }
    }


}