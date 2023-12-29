#ifndef CSCI207_PROJECT_LOGDISPLAY_H
#define CSCI207_PROJECT_LOGDISPLAY_H

#include <QPlainTextEdit>
#include <QScrollBar>


class LogDisplay : public QPlainTextEdit {
Q_OBJECT

public:
	explicit LogDisplay(QWidget *parent = nullptr)
			: QPlainTextEdit(parent)
	{
		setReadOnly(true);
	}

	void appendMessage(const QString &text)
	{
		appendPlainText(text);
		verticalScrollBar()->setValue(verticalScrollBar()->maximum());
	}
};


#endif //CSCI207_PROJECT_LOGDISPLAY_H
