#include "SettingsWindow.hpp"

SettingsWindow::SettingsWindow(QWidget *parent) : QDialog(parent)
{
    tabWidget = new QTabWidget;
    tabWidget->addTab(new ControlTab(), tr("Controls"));
    tabWidget->addTab(new HairsTab(), tr("Hairs settings"));
    tabWidget->addTab(new EnvironmentTab(), tr("Environment Settings"));
    tabWidget->addTab(new AboutTab(), tr("About"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Menu"));
}

ControlTab::ControlTab(QWidget *parent) : QWidget(parent)
{
	controlsLabel = new QLabel(tr("<b>Key M:</b> menu<br>" 
		"<b>Key T:</b> enables the TrackballManipulator<br>"
		"<b>Key F:</b> enables the GhostCameraManipulator (fly mode)<br>"
		"<b>Key F1:</b> toggles fullscreen mode if supported<br>"
		"<b>Key F5:</b> saves a screenshot of the current OpenGL window<br>"
		"<b>Key C:</b> toggles the continuous update fo the OpenGL window<br>"
		"<b>Key U:</b> updates the OpenGL window content<br>"
		"<b>Key SPACE:</b> simulation run/stop<br>"
		"<b>Key ESC:</b> quit application<br>"
		));
    
	controlLayout = new QVBoxLayout;
    controlLayout->addWidget(controlsLabel);
    setLayout(controlLayout);
}

HairsTab::HairsTab(QWidget *parent) : QWidget(parent)
{
	hairTypeLabel = new QLabel(tr("Hairs type:"));
	hairTypeComboBox = new QComboBox;
	hairTypeComboBox->setEditable(false);
	hairTypeComboBox->addItem(tr("Straight"));
	hairTypeComboBox->addItem(tr("Curly"));

	hairLengthLabel = new QLabel(tr("Hairs length:"));
	hairLengthComboBox = new QComboBox;
	hairLengthComboBox->setEditable(false);
	hairLengthComboBox->addItem(tr("Very Short"));
	hairLengthComboBox->addItem(tr("Short"));
	hairLengthComboBox->addItem(tr("Medium"));
	hairLengthComboBox->addItem(tr("Long"));
	hairLengthComboBox->addItem(tr("Very Long"));

	hairColorLabel = new QLabel(tr("Hairs color:"));
	hairColorButton = new QPushButton(tr("Change hair color"));
	connect(hairColorButton, SIGNAL(clicked()), this, SLOT(setHairColor()));

	hairNumberLabel = new QLabel(tr("Hairs number:"));
	hairNumberComboBox = new QComboBox;
	hairNumberComboBox->setEditable(false);
	hairNumberComboBox->addItem(tr("Few (10K)"));
	hairNumberComboBox->addItem(tr("Medium (30K)"));
	hairNumberComboBox->addItem(tr("Many (50K)"));

    hairsLayout = new QVBoxLayout;
    hairsLayout->addWidget(hairTypeLabel);
    hairsLayout->addWidget(hairTypeComboBox);
    hairsLayout->addWidget(hairLengthLabel);
    hairsLayout->addWidget(hairLengthComboBox);
    hairsLayout->addWidget(hairColorLabel);
    hairsLayout->addWidget(hairColorButton);
    hairsLayout->addWidget(hairNumberLabel);
    hairsLayout->addWidget(hairNumberComboBox);
    setLayout(hairsLayout);
}

void HairsTab::setHairColor()
{
	colorText = "background-color: ";

	hairColor = QColorDialog::getColor(Qt::yellow, this);

    if (hairColor.isValid()) 
	{
		hairColorButton->setStyleSheet(colorText + hairColor.name());
    }
}

EnvironmentTab::EnvironmentTab(QWidget *parent) : QWidget(parent)
{
	envBgColorLabel = new QLabel(tr("Background color:"));
	envBgColorButton = new QPushButton(tr("Change background color"));
	connect(envBgColorButton, SIGNAL(clicked()), this, SLOT(setBgColor()));

	envMultisamplingLabel = new QLabel(tr("Multisampling:"));
	envMultisamplingComboBox = new QComboBox;
	envMultisamplingComboBox->setEditable(false);
	envMultisamplingComboBox->addItem(tr("OFF"));
	envMultisamplingComboBox->addItem(tr("2x"));
	envMultisamplingComboBox->addItem(tr("4x"));
	envMultisamplingComboBox->addItem(tr("8x"));
	envMultisamplingComboBox->addItem(tr("16x"));

	envTextCheckBox = new QCheckBox;
	envTextCheckBox->setCheckable(true);
	envTextCheckBox->setChecked(true);
	envTextCheckBox->setText(tr("Show text label"));

	envLayout = new QVBoxLayout;
    envLayout->addWidget(envMultisamplingLabel);
    envLayout->addWidget(envMultisamplingComboBox);
    envLayout->addWidget(envTextCheckBox);
    envLayout->addWidget(envBgColorLabel);
    envLayout->addWidget(envBgColorButton);
    setLayout(envLayout);
}

void EnvironmentTab::setBgColor()
{
	colorText = "background-color: ";

	envBgColor = QColorDialog::getColor(Qt::gray, this);

    if (envBgColor.isValid()) 
	{
		envBgColorButton->setStyleSheet(colorText + envBgColor.name());
    }
}

AboutTab::AboutTab(QWidget *parent) : QWidget(parent)
{
    aboutLabel = new QLabel(tr("<center><b>Hair simulation and visualization using GPU</b><br>(Diploma project)<br><br>Author: <b>Bc. Tomas Hurban</b><br>hurbant@gmail.com<br><br>2011, June<br><br>Slovak University of Technology Bratislava<br>FACULTY OF INFORMATICS AND INFORMATION TECHNOLOGIES"));
    
	aboutLayout = new QVBoxLayout;
    aboutLayout->addWidget(aboutLabel);
    setLayout(aboutLayout);
}
/*
std::map<std::string, std::string> *SettingsWindow::getSettings()
{
	settings.clear();
	std::string key;
	std::string value;

	// TODO

	return &settings;
}

bool SettingsWindow::setSettings(std::map<std::string, std::string> *pSettings)
{
	bool error = false;

	// TODO

	return error;
}*/
/*
std::string SettingsWindow::getSettingValue(std::string pSettingName)
{
	return settings.find(pSettingName)->second;
}
*/