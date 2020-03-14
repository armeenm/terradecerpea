#pragma once

auto print_sig_info(google::protobuf::Map<std::string, tf::TensorInfo> const& map) -> void {
  for (auto const& [k, v] : map) {
    std::cout << "Key: " << k << '\n';
    std::cout << "Name: " << v.name() << '\n';
    std::cout << "Tensor shape: " << v.tensor_shape().DebugString() << '\n';
    std::cout << "Datatype: " << me::enum_name(v.dtype()) << '\n';
    std::cout << '\n';
  }
}
