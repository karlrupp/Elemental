/*
   Copyright (c) 2009-2010, Jack Poulson
   All rights reserved.

   This file is part of Elemental.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

    - Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    - Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    - Neither the name of the owner nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef ELEMENTAL_TYPES_HPP
#define ELEMENTAL_TYPES_HPP 1

#ifndef WITHOUT_COMPLEX
#include <complex>
#endif
#include <limits>
#include <string>

namespace elemental {

#ifndef WITHOUT_COMPLEX
typedef std::complex<float>  scomplex; 
typedef std::complex<double> dcomplex;
#endif

enum Diagonal
{
    NonUnit,
    Unit
};

inline char DiagonalToChar( Diagonal diagonal )
{
    char diagonalChar;
    switch( diagonal )
    {
        case NonUnit: diagonalChar = 'N'; break;
        default:      diagonalChar = 'U'; break;
    }
    return diagonalChar;
}

inline Diagonal CharToDiagonal( char c )
{
    Diagonal diagonal;
    switch( c )
    {
        case 'N': diagonal = NonUnit; break;
        case 'U': diagonal = Unit;    break;
        default:
            throw std::logic_error( "CharToDiagonal expects char in {N,U}." );
    }
    return diagonal;
}

enum Distribution
{
    MC,  // Col of a matrix distribution
    MD,  // Diagonal of a matrix distribution
    MR,  // Row of a matrix distribution
    VC,  // Col-major vector distribution
    VR,  // Row-major vector distribution
    Star // Do not distribute
};

inline std::string DistToString( Distribution distribution )
{
    std::string distString;
    switch( distribution )
    {
        case MC: distString = "MC"; break;
        case MD: distString = "MD"; break;
        case MR: distString = "MR"; break;
        case VC: distString = "VC"; break;
        case VR: distString = "VR"; break;
        default: distString = "* "; break;
    }
    return distString;
}

inline Distribution StringToDist( std::string s )
{
    Distribution distribution;
    if( s == "MC" )
        distribution = MC;
    else if( s == "MD" )
        distribution = MD;
    else if( s == "MR" )
        distribution = MR;
    else if( s == "VC" )
        distribution = VC;
    else if( s == "VR" )
        distribution = VR;
    else if( s == "* " || s == " *" || s == "*" )
        distribution = Star;
    else
    {
        throw std::logic_error( "StringToDist expects string in "
              "{\"MC\",\"MD\",\"MR\",\"VC\",\"VR\",\"* \",\" *\",\"*\"}." );
    }
    return distribution;
}

enum Orientation
{
    Normal,
    Transpose,
    ConjugateTranspose
};

inline char OrientationToChar( Orientation orientation )
{
    char orientationChar;
    switch( orientation )
    {
        case Normal:             orientationChar = 'N'; break;
        case Transpose:          orientationChar = 'T'; break;
        default:                 orientationChar = 'C'; break;
    }
    return orientationChar;
}

inline Orientation CharToOrientation( char c )
{
    Orientation orientation;
    switch( c )
    {
        case 'N': orientation = Normal;             break;
        case 'T': orientation = Transpose;          break;
        case 'C': orientation = ConjugateTranspose; break;
        default:
            throw std::logic_error
            ( "CharToOrientation expects char in {N,T,C}." );
    }
    return orientation;
}

enum Shape
{
    Lower,
    Upper
};

inline char ShapeToChar( Shape shape )
{
    char shapeChar;
    switch( shape )
    {
        case Lower: shapeChar = 'L'; break;
        default:    shapeChar = 'U'; break;
    }
    return shapeChar;
}

inline Shape CharToShape( char c )
{
    Shape shape;
    switch( c )
    {
        case 'L': shape = Lower; break;
        case 'U': shape = Upper; break;
        default:
            throw std::logic_error( "CharToShape expects char in {L,U}." );
    }
    return shape;
}

enum Side
{
    Left,
    Right
};

inline char SideToChar( Side side )
{
    char sideChar;
    switch( side )
    {
        case Left:  sideChar = 'L'; break;
        default:    sideChar = 'R'; break;
    }
    return sideChar;
}
    
inline Side CharToSide( char c )
{
    Side side;
    switch( c )
    {
        case 'L': side = Left;  break;
        case 'R': side = Right; break;
        default:
            throw std::logic_error( "CharToSide expects char in {L,R}." );
    }
    return side;
}

} // elemental

#endif /* ELEMENTAL_TYPES_HPP */

