#pragma once

/*This file is part of SIMS (Student Information Management System).

SIMS is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SIMS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SIMS.If not, see <http://www.gnu.org/licenses/>.
*/

#include <qwidget.h>
#include <qobject.h>
#include <ui_studentView.h>


class studentView : public QWidget
{
	Q_OBJECT

public:
	studentView(QWidget *parent = Q_NULLPTR);
	studentView(QString userName);
public slots:
	void on_viewScheduleButton_clicked();
	void on_backButton_clicked();
	void on_logoutButton_clicked();
	void on_viewClassesButton_clicked();
	void on_changePasswordButton_clicked();
	void on_manageScheduleButton_clicked();
	void on_searchButton_clicked();
	void on_submitButton_clicked();
	void on_addClassButton_clicked();
	void on_removeClassButton_clicked();
	
private:
	Ui::studentView ui;
};
