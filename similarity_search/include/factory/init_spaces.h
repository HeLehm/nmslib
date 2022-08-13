/**
 * Non-metric Space Library
 *
 * Main developers: Bilegsaikhan Naidan, Leonid Boytsov, Yury Malkov, Ben Frederickson, David Novak
 *
 * For the complete list of contributors and further details see:
 * https://github.com/nmslib/nmslib
 *
 * Copyright (c) 2013-2018
 *
 * This code is released under the
 * Apache License Version 2.0 http://www.apache.org/licenses/.
 *
 */
#ifndef INIT_SPACES_H
#define INIT_SPACES_H

#include "spacefactory.h"

#include "factory/space/space_edist.h"
#include "factory/space/space_bit_hamming.h"
#include "factory/space/space_bit_and.h"
#include "factory/space/space_bit_jaccard.h"
#include "factory/space/space_test_encode_float.h"
#include "factory/space/space_test_encode_uint.h"
#include "factory/space/space_mylingua.h"
#include "factory/space/space_bit_and_norm_lft_cos_varvec_varweigh.h"
#include "factory/space/space_bit_and_norm_lft_cos_varvec.h"
#include "factory/space/space_bit_and_norm_lft_cos.h"
#include "factory/space/space_bit_and_norm_lft.h"
#include "factory/space/space_bit_and_norm_rgt.h"
#include "factory/space/space_bregman.h"
#include "factory/space/space_dummy.h"
#include "factory/space/space_js.h"
#include "factory/space/space_lp.h"
#include "factory/space/space_scalar.h"
#include "factory/space/space_sparse_lp.h"
#include "factory/space/space_sparse_scalar.h"
#include "factory/space/space_word_embed.h"
#include "factory/space/space_ab_diverg.h"
#include "factory/space/space_renyi_diverg.h"
#include "factory/space/space_sparse_jaccard.h"
#include "factory/space/space_sparse_dense_fusion.h"
#if defined(WITH_EXTRAS)
#include "factory/space/space_sqfd.h"
#endif

