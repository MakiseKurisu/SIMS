#include "Header Files\stdafx.h"


int userlocation = 0;

studentView::studentView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.usernameLabel->setText("");
	ui.stackedWidget->setCurrentIndex(0);
	ui.backButton->hide();
	
}

studentView::studentView(QString userName)
{
	vector<users>allUsers = populateUsers();
	vector<Student>allStudents = populateStudents();
	vector<classes>allClasses = populateClasses();
	vector<records>allRecords = populateRecords();
	vector<faculty>allFaculty = populateFaculty();
	//QStrings
	QString user = userName;
	QString fullName;
	QString dob;
	QString id;
	QString semester;
	QString gpa;
	QString homeAddress;
	QString emaiAddress;
	QString phoneNumber;
	QString Major;

	//strings
	string username = user.toStdString();
	string name;
	
	
	for (int i = 0; i < allStudents.size(); i++)
	{
		if (allStudents[i].userName == username)
		{
			userlocation = i;
			break;
		}

	}
	name = allStudents[userlocation].firstName + " " + allStudents[userlocation].lastName;

	fullName = QString::fromStdString(name);
	dob = QString::fromStdString(allStudents[userlocation].DOB);
	id = QString::fromStdString(allStudents[userlocation].studentID);
	semester = QString::fromStdString(allStudents[userlocation].semesterEnrolled);
	homeAddress = QString::fromStdString(allStudents[userlocation].homeAddress);
	emaiAddress = QString::fromStdString(allStudents[userlocation].emailAddress);
	phoneNumber = QString::fromStdString(allStudents[userlocation].phoneNumber);
	Major = QString::fromStdString(allStudents[userlocation].Major);

	ui.setupUi(this);

	ui.studentInfoBrowser->setText("Name: " + fullName + "\nUsername: "+ user +"\nStudent ID: "+ id +"\n\nDate of Birth: "+ dob +"\nHome Address: "+homeAddress+"\nPhone Number: "+phoneNumber+"\nEmail: "+emaiAddress+"\n\nMajor: "+Major+"\nSemester Enrolled: "+ semester +"\nSemester GPA: ");

	ui.usernameLabel->setText(fullName);
	ui.stackedWidget->setCurrentIndex(0);
	//combobox implement
	ui.classesSearchBox->addItem("CRN");
	ui.classesSearchBox->addItem("Subject");
	ui.classesSearchBox->addItem("Course ID");
	ui.classesSearchBox->addItem("Name");
	ui.classesSearchBox->addItem("Semester");
	ui.classesSearchBox->addItem("Days");
	ui.classesSearchBox->addItem("Instructor");
	ui.classesSearchBox->addItem("Room");
	ui.backButton->hide();
}

void studentView::on_viewScheduleButton_clicked()
{
	vector<users>allUsers = populateUsers();
	vector<Student>allStudents = populateStudents();
	vector<classes>allClasses = populateClasses();
	vector<records>allRecords = populateRecords();
	vector<faculty>allFaculty = populateFaculty();
	ui.stackedWidget->setCurrentIndex(1);
	QString classes;
	
	//display schedule
	for (int i = 0; i < allRecords.size(); i++)
	{
		if (allStudents[userlocation].userName == allRecords[i].Username)
		{
			classes += QString::fromStdString(to_string(allClasses[i].CRN)) + " "
				+ QString::fromStdString(allClasses[i].Subject) + " "
				+ QString::fromStdString(to_string(allClasses[i].courseID)) + " "
				+ QString::fromStdString(allClasses[i].Name) + " "
				+ QString::fromStdString(allClasses[i].Semester) + " "
				+ QString::fromStdString(allClasses[i].classDays) + " "
				+ QString::fromStdString(allClasses[i].classTime) + " ";
			for (int j = 0; j < allFaculty.size();j++)
			{
				if (allClasses[i].Instructor == allFaculty[j].userName )
				{
					classes += QString::fromStdString(allFaculty[j].firstName) + " " + QString::fromStdString(allFaculty[j].lastName) + " ";
				}
			}
				
			classes += QString::fromStdString(allClasses[i].Room) + "\n";
		}
	}
	ui.semesterScheduleView->setText(classes);

	//change header text
	ui.welcomeLabel->setText("View Schedule");

	//enable back button
	ui.backButton->show();
	ui.backButton->setEnabled(true);

	
}

