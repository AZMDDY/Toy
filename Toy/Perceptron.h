// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 感知器

#ifndef TOY_PERCEPTRON_H
#define TOY_PERCEPTRON_H
#include <cstdint>
#include <array>
#include <vector>
#include <numeric>
template<uint32_t Num>
class Perceptron {
public:
    explicit Perceptron(const std::array<int32_t, Num>& initWeights) : weights(initWeights) {}

    // 根据当前权重，计算出预测值
    int32_t Estimate(const std::array<int32_t, Num>& datas)
    {
        // 计算数据和权重的内积
        return std::inner_product(weights.begin(), weights.end(), datas.begin(), int32_t(0));
    }

    // 根据学习率计算出下一次迭代的权重
    void UpdateWeight(int32_t rate, int32_t expectVal, int32_t estimateVal, const std::array<int32_t, Num>& datas)
    {
        int32_t deltaVal = expectVal - estimateVal;  // 期望值和预测值之间的差异
        for (uint32_t i = 0; i < Num; ++i) {
            weights[i] += rate * deltaVal * datas[i];
        }
        deltas.push_back(deltaVal);
    }

    // 损失函数
    double Loss() const
    {
        // 均方根误差
        int32_t squared_sum = std::inner_product(deltas.begin(), deltas.end(), deltas.begin(), int32_t(0));
        return sqrt(squared_sum * 1.0 / deltas.size());
    }

    void ClearDeltas() { deltas.clear(); }

private:
    std::array<int32_t, Num> weights;  // 权重
    std::vector<int32_t> deltas;       // 每次迭代的误差
};
#endif  // TOY_PERCEPTRON_H
