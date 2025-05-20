# 时间推进框架

项目中基于C++的各种机制实现了五种通用时间推进框架（向前欧拉和SSP-RK3，支持预处理和后处理，支持扩展为其它时间离散格式），不同的框架实现各有优劣，因此全部保留：

- 运行时多态：
  - `solver_virtual.hpp`：基于虚函数
  - `solver_stdfunc.hpp`：基于 std::function，类型擦除

- 编译期多态：
  - `solver_crtp.hpp`：基于 CRTP
  - `solver_deducing.hpp`：基于 deducing this（C++23）
  - `solver_template.hpp`：基于模板参数

基于前两种框架的写法比较简单，但是性能偏低；基于后三种框架的写法比较复杂，但是有更好的性能。