void studentView::on_manageScheduleButton_clicked()
{
	vector<users>allUsers = populateUsers();
	vector<Student>allStudents = populateStudents();
	vector<classes>allClasses = populateClasses();
	vector<records>allRecords = populateRecords();
	vector<faculty>allFaculty = populateFaculty();

	ui.stackedWidget->setCurrentIndex(2);

	//change header text
	ui.welcomeLabel->setText("Manage Schedule");
	
	//create QT items
	QStandardItemModel *model = new QStandardItemModel(this);
	QList<QStandardItem *> items;
	//set headers name and size
	QStringList headers;
	headers << "CRN" << "Subject" << "Course ID" << "Name" << "Semester" << "Day" << "Time" << "Instructor" << "Room";
	model->setColumnCount(allClasses.size() - 1);
	model->setHorizontalHeaderLabels(headers);
	//populate schedule
	for (int i = 0; i < allRecords.size(); i++)
	{
		if (allStudents[userlocation].userName == allRecords[i].Username)
		{
			items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].CRN))));
			items.append(new QStandardItem(QString::fromStdString(allClasses[i].Subject)));
			items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].courseID))));
			items.append(new QStandardItem(QString::fromStdString(allClasses[i].Name)));
			items.append(new QStandardItem(QString::fromStdString(allClasses[i].Semester)));
			items.append(new QStandardItem(QString::fromStdString(allClasses[i].classDays)));
			items.append(new QStandardItem(QString::fromStdString(allClasses[i].classTime)));
			for (int j = 0; j < allFaculty.size(); j++)
			{
				if (allClasses[i].Instructor == allFaculty[j].userName)
				{
					items.append(new QStandardItem(QString::fromStdString(allFaculty[j].firstName) + " " + QString::fromStdString(allFaculty[j].lastName)));
				}
			}
	
			items.append(new QStandardItem(QString::fromStdString(allClasses[i].Room)));
			model->appendRow(items);
			items.clear();
		}
	}
	ui.manageClassesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.manageClassesView->setModel(model);

	//enable back button
	ui.backButton->show();
	ui.backButton->setEnabled(true);
}

void studentView::on_addClassButton_clicked()
{
	//populate all vectors
	vector<users>allUsers = populateUsers();
	vector<Student>allStudents = populateStudents();
	vector<classes>allClasses = populateClasses();
	vector<records>allRecords = populateRecords();
	vector<faculty>allFaculty = populateFaculty();
	//variables
	string username = allStudents[userlocation].userName;
	int crnEntered = ui.crnAddRemoveLine->text().toInt();;
	//get entered CRN


	for (int i = 0; i < allClasses.size(); i++)
	{
		if (crnEntered == allClasses[i].CRN)
		{
			//class already in student schedule -error
			for (int j = 0; j < allRecords.size(); j++)
			{
				if (crnEntered == allRecords[j].Crn && username == allRecords[j].Username)
				{
					ui.addRemoveClassLabel->setText("Class already in schedule!");
				}
			}
		}
		//crn does not exist - error
		else if (crnEntered != allClasses[i].CRN)
		{
			ui.addRemoveClassLabel->setText("No such Class exist!");
		}
	}
	
}

void studentView::on_removeClassButton_clicked()
{
	//populate all vectors
	vector<users>allUsers = populateUsers();
	vector<Student>allStudents = populateStudents();
	vector<classes>allClasses = populateClasses();
	vector<records>allRecords = populateRecords();
	vector<faculty>allFaculty = populateFaculty();


}

void studentView::on_viewClassesButton_clicked()
{
	vector<users>allUsers = populateUsers();
	vector<Student>allStudents = populateStudents();
	vector<classes>allClasses = populateClasses();
	vector<records>allRecords = populateRecords();
	vector<faculty>allFaculty = populateFaculty();

	ui.stackedWidget->setCurrentIndex(3);
	//change header text
	ui.welcomeLabel->setText("View Classes");

	//create QT items
	QStandardItemModel *model = new QStandardItemModel(this);
	QList<QStandardItem *> items;
	//set headers name and size
	QStringList headers;
	headers << "CRN" << "Subject"<<"Course ID"<<"Name"<<"Semester"<<"Day"<<"Time"<<"Instructor"<<"Room";
	model->setColumnCount(allClasses.size()-1);
	model->setHorizontalHeaderLabels(headers);
	//populate table
	for (int i = 0; i < allClasses.size()-1; i++)
	{
		model->setRowCount(i);
		items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].CRN))));
		items.append(new QStandardItem(QString::fromStdString(allClasses[i].Subject)));
		items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].courseID))));
		items.append(new QStandardItem(QString::fromStdString(allClasses[i].Name)));
		items.append(new QStandardItem(QString::fromStdString(allClasses[i].Semester)));
		items.append(new QStandardItem(QString::fromStdString(allClasses[i].classDays)));
		items.append(new QStandardItem(QString::fromStdString(allClasses[i].classTime)));
		items.append(new QStandardItem(QString::fromStdString(allClasses[i].Instructor)));
		items.append(new QStandardItem(QString::fromStdString(allClasses[i].Room)));
		model->appendRow(items);
		items.clear();

	}
	ui.classesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.classesView->setModel(model);
	//enable back button
	ui.backButton->show();
	ui.backButton->setEnabled(true);
}

