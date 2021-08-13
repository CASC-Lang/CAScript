//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_TYPE_H
#define COLLAGE_CPP_TYPE_H

#include <any>

namespace collage::binding {
    enum class Type {
        Unidentified,
        Number,
        Bool
    };

    /**
     * @param left should be constant type
     * @param right should be dynamic type
     * @return if constant type is not specified, return true, else compare and return result.
     */
    static bool is_or_unspecified(const collage::binding::Type &left, const collage::binding::Type &right) {
        if (left == collage::binding::Type::Unidentified) return true;
        else if (left == right) return true;
        else return false;
    }

    template<Type, typename R>
    static R cast(std::any value);

    template<>
    bool cast<Type::Bool>(std::any value) {
        return std::any_cast<bool>(value);
    }

    template<>
    double cast<Type::Number>(std::any value) {
        return std::any_cast<double>(value);
    }
}

#endif //COLLAGE_CPP_TYPE_H
