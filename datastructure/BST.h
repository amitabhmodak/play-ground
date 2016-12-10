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
		Node(T value):m_data(value){};
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
			std::cout << "Inorder :\n";
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

		void inorderSingleLoop() {
			std::cout << "InorderSingleLoop :\n";
			std::stack<std::shared_ptr<Node<T>>> stack;
			auto node = m_root;
			 
			while (node != nullptr || !stack.empty()) {
				if (node != nullptr) {
					stack.push(node);
					node = node->m_left;
				}
				else {
					node = stack.top();
					stack.pop();
					std::cout << node->m_data << " ";
					node = node->m_right;
					
				}
			}
			std::cout << "\n";
		}

		void preorder() {
			std::cout << "Preorder :\n";
			std::stack<std::shared_ptr<Node<T>>> stack;
			auto node = m_root;
			while (node != nullptr || !stack.empty()) {
				while (node != nullptr) {
					std::cout << node->m_data << " ";
					if (node->m_right != nullptr)
						stack.push(node->m_right);
					node = node->m_left;
				}
				if (!stack.empty()) {
					node = stack.top();
					stack.pop();
				}
			}
			std::cout << "\n";
		}


		void preorderSingleLoop() {
			std::cout << "PreorderSingleLoop :\n";
			std::stack<std::shared_ptr<Node<T>>> stack;
			auto node = m_root;
			stack.push(node);
			while (!stack.empty()) {
				node = stack.top();
				stack.pop();
				std::cout << node->m_data << " ";
				if (node->m_right != nullptr)
					stack.push(node->m_right);
				if (node->m_left != nullptr)
					stack.push(node->m_left);
			}
			std::cout << "\n";
		}

		void postorder() {
			std::cout << "Postorder :\n";
			std::stack<std::shared_ptr<Node<T>>> stack;
		 
			auto node = m_root;
			auto lastNodeVisited = m_root;
			lastNodeVisited = nullptr;
			while (node != nullptr || !stack.empty()) {
				//traverse left
				if (node != nullptr) {
					stack.push(node);
					node = node->m_left;
				}
				else {
					auto peekNode = stack.top();
					if (peekNode->m_right && lastNodeVisited != peekNode->m_right) {
						node = peekNode->m_right;
					}
					else {
						std::cout << peekNode->m_data << " ";
						lastNodeVisited = stack.top();
						stack.pop();
					}
				}
			}

			std::cout << "\n";
			
		}
		
		void preorderRecur() {
			std::cout << "PreorderRecur :\n";
			preorderRecur(m_root);
			std::cout << "\n";
		}
		void postorderRecur() {
			std::cout << "PostorderRecur :\n";
			postorderRecur(m_root);
			std::cout << "\n";
		}
		void inorderRecur() {
			std::cout << "InorderRecur :\n";
			inorderRecur(m_root);
			std::cout << "\n";
		}

		void inorderRecur(std::shared_ptr<Node<T>> node)
		{
			if (node == nullptr)
				return;
			inorderRecur(node->m_left);
			std::cout << node->m_data << " ";
			inorderRecur(node->m_right);
		}
		void preorderRecur(std::shared_ptr<Node<T>>  node)
		{
			if (node == nullptr)
				return;
			std::cout << node->m_data << " ";
			preorderRecur(node->m_left);
			preorderRecur(node->m_right);
		}

		void postorderRecur(std::shared_ptr<Node<T>> node)
		{
			if (node == nullptr)
				return;
			postorderRecur(node->m_left);
			postorderRecur(node->m_right);
			std::cout << node->m_data << " ";
		}

		 
	};

	class DriverProgram {
	public:
		void test();
	};
}