void studentView::on_searchButton_clicked()
{
	vector<users>allUsers = populateUsers();
	vector<Student>allStudents = populateStudents();
	vector<classes>allClasses = populateClasses();
	vector<records>allRecords = populateRecords();
	vector<faculty>allFaculty = populateFaculty();

	//create QT items
	QStandardItemModel *model = new QStandardItemModel(this);
	QList<QStandardItem *> items;
	//set headers name and size
	QStringList headers;
	headers << "CRN" << "Subject" << "Course ID" << "Name" << "Semester" << "Day" << "Time" << "Instructor" << "Room";
	model->setHorizontalHeaderLabels(headers);

	if (ui.classesSearchBox->currentIndex() == 0)
	{
		QString searchClass = ui.searchClassesInput->text();
		int crn = searchClass.toInt();
		
		//populate table
		for (int i = 0; i < allClasses.size() - 1; i++)
		{
			if (crn == allClasses[i].CRN) {
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].CRN))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Subject)));
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].courseID))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Name)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Semester)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classDays)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classTime)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Instructor)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Room)));
				model->appendRow(items);
				items.clear();
			}

		}
		ui.classesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.classesView->setModel(model);
	}
	else if (ui.classesSearchBox->currentIndex() == 1)
	{
		QString searchClass = ui.searchClassesInput->text().toLower();
		string subject = searchClass.toStdString();

		//populate table
		for (int i = 0; i < allClasses.size() - 1; i++)
		{
			string searchSubject = "";
			for (int j = 0; j < allClasses[i].Subject.length(); j++)
			{
				searchSubject += tolower(allClasses[i].Subject[j]);
			}
			if (subject == searchSubject) {
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].CRN))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Subject)));
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].courseID))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Name)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Semester)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classDays)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classTime)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Instructor)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Room)));
				model->appendRow(items);
				items.clear();
			}

		}
		ui.classesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.classesView->setModel(model);
	}
	else if (ui.classesSearchBox->currentIndex() == 2)
	{
		QString searchClass = ui.searchClassesInput->text();
		int courseID = searchClass.toInt();

		//populate table
		for (int i = 0; i < allClasses.size() - 1; i++)
		{
			if (courseID == allClasses[i].courseID) {
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].CRN))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Subject)));
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].courseID))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Name)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Semester)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classDays)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classTime)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Instructor)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Room)));
				model->appendRow(items);
				items.clear();
			}

		}
		ui.classesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.classesView->setModel(model);
	}
	else if (ui.classesSearchBox->currentIndex() == 3)
	{
		QString searchClass = ui.searchClassesInput->text();
		string name = searchClass.toStdString();

		//populate table
		for (int i = 0; i < allClasses.size() - 1; i++)
		{
			if (name == allClasses[i].Name) {
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].CRN))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Subject)));
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].courseID))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Name)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Semester)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classDays)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classTime)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Instructor)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Room)));
				model->appendRow(items);
				items.clear();
			}

		}
		ui.classesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.classesView->setModel(model);
	}
	else if (ui.classesSearchBox->currentIndex() == 4)
	{
		QString searchClass = ui.searchClassesInput->text();
		string semester = searchClass.toStdString();

		//populate table
		for (int i = 0; i < allClasses.size() - 1; i++)
		{
			if (semester == allClasses[i].Semester) {
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].CRN))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Subject)));
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].courseID))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Name)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Semester)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classDays)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classTime)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Instructor)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Room)));
				model->appendRow(items);
				items.clear();
			}

		}
		ui.classesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.classesView->setModel(model);
	}
	else if (ui.classesSearchBox->currentIndex() == 5)
	{
		QString searchClass = ui.searchClassesInput->text();
		string days = searchClass.toStdString();

		//populate table
		for (int i = 0; i < allClasses.size() - 1; i++)
		{
			if (days == allClasses[i].classDays) {
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].CRN))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Subject)));
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].courseID))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Name)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Semester)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classDays)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classTime)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Instructor)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Room)));
				model->appendRow(items);
				items.clear();
			}

		}
		ui.classesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.classesView->setModel(model);
	}
	else if (ui.classesSearchBox->currentIndex() == 6)
	{
		QString searchClass = ui.searchClassesInput->text();
		string instructor = searchClass.toStdString();

		//populate table
		for (int i = 0; i < allClasses.size() - 1; i++)
		{
			if (instructor == allClasses[i].Instructor) {
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].CRN))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Subject)));
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].courseID))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Name)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Semester)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classDays)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classTime)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Instructor)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Room)));
				model->appendRow(items);
				items.clear();
			}

		}
		ui.classesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.classesView->setModel(model);
	}
	else if (ui.classesSearchBox->currentIndex() == 7)
	{
		QString searchClass = ui.searchClassesInput->text();
		string room = searchClass.toStdString();

		//populate table
		for (int i = 0; i < allClasses.size() - 1; i++)
		{
			if (room == allClasses[i].Room) {
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].CRN))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Subject)));
				items.append(new QStandardItem(QString::fromStdString(to_string(allClasses[i].courseID))));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Name)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Semester)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classDays)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].classTime)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Instructor)));
				items.append(new QStandardItem(QString::fromStdString(allClasses[i].Room)));
				model->appendRow(items);
				items.clear();
			}

		}
		ui.classesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.classesView->setModel(model);
	}
}

