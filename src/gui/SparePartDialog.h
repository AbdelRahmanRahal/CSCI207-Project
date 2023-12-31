#ifndef CSCI207_PROJECT_SPAREPARTDIALOG_H
#define CSCI207_PROJECT_SPAREPARTDIALOG_H

#include <QDialog>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>


class SparePartDialog : public QDialog {
Q_OBJECT

public:
	explicit SparePartDialog(QWidget *parent = nullptr) : QDialog(parent) {
		// Create widgets
		lineEditNumber = new QLineEdit(this);
		lineEditName = new QLineEdit(this);
		lineEditCost = new QLineEdit(this);
		lineEditExistingParts = new QLineEdit(this);

		// Validators to ensure the user can only type numbers in these fields
		lineEditNumber->setValidator(new QIntValidator(this));
		lineEditCost->setValidator(new QDoubleValidator(this));
		lineEditExistingParts->setValidator(new QIntValidator(this));

		// Create buttons
		QPushButton *okButton = new QPushButton("OK", this);
		okButton->setDefault(true);
		connect(
			okButton,
			&QPushButton::clicked,
			this,
			&SparePartDialog::accept
		);

		QPushButton *cancelButton = new QPushButton("Cancel", this);
		connect(
			cancelButton,
			&QPushButton::clicked,
			this,
			&SparePartDialog::reject
		);

		// Create layout
		QVBoxLayout *layout = new QVBoxLayout(this);
		layout->addWidget(new QLabel("Name:", this));
		layout->addWidget(lineEditName);
		layout->addWidget(new QLabel("Number:", this));
		layout->addWidget(lineEditNumber);
		layout->addWidget(new QLabel("Cost:", this));
		layout->addWidget(lineEditCost);
		layout->addWidget(new QLabel("Existing Parts:", this));
		layout->addWidget(lineEditExistingParts);
		layout->addWidget(okButton);
		layout->addWidget(cancelButton);

		setLayout(layout);
	}

	~SparePartDialog() {}

	std::string getName() const { return lineEditName->text().toStdString(); }
	unsigned getNumber() const { return lineEditNumber->text().toUInt(); }
	double getCost() const { return lineEditCost->text().toDouble(); }
	unsigned getExistingParts() const { return lineEditExistingParts->text().toUInt(); }

protected:
	void accept() override {
		if (lineEditName->text().isEmpty() || lineEditNumber->text().isEmpty() ||
			lineEditCost->text().isEmpty() || lineEditExistingParts->text().isEmpty()) {
			QMessageBox::warning(this, "Empty Fields", "Please fill in all fields.");
		} else {
			QDialog::accept();
		}
	}
private:
	QLineEdit *lineEditName;
	QLineEdit *lineEditNumber;
	QLineEdit *lineEditCost;
	QLineEdit *lineEditExistingParts;
};

#endif //CSCI207_PROJECT_SPAREPARTDIALOG_H
