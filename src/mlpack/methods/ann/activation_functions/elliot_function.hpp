/**
 * @file elliot_function.hpp
 * @author Bisakh Mondal
 *
 * Definition and implementation of the Elliot Activation function as described 
 * by D.L. Elliott
 *
 * For more information, see the following paper.
 *
 * @code
 * @techreport{elliott1993better,
 *   title={A better activation function for artificial neural networks},
 *   author={Elliott, David L},
 *   year={1993}
 * }
 * @endcode
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_METHODS_ANN_ACTIVATION_FUNCTIONS_ELLIOT_FUNCTION_HPP
#define MLPACK_METHODS_ANN_ACTIVATION_FUNCTIONS_ELLIOT_FUNCTION_HPP

#include <mlpack/prereqs.hpp>

namespace mlpack {
namespace ann /** Artificial Neural Network. */ {

/**
 * The Elliot function, defined by
 *
 * @f{eqnarray*}{
 *  f(x) &=& \frac{x}{1 + |x|} \\
 *  f'(x) &=& \frac{1}{(1 + |x|)^2}
 * @f}
 */

class ElliotFunction
{
 public:
  /**
   * Computes the Elliot function.
   *
   * @param x Input data.
   * @return f(x).
   */
  static double Fn(const double x)
  {
    return x / (1.0 + std::abs(x));
  }

  /**
   * Computes the Elliot function.
   *
   * @param x Input data.
   * @param y The resulting output activation.
   */
  template <typename InputVecType, typename OutputVecType>
  static void Fn(const InputVecType &x, OutputVecType &y)
  {
      y = x * (1.0 + arma::abs(x));
  }

  /**
   * Computes the first derivative of the Elliot function.
   *
   * @param y Input data.
   * @return f'(x)
   */
  static double Deriv(const double y)
  {
    return 1.0 / std::pow(1.0 + std::abs(y), 2);
  }

  /**
   * Computes the first derivatives of the Elliot function.
   * 
   * @param y Input activations.
   * @param x The resulting derivatives.
   */
  template <typename InputVecType, typename OutputVecType>
  static void Deriv(const InputVecType &y, OutputVecType &x)
  {
    x = 1.0 / arma::pow(1.0 + arma::abs(y), 2);
  }
}; // class ElliotFunction

} // namespace ann
} // namespace mlpack


#endif