#pragma once

#include<memory>
#include<iostream>
#include <stack>

namespace bst {

	template<typename T>

	struct Node {
		T m_data;
		std::shared_ptr<Node<T>> m_left;
		std::shared_ptr<Node<T>> m_right;
		Node(T value) {
			m_data = value;
		}
		~Node() {
			std::cout << "Node deleted with value " << m_data << "\n";
		}
	};


	template<typename T>
	class BST
	{
		std::shared_ptr<Node<T>> m_root;
	public:
		BST() = default;
		~BST() = default;

		void add(T data) {

			if (m_root == nullptr) {
				m_root = std::make_shared<Node<T>>(data);
				return;
			}
			auto parent = m_root;
			auto prev = m_root;
			while (parent != nullptr) {
				prev = parent;

				if (parent->m_data < data) {
					parent = parent->m_right;
				}
				else {
					parent = parent->m_left;
				}
			}
			if (prev->m_data < data) {
				prev->m_right = std::make_shared<Node<T>>(data);
			}
			else {
				prev->m_left = std::make_shared<Node<T>>(data);
			}

		}
 
		void inorder() {
			std::stack<std::shared_ptr<Node<T>>> stack;
			auto node = m_root;

			while (node != nullptr || !stack.empty()) {
				while (node != nullptr) {
					stack.push(node);
					node = node->m_left;
				}
				if (!stack.empty()) {
					auto value = stack.top();
					stack.pop();
					std::cout << value->m_data << " ";
					node = value->m_right;
				}
			}

			std::cout << "\n";
		}
		 
	};

	class DriverProgram {
	public:
		void test();
	};
}