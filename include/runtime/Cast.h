//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_CAST_H
#define COLLAGE_CPP_CAST_H

#include <any>
#include "binding/Type.h"

template <collage::binding::Type T, class To> static To cast(std::any value);

template <> bool cast<collage::binding::Type::Bool>(std::any value) {
    return std::any_cast<bool>(value);
}

#endif //COLLAGE_CPP_CAST_H
