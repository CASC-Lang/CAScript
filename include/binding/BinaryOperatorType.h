//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BINARYOPERATORTYPE_H
#define COLLAGE_CPP_BINARYOPERATORTYPE_H

namespace collage::binding {
    enum class BinaryOperatorType {
        Addition,
        Minus,
        Multiplication,
        Division,
        Modulus,
        Equal,
        NotEqual,
        LeftShift,
        RightShift,
        BitwiseAnd,
        BitwiseExclusiveOr,
        BitwiseInclusiveOr,
        LogicalAnd,
        LogicalOr,
        Greater,
        GreaterEqual,
        Less,
        LessEqual,
    };
}

#endif //COLLAGE_CPP_BINARYOPERATORTYPE_H
