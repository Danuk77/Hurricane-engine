#include <memory>
#include <vector>
template<typename T>
class PriorityQueue {
  std::vector<T> items;
public:
  void insert(T item_to_insert);
  T pop();
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

