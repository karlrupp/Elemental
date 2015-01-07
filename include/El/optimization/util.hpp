/*
   Copyright (c) 2009-2015, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#ifndef EL_OPTIMIZATION_UTIL_HPP
#define EL_OPTIMIZATION_UTIL_HPP

namespace El {

// Utilities
// =========

// Covariance
// ----------
template<typename F>
void Covariance( const Matrix<F>& D, Matrix<F>& S );
template<typename F>
void Covariance( const AbstractDistMatrix<F>& D, AbstractDistMatrix<F>& S );

// Log barrier
// -----------
template<typename F>
Base<F> LogBarrier( UpperOrLower uplo, const Matrix<F>& A );
template<typename F>
Base<F> LogBarrier( UpperOrLower uplo, const AbstractDistMatrix<F>& A );

template<typename F>
Base<F> LogBarrier
( UpperOrLower uplo, Matrix<F>& A, bool canOverwrite=false );
template<typename F>
Base<F> LogBarrier
( UpperOrLower uplo, AbstractDistMatrix<F>& A, bool canOverwrite=false );

// Log-det divergence
// ------------------
template<typename F>
Base<F> LogDetDiv
( UpperOrLower uplo, const Matrix<F>& A, const Matrix<F>& B );
template<typename F>
Base<F> LogDetDiv
( UpperOrLower uplo, 
  const AbstractDistMatrix<F>& A, const AbstractDistMatrix<F>& B );

// Maximum step within the positive cone
// -------------------------------------
template<typename Real>
Real MaxStepInPositiveCone
( const Matrix<Real>& s, 
  const Matrix<Real>& ds, Real upperBound );
template<typename Real>
Real MaxStepInPositiveCone
( const AbstractDistMatrix<Real>& s, 
  const AbstractDistMatrix<Real>& ds, Real upperBound );
template<typename Real>
Real MaxStepInPositiveCone
( const DistMultiVec<Real>& s, 
  const DistMultiVec<Real>& ds, Real upperBound );

// Number of non-positive entries
// ------------------------------
template<typename Real>
Int NumNonPositive( const Matrix<Real>& A );
template<typename Real>
Int NumNonPositive( const SparseMatrix<Real>& A );
template<typename Real>
Int NumNonPositive( const AbstractDistMatrix<Real>& A );
template<typename Real>
Int NumNonPositive( const DistSparseMatrix<Real>& A );
template<typename Real>
Int NumNonPositive( const DistMultiVec<Real>& A );

// Number of non-SOC members
// -------------------------
template<typename Real>
Int NumNonSecondOrder
( const Matrix<Real>& x, 
  const Matrix<Int>& orders, 
  const Matrix<Int>& firstInds );
template<typename Real>
Int NumNonSecondOrder
( const AbstractDistMatrix<Real>& x, 
  const AbstractDistMatrix<Int>& orders, 
  const AbstractDistMatrix<Int>& firstInds, Int cutoff=1000 );
template<typename Real>
Int NumNonSecondOrder
( const DistMultiVec<Real>& x, 
  const DistMultiVec<Int>& orders, 
  const DistMultiVec<Int>& firstInds, Int cutoff=1000 );

// Regularized LDL
// ---------------
// NOTE: If the pivot candidate is not at least as large as the pivot tolerance
//       and with the implied sign, then it is increased by the specified value.
template<typename F>
void RegularizedLDL
( Matrix<F>& A, Base<F> pivTol,
  const Matrix<Base<F>>& regCand, 
        Matrix<Base<F>>& reg );
template<typename F>
void RegularizedLDL
( AbstractDistMatrix<F>& A, Base<F> pivTol,
  const AbstractDistMatrix<Base<F>>& regCand, 
        AbstractDistMatrix<Base<F>>& reg );

template<typename F>
void RegularizedLDL
( DistSymmInfo& info, DistSymmFrontTree<F>& L,
  Base<F> pivTol,
  const DistNodalMultiVec<Base<F>>& regCand, 
        DistNodalMultiVec<Base<F>>& reg,
  SymmFrontType newFrontType=LDL_1D );

namespace reg_ldl {

template<typename F>
Int SolveAfter
( const DistSparseMatrix<F>& A,      const DistMultiVec<Base<F>>& reg,
  const DistMap& invMap,             const DistSymmInfo& info,
  const DistSymmFrontTree<F>& AFact,       DistMultiVec<F>& y,
  Base<F> minReductionFactor,              Int maxRefineIts,
  bool progress );

} // namespace reg_ldl

} // namespace El

#endif // ifndef EL_OPTIMIZATION_UTIL_HPP
