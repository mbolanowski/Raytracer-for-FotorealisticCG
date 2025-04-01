//
// Created by cheily on 31.03.2025.
//

#include "Camera.h"

Camera::Camera()
    : position(0, 0, 0),
      forward(0, 0, 1),
      up(0, 1, 0) {

}

Camera::Camera(Vector position, Vector target)
    : position(position),
      forward(target),
      up(0, 1, 0){

}

