#include "SettingsWindow.hpp"

SettingsWindow::SettingsWindow(Settings *pSettings, QWidget *parent) : QDialog(parent)
{
	controlTab = new ControlTab();
	hairsTab = new HairsTab();
	environmentTab = new EnvironmentTab();
	aboutTab = new AboutTab();

    tabWidget = new QTabWidget;
    tabWidget->addTab(controlTab, tr("Controls"));
    tabWidget->addTab(hairsTab, tr("Hairs settings"));
    tabWidget->addTab(environmentTab, tr("Environment Settings"));
    tabWidget->addTab(aboutTab, tr("About"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Menu"));

	hairsTab->setValues(pSettings);
	environmentTab->setValues(pSettings);
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
	hairTypeLabel = new QLabel(tr("Hairs type: "));
	hairTypeComboBox = new QComboBox;
	hairTypeComboBox->setEditable(false);
	hairTypeComboBox->addItem(tr("Straight"));
	//hairTypeComboBox->addItem(tr("Curly"));

	hairNumberLabel = new QLabel(tr("Hairs number: "));
	hairNumberSlider = new QSlider(Qt::Horizontal, this);
	hairNumberSlider->setRange(50, 10000);
	connect(hairNumberSlider, SIGNAL(valueChanged(int)), this, SLOT(hairNumberChanged()));
	hairNumberChanged();

	hairLengthLabel = new QLabel(tr("Hairs length: "));
	hairLengthSlider = new QSlider(Qt::Horizontal, this);
	hairLengthSlider->setRange(1, 100);
	connect(hairLengthSlider, SIGNAL(valueChanged(int)), this, SLOT(hairLengthChanged()));
	hairLengthChanged();

	hairWidthLabel = new QLabel(tr("Hairs width: "));
	hairWidthSlider = new QSlider(Qt::Horizontal, this);
	hairWidthSlider->setRange(5, 55);
	connect(hairWidthSlider, SIGNAL(valueChanged(int)), this, SLOT(hairWidthChanged()));
	hairWidthChanged();

	hairParticlesLabel = new QLabel(tr("Hair particles number: "));
	hairParticlesSlider = new QSlider(Qt::Horizontal, this);
	hairParticlesSlider->setRange(1, 50);
	connect(hairParticlesSlider, SIGNAL(valueChanged(int)), this, SLOT(hairParticlesChanged()));
	hairParticlesChanged();

	hairInterpolLabel = new QLabel(tr("Hair interpolation points number: "));
	hairInterpolSlider = new QSlider(Qt::Horizontal, this);
	hairInterpolSlider->setRange(1, 1000);
	connect(hairInterpolSlider, SIGNAL(valueChanged(int)), this, SLOT(hairInterpolChanged()));
	hairInterpolChanged();

	hairColorLabel = new QLabel(tr("Hairs color: "));
	hairColorButton = new QPushButton(tr("Change hair color"));
	connect(hairColorButton, SIGNAL(clicked()), this, SLOT(hairColorChanged()));

    hairsLayout = new QVBoxLayout;
    hairsLayout->addWidget(hairTypeLabel);
    hairsLayout->addWidget(hairTypeComboBox);
    hairsLayout->addWidget(hairNumberLabel);
    hairsLayout->addWidget(hairNumberSlider);
    hairsLayout->addWidget(hairLengthLabel);
	hairsLayout->addWidget(hairLengthSlider);
    hairsLayout->addWidget(hairWidthLabel);
	hairsLayout->addWidget(hairWidthSlider);
    hairsLayout->addWidget(hairParticlesLabel);
	hairsLayout->addWidget(hairParticlesSlider);
    hairsLayout->addWidget(hairInterpolLabel);
	hairsLayout->addWidget(hairInterpolSlider);
    hairsLayout->addWidget(hairColorLabel);
    hairsLayout->addWidget(hairColorButton);
    setLayout(hairsLayout);
}

void HairsTab::hairNumberChanged()
{
	int value = hairNumberSlider->value();
	char* valueString = new char[30];
	std::string text;
	
	itoa(value, valueString, 10);
	text = "Hairs number: ";
	text.append(valueString);

	// TODO set value 
	
	hairNumberLabel->setText(tr(text.c_str()));
}

void HairsTab::hairLengthChanged()
{
	int value = hairLengthSlider->value();
	float hairLength = (float) value / 10;
	char* valueString = new char[30];
	std::string text;
	
	sprintf(valueString, "%.1f", hairLength);
	text = "Hairs length: ";
	text.append(valueString);

	// TODO set value 
	
	hairLengthLabel->setText(tr(text.c_str()));
}

void HairsTab::hairWidthChanged()
{
	int value = hairWidthSlider->value() - 5;
	float hairWidth = 0.5 + value*0.05;
	char* valueString = new char[30];
	std::string text;
	
	sprintf(valueString, "%.2f", hairWidth);
	text = "Hairs width: ";
	text.append(valueString);

	// TODO set value 
	
	hairWidthLabel->setText(tr(text.c_str()));
}

void HairsTab::hairParticlesChanged()
{
	int value = hairParticlesSlider->value();
	char* valueString = new char[30];
	std::string text;
	
	itoa(value, valueString, 10);
	text = "Hair particles number: ";
	text.append(valueString);

	// TODO set value 
	
	hairParticlesLabel->setText(tr(text.c_str()));
}

void HairsTab::hairInterpolChanged()
{
	int value = hairInterpolSlider->value();
	char* valueString = new char[30];
	std::string text;
	
	itoa(value, valueString, 10);
	text = "Hair interpolation points number: ";
	text.append(valueString);

	// TODO set value and maybe save to config
	
	hairInterpolLabel->setText(tr(text.c_str()));
}

void HairsTab::hairColorChanged()
{
	hairColor = QColorDialog::getColor(Qt::yellow, this);
	changeHairColorButton(hairColor);
}

void HairsTab::changeHairColorButton(QColor pNewColor)
{
	colorText = "background-color: ";

    if (pNewColor.isValid()) 
	{
		hairColorButton->setStyleSheet(colorText + pNewColor.name());
    }
}

EnvironmentTab::EnvironmentTab(QWidget *parent) : QWidget(parent)
{
	empty = new QLabel(tr(" "));

	envMultisamplingLabel = new QLabel(tr("Multisampling:"));
	envMultisamplingComboBox = new QComboBox;
	envMultisamplingComboBox->setEditable(false);
	envMultisamplingComboBox->addItem(tr("OFF"));
	envMultisamplingComboBox->addItem(tr("2x"));
	envMultisamplingComboBox->addItem(tr("4x"));
	envMultisamplingComboBox->addItem(tr("8x"));
	envMultisamplingComboBox->addItem(tr("16x"));

	envSimulationShowCheckBox = new QCheckBox;
	envSimulationShowCheckBox->setCheckable(true);
	envSimulationShowCheckBox->setChecked(true); 
	envSimulationShowCheckBox->setText(tr("Show simulation window"));

	envTextCheckBox = new QCheckBox;
	envTextCheckBox->setCheckable(true);
	envTextCheckBox->setChecked(true);
	envTextCheckBox->setText(tr("Show text label"));

	envBgColorLabel = new QLabel(tr("Background color:"));
	envBgColorButton = new QPushButton(tr("Change background color"));
	connect(envBgColorButton, SIGNAL(clicked()), this, SLOT(bgColorChanged()));

	envLayout = new QVBoxLayout;
    envLayout->addWidget(envMultisamplingLabel);
    envLayout->addWidget(envMultisamplingComboBox);
    envLayout->addWidget(envSimulationShowCheckBox);
    envLayout->addWidget(envTextCheckBox);
    envLayout->addWidget(envBgColorLabel);
    envLayout->addWidget(envBgColorButton);
    envLayout->addWidget(empty);
    envLayout->addWidget(empty);
    envLayout->addWidget(empty);
    envLayout->addWidget(empty);
    envLayout->addWidget(empty);
    envLayout->addWidget(empty);
    envLayout->addWidget(empty);
    envLayout->addWidget(empty);
    setLayout(envLayout);
}

void EnvironmentTab::bgColorChanged()
{
	envBgColor = QColorDialog::getColor(Qt::gray, this);
	changeBgColorButton(envBgColor);
}

void EnvironmentTab::changeBgColorButton(QColor pNewColor)
{
	colorText = "background-color: ";

    if (pNewColor.isValid()) 
	{
		envBgColorButton->setStyleSheet(colorText + pNewColor.name());
    }
}

AboutTab::AboutTab(QWidget *parent) : QWidget(parent)
{
    aboutLabel = new QLabel(tr("<center><b>Hair simulation and visualization using GPU</b><br>(Diploma project)<br><br>Author: <b>Bc. Tomas Hurban</b><br>hurbant@gmail.com<br><br>2/2011 - 5/2012<br><br>Slovak University of Technology Bratislava<br>FACULTY OF INFORMATICS AND INFORMATION TECHNOLOGIES"));
    
	aboutLayout = new QVBoxLayout;
    aboutLayout->addWidget(aboutLabel);
    setLayout(aboutLayout);
}

void HairsTab::setValues(Settings* pSettings)
{
	hairTypeComboBox->setCurrentIndex(pSettings->getHairType() - 1);
	hairNumberSlider->setValue(pSettings->getHairsNumber());
	hairLengthSlider->setValue(pSettings->getHairsLength() * 10);
	hairWidthSlider->setValue(((pSettings->getHairsWidth() - 0.5) / 0.05) + 5);
	hairParticlesSlider->setValue(pSettings->getHairParticlesNumber());
	hairInterpolSlider->setValue(pSettings->getHairInterpolationPointsNumber());
	hairColor.setRgb(pSettings->getHairColorR()*255, pSettings->getHairColorG()*255, pSettings->getHairColorB()*255, pSettings->getHairColorA()*255);
	changeHairColorButton(hairColor);
}

void EnvironmentTab::setValues(Settings* pSettings)
{
	if (pSettings->getFormatMultisamplingValue() == 2)
		envMultisamplingComboBox->setCurrentIndex(1);
	else if (pSettings->getFormatMultisamplingValue() == 4)
		envMultisamplingComboBox->setCurrentIndex(2);
	else if (pSettings->getFormatMultisamplingValue() == 8)
		envMultisamplingComboBox->setCurrentIndex(3);
	else if (pSettings->getFormatMultisamplingValue() == 16)
		envMultisamplingComboBox->setCurrentIndex(4);
	else
		envMultisamplingComboBox->setCurrentIndex(0);

	if (pSettings->getFormatMultisamplingEnabled() == true)
		envSimulationShowCheckBox->setChecked(true);
	else
		envSimulationShowCheckBox->setChecked(false);

	if (pSettings->getTextEnabled() == true)
		envTextCheckBox->setChecked(true);
	else
		envTextCheckBox->setChecked(false);

	envBgColor.setRgb(pSettings->getWindowBgColorR()*255, pSettings->getWindowBgColorG()*255, pSettings->getWindowBgColorB()*255, pSettings->getWindowBgColorA()*255);
	changeBgColorButton(envBgColor);
}