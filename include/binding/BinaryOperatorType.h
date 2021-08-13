//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BINARYOPERATORTYPE_H
#define COLLAGE_CPP_BINARYOPERATORTYPE_H

namespace cascript::binding {
    enum class BinaryOperatorType {
        Addition,
        Minus,
        Multiplication,
        Exponent,
        Division,
        FloorDivision,
        Modulus,
        Equal,
        NotEqual,
        LeftShift,
        UnsignedRightShift,
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
        ThreeWayComparison,
    };
}

#endif //COLLAGE_CPP_BINARYOPERATORTYPE_H
