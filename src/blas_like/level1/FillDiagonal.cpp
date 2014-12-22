/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#include "El.hpp"

namespace El {

template<typename T,typename S>
void FillDiagonal( Matrix<T>& A, S alpha, Int offset )
{
    DEBUG_ONLY(CallStackEntry cse("FillDiagonal"))
    const Int height = A.Height();
    const Int width = A.Width();
    for( Int j=0; j<width; ++j )
    {
        const Int i = j-offset;
        if( i >= 0 && i < height )
            A.Set(i,j,alpha);
    }
}

template<typename T,typename S>
void FillDiagonal( AbstractDistMatrix<T>& A, S alpha, Int offset )
{
    DEBUG_ONLY(CallStackEntry cse("FillDiagonal"))
    const Int height = A.Height();
    const Int localWidth = A.LocalWidth();
    for( Int jLoc=0; jLoc<localWidth; ++jLoc )
    {
        const Int j = A.GlobalCol(jLoc);
        const Int i = j-offset;
        if( i >= 0 && i < height && A.IsLocalRow(i) )
        {
            const Int iLoc = A.LocalRow(i);
            A.SetLocal( iLoc, jLoc, alpha );
        }
    }
}

template<typename T,typename S>
void FillDiagonal( AbstractBlockDistMatrix<T>& A, S alpha, Int offset )
{
    DEBUG_ONLY(CallStackEntry cse("FillDiagonal"))
    const Int height = A.Height();
    const Int localWidth = A.LocalWidth();
    for( Int jLoc=0; jLoc<localWidth; ++jLoc )
    {
        const Int j = A.GlobalCol(jLoc);
        const Int i = j-offset;
        if( i >= 0 && i < height && A.IsLocalRow(i) )
        {
            const Int iLoc = A.LocalRow(i);
            A.SetLocal( iLoc, jLoc, alpha );
        }
    }
}

#define PROTO_TYPES(T,S) \
  template void FillDiagonal( Matrix<T>& A, S alpha, Int offset ); \
  template void FillDiagonal \
  ( AbstractDistMatrix<T>& A, S alpha, Int offset ); \
  template void FillDiagonal \
  ( AbstractBlockDistMatrix<T>& A, S alpha, Int offset );

#define PROTO_SAME(T) PROTO_TYPES(T,T)

#define PROTO_INT(T) PROTO_SAME(T)

#define PROTO_REAL(T) \
  PROTO_TYPES(T,Int) \
  PROTO_SAME(T) 

#define PROTO_COMPLEX(T) \
  PROTO_TYPES(T,Int) \
  PROTO_TYPES(T,Base<T>) \
  PROTO_SAME(T)

#include "El/macros/Instantiate.h"

} // namespace El
