#ifndef CSCI207_PROJECT_STACK_H
#define CSCI207_PROJECT_STACK_H

#include <QString>
#include <vector>


class Stack {
private:
	std::vector<QString> messages;

public:
	void push(QString const &message) {
		messages.push_back(message);
	}

	void pop() {
		if (!messages.empty())
			messages.pop_back();
	}

	QString top() const {
		if (messages.empty())
			return "Log is empty.";

		return messages.back();
	}

	bool empty() const {
		return messages.empty();
	}
};


#endif //CSCI207_PROJECT_STACK_H
