#ifndef WINDOW_SETTINGS_H
#define WINDOW_SETTINGS_H

#include <iostream>
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
#include <QSlider>

#include "Settings.hpp"

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
		void setValues();
		void changeHairColorButton(QColor pNewColor);

	private:
		QColor hairColor;
		QComboBox *hairTypeComboBox;
		QLabel *hairColorLabel;
		QLabel *hairLengthLabel;
		QLabel *hairNumberLabel;
		QLabel *hairTypeLabel;
		QLabel *hairWidthLabel;
		QLabel *hairParticlesLabel;
		QLabel *hairInterpolLabel;
		QPushButton *hairColorButton;
		QSlider *hairLengthSlider;
		QSlider *hairNumberSlider;
		QSlider *hairWidthSlider;
		QSlider *hairParticlesSlider;
		QSlider *hairInterpolSlider;
		QString colorText;
		QVBoxLayout *hairsLayout;

	private slots:
		void hairColorChanged();
		void hairLengthChanged();
		void hairNumberChanged();
		void hairWidthChanged();
		void hairParticlesChanged();
		void hairInterpolChanged();
};

class EnvironmentTab : public QWidget
{
    Q_OBJECT

	public:
		EnvironmentTab(QWidget *parent = 0);
		void setValues();
		void changeBgColorButton(QColor pNewColor);

	private:
		QCheckBox *envTextCheckBox;
		QCheckBox *envSimulationShowCheckBox;
		QColor envBgColor;
		QComboBox *envMultisamplingComboBox;
		QLabel *envBgColorLabel;
		QLabel *envMultisamplingLabel;
		QPushButton *envBgColorButton;
		QString colorText;
		QVBoxLayout *envLayout;
		QLabel *empty;
		QLabel *sizeCoefLabel;
		QLabel *controlPointRadiusLabel;
		QLabel *controlPointMassLabel;
		QLabel *hairMassLabel;
		QSlider *sizeCoefSlider;
		QSlider *controlPointRadiusSlider;
		QSlider *controlPointMassSlider;
		QSlider *hairMassSlider;

	private slots:
		void bgColorChanged();
		void sizeCoefChanged();
		void controlPointRadiusChanged();
		void controlPointMassChanged();
		void hairMassChanged();
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
		SettingsWindow(Settings** pSettings, QWidget* parent = 0);

	private:
		ControlTab* controlTab;
		HairsTab* hairsTab;
		EnvironmentTab* environmentTab;
		AboutTab* aboutTab;
		QTabWidget* tabWidget;
		QDialogButtonBox* buttonBox;
		QVBoxLayout* mainLayout;

	private slots:
		void accept();
};

#endif