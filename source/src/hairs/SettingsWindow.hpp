#ifndef WINDOW_SETTINGS_H
#define WINDOW_SETTINGS_H

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileInfo>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <map>
#include <QColorDialog>
#include <QtGui>

class ControlTab : public QWidget
{
    Q_OBJECT
	
	public:
		ControlTab(QWidget *parent = 0);

	private:
		QLabel *controlsLabel;
		QVBoxLayout *controlLayout;

};

class HairsTab : public QWidget
{
    Q_OBJECT

	public:
		HairsTab(QWidget *parent = 0);

	private:
		QColor hairColor;
		QComboBox *hairLengthComboBox;
		QComboBox *hairNumberComboBox;
		QComboBox *hairTypeComboBox;
		QLabel *hairColorLabel;
		QLabel *hairLengthLabel;
		QLabel *hairNumberLabel;
		QLabel *hairTypeLabel;
		QPushButton *hairColorButton;
		QString colorText;
		QVBoxLayout *hairsLayout;

	private slots:
		void setHairColor();
};

class EnvironmentTab : public QWidget
{
    Q_OBJECT

	public:
		EnvironmentTab(QWidget *parent = 0);

	private:
		QCheckBox *envTextCheckBox;
		QColor envBgColor;
		QComboBox *envMultisamplingComboBox;
		QLabel *envBgColorLabel;
		QLabel *envMultisamplingLabel;
		QPushButton *envBgColorButton;
		QString colorText;
		QVBoxLayout *envLayout;

	private slots:
		void setBgColor();
};

class AboutTab : public QWidget
{
    Q_OBJECT

	public:
		AboutTab(QWidget *parent = 0);

	private:
		QLabel *aboutLabel;
		QVBoxLayout *aboutLayout;
};

class SettingsWindow : public QDialog
{
    Q_OBJECT

	public:
		SettingsWindow(QWidget *parent = 0);
		std::map<std::string, std::string> *getSettings();
		bool setSettings(std::map<std::string, std::string> *pSettings);
		//std::string getSettingValue(std::string pSettingName);

	private:
		QTabWidget *tabWidget;
		QDialogButtonBox *buttonBox;
		QVBoxLayout *mainLayout;
		std::map<std::string, std::string> settings;
};

#endif