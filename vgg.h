#ifndef VGG_H
#define VGG_H

#include<torch/script.h>
#include<torch/torch.h>
#include<vector>

// Hyperparameters for Convolution
inline torch::nn::Conv2dOptions conv_options(int64_t in_planes, int64_t out_planes, int64_t kerner_size, int64_t stride = 1, int64_t padding = 0, bool with_bias = false) {
    torch::nn::Conv2dOptions conv_options = torch::nn::Conv2dOptions(in_planes, out_planes, kerner_size);
    conv_options.stride(stride);
    conv_options.padding(padding);
    conv_options.bias(with_bias);
    return conv_options;
}

// Hyperparameters for MaxPool2d
inline torch::nn::MaxPool2dOptions maxpool_options(int kernel_size, int stride) {
    torch::nn::MaxPool2dOptions maxpool_options(kernel_size);
    maxpool_options.stride(stride);
    return maxpool_options;
}

// Similar to the make_features function in pytorch, return a CNN instance which is a torch::nnL::Sequential objects
torch::nn::Sequential make_features(std::vector<int> &cfg, bool batch_norm);

// Dinifition for VGG, including initialization and forwarding
class VGGImpl: public torch::nn::Module {
private:
    torch::nn::Sequential features_{nullptr};
    torch::nn::AdaptiveAvgPool2d avgpool{nullptr};
    torch::nn::Sequential classifier;
public:
    VGGImpl(std::vector<int> &cfg, int num_classes = 1000, bool batch_norm = false);
    torch::Tensor forward(torch::Tensor x);
};
TORCH_MODULE(VGG);

// Claim for VGG16bn function
//VGG vgg16bn(int num_classes); //??

#endif // VGG_H