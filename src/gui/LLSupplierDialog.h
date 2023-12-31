#ifndef CSCI207_PROJECT_LLSUPPLIERDIALOG_H
#define CSCI207_PROJECT_LLSUPPLIERDIALOG_H

#include <QDialog>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>


class LLSupplierDialog : public QDialog {
Q_OBJECT

public:
	explicit LLSupplierDialog(QWidget *parent = nullptr) : QDialog(parent) {
		// Create widgets
		lineEditCode = new QLineEdit(this);
		lineEditName = new QLineEdit(this);
		lineEditAddress = new QLineEdit(this);
		lineEditTelephone = new QLineEdit(this);
		lineEditEmail = new QLineEdit(this);

		// Validator to ensure the user can only type numbers in the code field
		lineEditCode->setValidator(new QIntValidator(this));

		// Create buttons
		QPushButton *okButton = new QPushButton("OK", this);
		okButton->setDefault(true);
		connect(
			okButton,
			&QPushButton::clicked,
			this,
			&LLSupplierDialog::accept
		);

		QPushButton *cancelButton = new QPushButton("Cancel", this);
		connect(
			cancelButton,
			&QPushButton::clicked,
			this,
			&LLSupplierDialog::reject
		);

		// Create layout
		QVBoxLayout *layout = new QVBoxLayout(this);
		layout->addWidget(new QLabel("Name:", this));
		layout->addWidget(lineEditName);
		layout->addWidget(new QLabel("Code:", this));
		layout->addWidget(lineEditCode);
		layout->addWidget(new QLabel("Address:", this));
		layout->addWidget(lineEditAddress);
		layout->addWidget(new QLabel("Telephone:", this));
		layout->addWidget(lineEditTelephone);
		layout->addWidget(new QLabel("Email:", this));
		layout->addWidget(lineEditEmail);
		layout->addWidget(okButton);
		layout->addWidget(cancelButton);

		setLayout(layout);
	}

	~LLSupplierDialog() {}

	std::string getName() const { return lineEditName->text().toStdString(); }
	unsigned getCode() const { return lineEditCode->text().toUInt(); }
	std::string getAddress() const { return lineEditAddress->text().toStdString(); }
	std::string getTelephone() const { return lineEditTelephone->text().toStdString(); }
	std::string getEmail() const { return lineEditEmail->text().toStdString(); }

protected:
	void accept() override {
		if (lineEditName->text().isEmpty() || lineEditCode->text().isEmpty() ||
			lineEditAddress->text().isEmpty() || lineEditTelephone->text().isEmpty() ||
			lineEditEmail->text().isEmpty()) {
			QMessageBox::warning(this, "Empty Fields", "Please fill in all fields.");
		} else {
			QDialog::accept();
		}
	}

private:
	QLineEdit *lineEditName;
	QLineEdit *lineEditCode;
	QLineEdit *lineEditAddress;
	QLineEdit *lineEditTelephone;
	QLineEdit *lineEditEmail;
};

#endif //CSCI207_PROJECT_LLSUPPLIERDIALOG_H
