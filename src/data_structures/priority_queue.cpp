#include "data_structures/priority_queue.hpp"
#include "physics/collision_resolution/particle_contact_resolver.hpp"
#include <algorithm>
#include <stdexcept>
#include <utility>

template class PriorityQueue<int>;
template class PriorityQueue<SeparatingVelocityContact>;
template class PriorityQueue<InterpenetrationContact>;

template<typename T>
void
PriorityQueue<T>::insert(T item_to_insert)
{
  items.push_back(item_to_insert);
  _bubble_up();
};

template<typename T>
bool
PriorityQueue<T>::is_empty()
{
  return items.empty();
}

template<typename T>
T
PriorityQueue<T>::pop()
{
  if (items.empty()) {
    throw std::runtime_error("The priority queue is empty");
  }

  std::swap(items.front(), items.back());
  T _item_to_return = std::move(items.back());
  items.pop_back();
  _bubble_down();
  return _item_to_return;
}

template<typename T>
void
PriorityQueue<T>::_bubble_up()
{
  if (items.size() == 1) {
    return;
  }

  int _index_of_node_to_bubble_up = items.size() - 1;
  while (_index_of_node_to_bubble_up > 0) {
    int _parent_index = _get_parent_index(_index_of_node_to_bubble_up);
    if (items[_parent_index] < items[_index_of_node_to_bubble_up]) {
      return;
    }

    std::swap(items[_parent_index], items[_index_of_node_to_bubble_up]);
    _index_of_node_to_bubble_up = _parent_index;
  }
}

template<typename T>
void
PriorityQueue<T>::_bubble_down()
{
  int _index_of_item_to_bubble_down = 0;

  while (!_is_leaf(_index_of_item_to_bubble_down)) {
    int _smallest_child_index =
      _get_left_child_index(_index_of_item_to_bubble_down);
    int _index_of_right_child =
      _get_right_child_index(_index_of_item_to_bubble_down);

    if (_does_node_exist(_index_of_right_child)) {
      if (items[_index_of_right_child] < items[_smallest_child_index]) {
        _smallest_child_index = _index_of_right_child;
      }
    }

    if (items[_index_of_item_to_bubble_down] < items[_smallest_child_index]) {
      _smallest_child_index = _index_of_item_to_bubble_down;
    }

    if (_smallest_child_index == _index_of_item_to_bubble_down)
      return;

    std::swap(items[_index_of_item_to_bubble_down],
              items[_smallest_child_index]);
    _index_of_item_to_bubble_down = _smallest_child_index;
  }
}

template<typename T>
bool
PriorityQueue<T>::_is_leaf(int node_index)
{
  return (items.size() < (node_index * 2) + 2);
}

template<typename T>
int
PriorityQueue<T>::_get_parent_index(int node_index)
{
  return (node_index - 1) / 2;
}

template<typename T>
int
PriorityQueue<T>::_get_left_child_index(int node_index)
{
  return (node_index * 2) + 1;
}

template<typename T>
int
PriorityQueue<T>::_get_right_child_index(int node_index)
{
  return (node_index * 2) + 2;
}

template<typename T>
bool
PriorityQueue<T>::_does_node_exist(int node_index)
{
  return (node_index < items.size());
}

// template <typename T> void PriorityQueue<T>::print() {
//   auto iterator = items.begin();
//   for (; iterator < items.end(); iterator++) {
//     std::cout << *iterator;
//   }
//
//   std::cout << std::endl;
// }
