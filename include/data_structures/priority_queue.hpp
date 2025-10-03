#include <memory>
#include <vector>
template<typename T>
class PriorityQueue {
  std::vector<std::unique_ptr<T>> items;
public:
  void insert(std::unique_ptr<T> item_to_insert);
  std::unique_ptr<T> pop();
  void print();
private:
  void _bubble_up();
  void _bubble_down();

  bool _is_leaf(int node_index);
  bool _does_node_exist(int node_index);
  int _get_parent_index(int node_index);
  int _get_left_child_index(int node_index);
  int _get_right_child_index(int node_index);
};

