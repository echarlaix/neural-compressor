//  Copyright (c) 2021 Intel Corporation
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#ifndef ENGINE_EXECUTOR_INCLUDE_OPERATORS_LAYER_NORM_HPP_
#define ENGINE_EXECUTOR_INCLUDE_OPERATORS_LAYER_NORM_HPP_
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>

#include "../operator.hpp"
#include "oneapi/dnnl/dnnl.hpp"

namespace executor {
using dnnl::algorithm;
using dnnl::engine;
using dnnl::memory;
using dnnl::prop_kind;

/**
 * @brief A Layer Normalization operator.
 *
 */

class LayerNormOperator : public Operator {
 public:
  explicit LayerNormOperator(const OperatorConfig& conf);
  virtual ~LayerNormOperator() {}

  void Reshape(const vector<Tensor*>& input, const vector<Tensor*>& output) override;
  void Forward(const vector<Tensor*>& input, const vector<Tensor*>& output) override;

 private:
  bool weight_cached_;
  float epsilon_;
  dnnl::engine eng_ = engine(engine::kind::cpu, 0);
  dnnl::layer_normalization_forward lnorm_p_;
  memory src_m_;
  memory dst_m_;
  unordered_map<int, memory> memory_args_;
};
}  // namespace executor
#endif  // ENGINE_EXECUTOR_INCLUDE_OPERATORS_LAYER_NORM_HPP_
