#ifndef CSCI207_PROJECT_STACK_H
#define CSCI207_PROJECT_STACK_H

#include <QString>
#include <vector>


class Stack {
private:
	std::vector<QString> messages;

public:
	// Time complexity: O(1); Vector operations are O(1)
	void push(QString const &message) {
		messages.push_back(message);
	}

	// Time complexity: O(1)
	void pop() {
		if (!messages.empty())
			messages.pop_back();
	}

	// Time complexity: O(1)
	QString top() const {
		if (messages.empty())
			return "Log is empty.";

		return messages.back();
	}

	// Time complexity: O(1)
	bool empty() const {
		return messages.empty();
	}
};


#endif //CSCI207_PROJECT_STACK_H