namespace similarity {

inline void initSpaces() {
  // Registering a dummy space
  REGISTER_SPACE_CREATOR(int,    SPACE_DUMMY,  CreateDummy)
  REGISTER_SPACE_CREATOR(float,  SPACE_DUMMY,  CreateDummy)

  // Registering binary/bit Hamming/Jaccard/And/AndNorm2x
  SpaceFactoryRegistry<int>::CreateFuncPtr bit_hamming_func_ptr = CreateBitHamming<int,uint32_t>;
  REGISTER_SPACE_CREATOR(int, SPACE_BIT_HAMMING, bit_hamming_func_ptr )

  SpaceFactoryRegistry<float>::CreateFuncPtr bit_jaccard_func_ptr = CreateBitJaccard<float,uint32_t>;
  REGISTER_SPACE_CREATOR(float, SPACE_BIT_JACCARD,  bit_jaccard_func_ptr )

  // Mylingua test encoding methods 
  SpaceFactoryRegistry<int>::CreateFuncPtr test_uint_func_ptr = CreateTestEncodeUint<int,uint32_t>;
  REGISTER_SPACE_CREATOR(int, SPACE_TEST_ENCODE_UINT, test_uint_func_ptr )

  SpaceFactoryRegistry<float>::CreateFuncPtr test_float_func_ptr = CreateTestEncodeFloat<float,uint32_t>;
  REGISTER_SPACE_CREATOR(float, SPACE_TEST_ENCODE_FLOAT,  test_float_func_ptr )


  // My custom methods (mylingua)
  SpaceFactoryRegistry<float>::CreateFuncPtr mylingua_func_ptr = CreateMyLingua<float,uint32_t>;
  REGISTER_SPACE_CREATOR(float, SPACE_MYLINGUA,  mylingua_func_ptr )

  SpaceFactoryRegistry<float>::CreateFuncPtr bit_and_norm_lft_cos_varvec_varweigh_func_ptr = CreateBitAndNormLftCosVarvecVarweigh<float,uint32_t>;
  REGISTER_SPACE_CREATOR(float, SPACE_BIT_AND_NORM_LFT_COS_VARVEC_VARWEIGH,  bit_and_norm_lft_cos_varvec_varweigh_func_ptr )

  SpaceFactoryRegistry<float>::CreateFuncPtr bit_and_norm_lft_cos_varvec_func_ptr = CreateBitAndNormLftCosVarvec<float,uint32_t>;
  REGISTER_SPACE_CREATOR(float, SPACE_BIT_AND_NORM_LFT_COS_VARVEC,  bit_and_norm_lft_cos_varvec_func_ptr )

  SpaceFactoryRegistry<float>::CreateFuncPtr bit_and_norm_lft_cos_func_ptr = CreateBitAndNormLftCos<float,uint32_t>;
  REGISTER_SPACE_CREATOR(float, SPACE_BIT_AND_NORM_LFT_COS,  bit_and_norm_lft_cos_func_ptr )
  
  SpaceFactoryRegistry<float>::CreateFuncPtr bit_and_norm_lft_func_ptr = CreateBitAndNormLft<float,uint32_t>;
  REGISTER_SPACE_CREATOR(float, SPACE_BIT_AND_NORM_LFT,  bit_and_norm_lft_func_ptr )
  SpaceFactoryRegistry<float>::CreateFuncPtr bit_and_norm_rgt_func_ptr = CreateBitAndNormRgt<float,uint32_t>;
  REGISTER_SPACE_CREATOR(float, SPACE_BIT_AND_NORM_RGT,  bit_and_norm_rgt_func_ptr )
  
  SpaceFactoryRegistry<int>::CreateFuncPtr bit_and_func_ptr = CreateBitAnd<int,uint32_t>;
  REGISTER_SPACE_CREATOR(int,    SPACE_BIT_AND, bit_and_func_ptr )

  // Registering the Levensthein-distance: regular and normalized
  REGISTER_SPACE_CREATOR(int,   SPACE_LEVENSHTEIN,  CreateLevenshtein)
  REGISTER_SPACE_CREATOR(float, SPACE_LEVENSHTEIN_NORM,  CreateLevenshteinNormalized)

  // Registering Bregman divergences
  REGISTER_SPACE_CREATOR(float,  SPACE_KLDIV_FAST, CreateKLDivFast)
  REGISTER_SPACE_CREATOR(float,  SPACE_KLDIV_FAST_RIGHT_QUERY, CreateKLDivFastRightQuery)
  REGISTER_SPACE_CREATOR(float,  SPACE_KLDIVGEN_FAST, CreateKLDivGenFast)
  REGISTER_SPACE_CREATOR(float,  SPACE_KLDIVGEN_SLOW, CreateKLDivGenSlow)
  REGISTER_SPACE_CREATOR(float,  SPACE_KLDIVGEN_FAST_RIGHT_QUERY, CreateKLDivGenFastRightQuery)
  REGISTER_SPACE_CREATOR(float,  SPACE_ITAKURASAITO_FAST, CreateItakuraSaitoFast)

  // Jensen-Shannon functions and their derivatives
  REGISTER_SPACE_CREATOR(float,  SPACE_JS_DIV_SLOW, CreateJSDivSlow)
  REGISTER_SPACE_CREATOR(float,  SPACE_JS_DIV_FAST, CreateJSDivFastPrecomp)
  REGISTER_SPACE_CREATOR(float,  SPACE_JS_DIV_FAST_APPROX, CreateJSDivFastPrecompApprox)

  REGISTER_SPACE_CREATOR(float,  SPACE_JS_METR_SLOW, CreateJSMetricSlow)
  REGISTER_SPACE_CREATOR(float,  SPACE_JS_METR_FAST, CreateJSMetricFastPrecomp)
  REGISTER_SPACE_CREATOR(float,  SPACE_JS_METR_FAST_APPROX, CreateJSMetricFastPrecompApprox)

  // Word embeddings
  REGISTER_SPACE_CREATOR(float,  SPACE_WORD_EMBED,  CreateWordEmbed)

  // LP spaces
  REGISTER_SPACE_CREATOR(float,  SPACE_L,  CreateL)
  REGISTER_SPACE_CREATOR(float,  SPACE_LINF, CreateLINF)
  REGISTER_SPACE_CREATOR(float,  SPACE_L1, CreateL1)
  REGISTER_SPACE_CREATOR(float,  SPACE_L2, CreateL2)

  // Scalar product and related distances
  // Dense
  REGISTER_SPACE_CREATOR(float,  SPACE_COSINE_SIMILARITY, CreateCosineSimilarity)
  REGISTER_SPACE_CREATOR(float,  SPACE_ANGULAR_DISTANCE, CreateAngularDistance)
  REGISTER_SPACE_CREATOR(float,  SPACE_NEGATIVE_SCALAR, CreateNegativeScalarProduct)

  // Sparse
  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_L, CreateSparseL)
  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_LINF, CreateSparseLINF)
  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_L1, CreateSparseL1)
  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_L2, CreateSparseL2)

  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_COSINE_SIMILARITY, CreateSparseCosineSimilarity)
  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_ANGULAR_DISTANCE, CreateSparseAngularDistance)
  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_NEGATIVE_SCALAR, CreateSparseNegativeScalarProduct)

  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_COSINE_SIMILARITY_FAST, CreateSparseCosineSimilarityFast)
  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_COSINE_SIMILARITY_BIN_FAST, CreateSparseCosineSimilarityBinFast)
  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_ANGULAR_DISTANCE_FAST, CreateSparseAngularDistanceFast)
  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_NEGATIVE_SCALAR_FAST, CreateSparseNegativeScalarProductFast)
  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_NEGATIVE_SCALAR_PROD_BIN_FAST, CreateSparseNegativeScalarProductBinFast)
  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_QUERY_NORM_NEGATIVE_SCALAR_FAST, CreateSparseQueryNormNegativeScalarProductFast)

  REGISTER_SPACE_CREATOR(float,  SPACE_SPARSE_JACCARD,  CreateSpaceSparseJaccard)

#if defined(WITH_EXTRAS)
  // Signature Quadratic Form Distance
  REGISTER_SPACE_CREATOR(float,  SPACE_SQFD_HEURISTIC_FUNC, CreateSqfdHeuristicFunc)
  REGISTER_SPACE_CREATOR(float,  SPACE_SQFD_MINUS_FUNC, CreateSqfdMinusFunc)
  REGISTER_SPACE_CREATOR(float,  SPACE_SQFD_GAUSSIAN_FUNC, CreateSqfdGaussianFunc)
#endif

  REGISTER_SPACE_CREATOR(float,  SPACE_AB_DIVERG_SLOW,  CreateAlphaBetaDivergSlow)
  REGISTER_SPACE_CREATOR(float,  SPACE_AB_DIVERG_FAST,  CreateAlphaBetaDivergFast)

  REGISTER_SPACE_CREATOR(float,  SPACE_RENYI_DIVERG_SLOW,  CreateRenyiDivergSlow)
  REGISTER_SPACE_CREATOR(float,  SPACE_RENYI_DIVERG_FAST,  CreateRenyiDivergFast)

  REGISTER_SPACE_CREATOR(int,    SPACE_L2SQR_SIFT,  CreateL2SqrSIFT)
  REGISTER_SPACE_CREATOR(float, SPACE_SPARSE_DENSE_FUSION, createSparseDenseFusion)
}

}

#endif