void studentView::on_changePasswordButton_clicked()
{

	ui.stackedWidget->setCurrentIndex(4);

	//change header text
	ui.welcomeLabel->setText("Change Password");
	

	//enable back button
	ui.backButton->show();
	ui.backButton->setEnabled(true);
}

void studentView::on_submitButton_clicked()
{
	vector<users>allUsers = populateUsers();
	vector<Student>allStudents = populateStudents();
	vector<classes>allClasses = populateClasses();
	vector<records>allRecords = populateRecords();
	vector<faculty>allFaculty = populateFaculty();

	QString newPassword;
	QString currentPasswordTyped = ui.currentPasswordField->text();
	QString currentPassword;
	string username = allStudents[userlocation].userName;
	string newVerifyPassword;
	//getting user password
	for (int i = 0; i < allUsers.size(); i++)
	{
		if (allStudents[userlocation].userName == allUsers[i].username)
		{
			currentPassword = QString::fromStdString(allUsers[i].password);
			break;
		}
	}

	//getcurrentPassword
	if ( currentPasswordTyped == "")
	{
		ui.passwordChangeStatusLabel->setStyleSheet("QLabel { background-color : red; color : white; }");
		ui.passwordChangeStatusLabel->setText("Current password can not be blank!");
	}
	else if (currentPasswordTyped !=currentPassword )
	{
		ui.passwordChangeStatusLabel->setStyleSheet("QLabel { background-color : red; color : white; }");
		ui.passwordChangeStatusLabel->setText("Incorrect current password!");
	}
	else
	{
		newPassword = ui.newPasswordField->text();
		if (newPassword != ui.verifyNewPasswordField->text())
		{
			ui.passwordChangeStatusLabel->setStyleSheet("QLabel { background-color : red; color : white; }");
			ui.passwordChangeStatusLabel->setText("The new password does not match!");
		}
		else if (newPassword == "")
		{
			ui.passwordChangeStatusLabel->setStyleSheet("QLabel { background-color : red; color : white; }");
			ui.passwordChangeStatusLabel->setText("The new password can not be blank!");
		}
		else
		{
			ui.currentPasswordField->setText("");
			ui.newPasswordField->setText("");
			ui.verifyNewPasswordField->setText("");

			newVerifyPassword = newPassword.toStdString();
			changePassword(username, newVerifyPassword);

			ui.passwordChangeStatusLabel->setStyleSheet("QLabel { background-color : green; color : white; }");
			ui.passwordChangeStatusLabel->setText("Password has been changed!");
		}


	}
}

void studentView::on_backButton_clicked()
{
	//change header text
	ui.welcomeLabel->setText("Student Portal");
	ui.backButton->hide();
	ui.stackedWidget->setCurrentIndex(0);
}

void studentView::on_logoutButton_clicked()
{
	this->hide();
	loginView *login = new loginView();
	login->show();
}