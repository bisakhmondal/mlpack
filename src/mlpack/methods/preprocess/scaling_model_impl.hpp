/**
 * @file scaling_model_impl.hpp
 * @author Jeffin Sam
 *
 * A serializable scaling model, used by the main program.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */

#ifndef MLPACK_CORE_DATA_SCALING_MODEL_IMPL_HPP
#define MLPACK_CORE_DATA_SCALING_MODEL_IMPL_HPP

// In case it hasn't been included yet.
#include "scaling_model.hpp"

namespace mlpack {
namespace data {

ScalingModel::ScalingModel(const int minvalue, const int maxvalue,
    double epsilonvalue) :
    scalerType(0),
    minmaxscale(NULL),
    maxabsscale(NULL),
    meanscale(NULL),
    standardscale(NULL),
    pcascale(NULL),
    zcascale(NULL),
    minValue(minvalue),
    maxValue(maxvalue),
    epsilon(epsilonvalue)
{
  // Nothing to do.
}

//! Copy constructor.
ScalingModel::ScalingModel(const ScalingModel& other) :
    minValue(other.minValue),
    scalerType(other.scalerType),
    maxValue(other.maxValue),
    epsilon(other.epsilon),
    minmaxscale(other.minmaxscale == NULL ? NULL :
        new data::MinMaxScaler(*other.minmaxscale)),
    maxabsscale(other.maxabsscale == NULL ? NULL :
        new data::MaxAbsScaler(*other.maxabsscale)),
    pcascale(other.pcascale == NULL ? NULL :
        new data::PcaWhitening(*other.pcascale)),
    zcascale(other.zcascale == NULL ? NULL :
        new data::ZcaWhitening(*other.zcascale)),
    meanscale(other.meanscale == NULL ? NULL :
        new data::MeanNormalization(*other.meanscale)),
    standardscale(other.standardscale == NULL ? NULL :
        new data::StandardScaler(*other.standardscale))
{
  // Nothing to do.
}

//! Move constructor.
ScalingModel::ScalingModel(ScalingModel&& other) :
    scalerType(other.scalerType),
    minmaxscale(other.minmaxscale),
    maxabsscale(other.maxabsscale),
    pcascale(other.pcascale),
    zcascale(other.zcascale),
    meanscale(other.meanscale),
    standardscale(other.standardscale),
    epsilon(other.epsilon),
    minValue(other.minValue),
    maxValue(other.maxValue)
{
  other.scalerType = 0;
  other.minmaxscale = NULL;
  other.maxabsscale = NULL;
  other.meanscale = NULL;
  other.standardscale = NULL;
  other.pcascale = NULL;
  other.zcascale = NULL;
  other.minValue = 0;
  other.maxValue = 1;
  other.epsilon = 0.00005;
}

//! Copy assignment operator.
ScalingModel& ScalingModel::operator= (const ScalingModel& other)
{
  if (this == &other)
  {
    return *this;
  }
  scalerType = other.scalerType;

  delete minmaxscale;
  minmaxscale = (other.minmaxscale == NULL) ? NULL :
      new data::MinMaxScaler(*other.minmaxscale);

  delete maxabsscale;
  maxabsscale = (other.maxabsscale == NULL) ? NULL :
      new data::MaxAbsScaler(*other.maxabsscale);

  delete standardscale;
  standardscale = (other.standardscale == NULL) ? NULL :
      new data::StandardScaler(*other.standardscale);

  delete meanscale;
  meanscale = (other.meanscale == NULL) ? NULL :
      new data::MeanNormalization(*other.meanscale);

  delete pcascale;
  pcascale = (other.pcascale == NULL) ? NULL :
      new data::PcaWhitening(*other.pcascale);

  delete zcascale;
  zcascale = (other.zcascale == NULL) ? NULL :
      new data::ZcaWhitening(*other.zcascale);

  minValue = other.minValue;
  maxValue = other.maxValue;
  epsilon = other.epsilon;

  return *this;
}

ScalingModel::~ScalingModel()
{
  delete minmaxscale;
  delete maxabsscale;
  delete standardscale;
  delete meanscale;
  delete pcascale;
  delete zcascale;
}

template<typename MatType>
void ScalingModel::Fit(const MatType& input)
{
  if (scalerType == ScalerTypes::STANDARD_SCALER)
  {
    delete standardscale;
    standardscale = new data::StandardScaler();
    standardscale->Fit(input);
  }
  else if (scalerType == ScalerTypes::MIN_MAX_SCALER)
  {
    delete minmaxscale;
    minmaxscale = new data::MinMaxScaler(minValue, maxValue);
    minmaxscale->Fit(input);
  }
  else if (scalerType == ScalerTypes::MEAN_NORMALIZATION)
  {
    delete meanscale;
    meanscale = new data::MeanNormalization();
    meanscale->Fit(input);
  }
  else if (scalerType == ScalerTypes::MAX_ABS_SCALER)
  {
    delete maxabsscale;
    maxabsscale = new data::MaxAbsScaler();
    maxabsscale->Fit(input);
  }
  else if (scalerType == ScalerTypes::PCAWHITENING)
  {
    delete pcascale;
    pcascale = new data::PcaWhitening(epsilon);
    pcascale->Fit(input);
  }
  else if (scalerType == ScalerTypes::ZCAWHITENING)
  {
    delete zcascale;
    zcascale = new data::ZcaWhitening(epsilon);
    zcascale->Fit(input);
  }
}

template<typename MatType>
void ScalingModel::Transform(const MatType& input, MatType& output)
{
  if (scalerType == ScalerTypes::STANDARD_SCALER)
  {
    standardscale->Transform(input, output);
  }
  else if (scalerType == ScalerTypes::MIN_MAX_SCALER)
  {
    minmaxscale->Transform(input, output);
  }
  else if (scalerType == ScalerTypes::MEAN_NORMALIZATION)
  {
    meanscale->Transform(input, output);
  }
  else if (scalerType == ScalerTypes::MAX_ABS_SCALER)
  {
    maxabsscale->Transform(input, output);
  }
  else if (scalerType == ScalerTypes::PCAWHITENING)
  {
    pcascale->Transform(input, output);
  }
  else if (scalerType == ScalerTypes::ZCAWHITENING)
  {
    zcascale->Transform(input, output);
  }
}

template<typename MatType>
void ScalingModel::InverseTransform(const MatType& input, MatType& output)
{
  if (scalerType == ScalerTypes::STANDARD_SCALER)
  {
    standardscale->InverseTransform(input, output);
  }
  else if (scalerType == ScalerTypes::MIN_MAX_SCALER)
  {
    minmaxscale->InverseTransform(input, output);
  }
  else if (scalerType == ScalerTypes::MEAN_NORMALIZATION)
  {
    meanscale->InverseTransform(input, output);
  }
  else if (scalerType == ScalerTypes::MAX_ABS_SCALER)
  {
    maxabsscale->InverseTransform(input, output);
  }
  else if (scalerType == ScalerTypes::PCAWHITENING)
  {
    pcascale->InverseTransform(input, output);
  }
  else if (scalerType == ScalerTypes::ZCAWHITENING)
  {
    zcascale->InverseTransform(input, output);
  }
}

} // namespace data
} // namespace mlpack

#endif
