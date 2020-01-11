#pragma once

void print_sig_info(
    const google::protobuf::Map<std::string, tf::TensorInfo>& map) {
    for (const auto& [k, v] : map) {
        std::cout << "Key: " << k << '\n';
        std::cout << "Name: " << v.name() << '\n';
        std::cout << "Tensor shape: " << v.tensor_shape().DebugString() << '\n';
        std::cout << "Datatype: " << me::enum_name(v.dtype()) << '\n';
        std::cout << '\n';
    }
}
