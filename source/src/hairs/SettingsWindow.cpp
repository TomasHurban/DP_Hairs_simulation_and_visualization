#include "SettingsWindow.hpp"

Settings** settings;

SettingsWindow::SettingsWindow(Settings** pSettings, bool* pChange, QWidget* parent) : QDialog(parent)
{
	settings = pSettings;
	change = pChange;

	controlTab = new ControlTab();
	hairsTab = new HairsTab();
	environmentTab = new EnvironmentTab();
	aboutTab = new AboutTab();

    tabWidget = new QTabWidget;
    tabWidget->addTab(controlTab, tr("Controls"));
    tabWidget->addTab(hairsTab, tr("Hairs"));
    tabWidget->addTab(environmentTab, tr("Environment and physics"));
    tabWidget->addTab(aboutTab, tr("About"));

	applyButton = new QPushButton("&Apply", this);
	connect(applyButton, SIGNAL(clicked()), this, SLOT(applyWindow()));

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(applyButton);
    setLayout(mainLayout);

    setWindowTitle(tr("Menu"));

	hairsTab->setValues();
	environmentTab->setValues();
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

	hairLengthLabel = new QLabel(tr("Hairs length: "));
	hairLengthSlider = new QSlider(Qt::Horizontal, this);
	hairLengthSlider->setRange(1, 100);
	connect(hairLengthSlider, SIGNAL(valueChanged(int)), this, SLOT(hairLengthChanged()));

	hairWidthLabel = new QLabel(tr("Hairs width: "));
	hairWidthSlider = new QSlider(Qt::Horizontal, this);
	hairWidthSlider->setRange(1, 20);
	connect(hairWidthSlider, SIGNAL(valueChanged(int)), this, SLOT(hairWidthChanged()));

	hairParticlesLabel = new QLabel(tr("Hair particles number: "));
	hairParticlesSlider = new QSlider(Qt::Horizontal, this);
	hairParticlesSlider->setRange(1, 50);
	connect(hairParticlesSlider, SIGNAL(valueChanged(int)), this, SLOT(hairParticlesChanged()));

	hairInterpolLabel = new QLabel(tr("Hair interpolation points number: "));
	hairInterpolSlider = new QSlider(Qt::Horizontal, this);
	hairInterpolSlider->setRange(1, 1000);
	connect(hairInterpolSlider, SIGNAL(valueChanged(int)), this, SLOT(hairInterpolChanged()));

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

	change = false;
}

void HairsTab::hairNumberChanged()
{
	int value = hairNumberSlider->value();
	char* valueString = new char[30];
	std::string text;
	
	itoa(value, valueString, 10);
	text = "Hairs number: ";
	text.append(valueString);

	(*settings)->setHairsNumber(value);
	change = true;
	
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

	(*settings)->setHairsLength(hairLength);
	change = true;
	
	hairLengthLabel->setText(tr(text.c_str()));
}

void HairsTab::hairWidthChanged()
{
	int value = hairWidthSlider->value(); 
	float hairWidth = (float) value / 1000;
	char* valueString = new char[30];
	std::string text;
	
	sprintf(valueString, "%.3f", hairWidth);
	text = "Hairs width: ";
	text.append(valueString);

	(*settings)->setHairsWidth(hairWidth);
	change = true;
	
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

	(*settings)->setHairParticlesNumber(value);
	change = true;
	
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

	(*settings)->setHairInterpolationPointsNumber(value);
	change = true;
	
	hairInterpolLabel->setText(tr(text.c_str()));
}

void HairsTab::hairColorChanged()
{
	hairColor = QColorDialog::getColor(Qt::yellow, this);
	changeHairColorButton(hairColor);

	// TODO set color - (*settings)->setHairColorR(hairColor);
	change = true;
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

	sizeCoefLabel = new QLabel(tr("Simulation objects size coefficient: "));
	sizeCoefSlider = new QSlider(Qt::Horizontal, this);
	sizeCoefSlider->setRange(1, 10);
	connect(sizeCoefSlider, SIGNAL(valueChanged(int)), this, SLOT(sizeCoefChanged()));

	controlPointRadiusLabel = new QLabel(tr("Control points radius: "));
	controlPointRadiusSlider = new QSlider(Qt::Horizontal, this);
	controlPointRadiusSlider->setRange(1, 20);
	connect(controlPointRadiusSlider, SIGNAL(valueChanged(int)), this, SLOT(controlPointRadiusChanged()));

	controlPointMassLabel = new QLabel(tr("Control points mass: "));
	controlPointMassSlider = new QSlider(Qt::Horizontal, this);
	controlPointMassSlider->setRange(1, 10);
	connect(controlPointMassSlider, SIGNAL(valueChanged(int)), this, SLOT(controlPointMassChanged()));

	hairMassLabel = new QLabel(tr("Hairs mass: "));
	hairMassSlider = new QSlider(Qt::Horizontal, this);
	hairMassSlider->setRange(1, 10);
	connect(hairMassSlider, SIGNAL(valueChanged(int)), this, SLOT(hairMassChanged()));

	envBgColorLabel = new QLabel(tr("Background color:"));
	envBgColorButton = new QPushButton(tr("Change background color"));
	connect(envBgColorButton, SIGNAL(clicked()), this, SLOT(bgColorChanged()));

	envLayout = new QVBoxLayout;
    envLayout->addWidget(envMultisamplingLabel);
    envLayout->addWidget(envMultisamplingComboBox);
    envLayout->addWidget(envSimulationShowCheckBox);
    envLayout->addWidget(envTextCheckBox);
    envLayout->addWidget(sizeCoefLabel);
    envLayout->addWidget(sizeCoefSlider);
    envLayout->addWidget(controlPointRadiusLabel);
    envLayout->addWidget(controlPointRadiusSlider);
    envLayout->addWidget(controlPointMassLabel);
    envLayout->addWidget(controlPointMassSlider);
    envLayout->addWidget(hairMassLabel);
    envLayout->addWidget(hairMassSlider);
    envLayout->addWidget(envBgColorLabel);
    envLayout->addWidget(envBgColorButton);
    setLayout(envLayout);

	change = false;
}

void EnvironmentTab::sizeCoefChanged()
{
	int value = sizeCoefSlider->value();
	char* valueString = new char[30];
	std::string text;
	
	itoa(value, valueString, 10);
	text = "Simulation objects size coefficient: ";
	text.append(valueString);

	(*settings)->setSimulationSizeCoef(value);
	change = true;
	
	sizeCoefLabel->setText(tr(text.c_str()));
}

void EnvironmentTab::controlPointRadiusChanged()
{
	int value = controlPointRadiusSlider->value();
	float controlPointRadius = (float) value / 10;
	char* valueString = new char[30];
	std::string text;
	
	sprintf(valueString, "%.1f", controlPointRadius);
	text = "Control points radius: ";
	text.append(valueString);

	(*settings)->setSimulationControlPointRadius(controlPointRadius);
	change = true;
	
	controlPointRadiusLabel->setText(tr(text.c_str()));
}

void EnvironmentTab::controlPointMassChanged()
{
	int value = controlPointMassSlider->value();
	float controlPointMass = (float) value / 10;
	char* valueString = new char[30];
	std::string text;
	
	sprintf(valueString, "%.1f", controlPointMass);
	text = "Control points mass: ";
	text.append(valueString);

	(*settings)->setSimulationControlPointMass(controlPointMass);
	change = true;
	
	controlPointMassLabel->setText(tr(text.c_str()));
}

void EnvironmentTab::hairMassChanged()
{
	int value = hairMassSlider->value();
	float hairMass = (float) value / 10;
	char* valueString = new char[30];
	std::string text;
	
	sprintf(valueString, "%.1f", hairMass);
	text = "Hairs mass: ";
	text.append(valueString);

	(*settings)->setSimulationControlPointMass(hairMass);
	change = true;
	
	hairMassLabel->setText(tr(text.c_str()));
}

void EnvironmentTab::bgColorChanged()
{
	envBgColor = QColorDialog::getColor(Qt::gray, this);
	changeBgColorButton(envBgColor);

	// TODO set color
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

void HairsTab::setValues()
{
	hairTypeComboBox->setCurrentIndex((*settings)->getHairType() - 1);
	hairNumberSlider->setValue((*settings)->getHairsNumber());
	hairLengthSlider->setValue((*settings)->getHairsLength() * 10);
	hairWidthSlider->setValue((*settings)->getHairsWidth() * 1000 + 1);
	hairParticlesSlider->setValue((*settings)->getHairParticlesNumber());
	hairInterpolSlider->setValue((*settings)->getHairInterpolationPointsNumber());
	hairColor.setRgb((*settings)->getHairColorR()*255, (*settings)->getHairColorG()*255, (*settings)->getHairColorB()*255, (*settings)->getHairColorA()*255);
	changeHairColorButton(hairColor);
}

void EnvironmentTab::setValues()
{
	if ((*settings)->getFormatMultisamplingValue() == 2)
		envMultisamplingComboBox->setCurrentIndex(1);
	else if ((*settings)->getFormatMultisamplingValue() == 4)
		envMultisamplingComboBox->setCurrentIndex(2);
	else if ((*settings)->getFormatMultisamplingValue() == 8)
		envMultisamplingComboBox->setCurrentIndex(3);
	else if ((*settings)->getFormatMultisamplingValue() == 16)
		envMultisamplingComboBox->setCurrentIndex(4);
	else
		envMultisamplingComboBox->setCurrentIndex(0);

	if ((*settings)->getFormatMultisamplingEnabled() == true)
		envSimulationShowCheckBox->setChecked(true);
	else
		envSimulationShowCheckBox->setChecked(false);

	if ((*settings)->getTextEnabled() == true)
		envTextCheckBox->setChecked(true);
	else
		envTextCheckBox->setChecked(false);

	sizeCoefSlider->setValue((*settings)->getSimulationSizeCoef());
	controlPointRadiusSlider->setValue((*settings)->getSimulationControlPointRadius() * 10);
	controlPointMassSlider->setValue((*settings)->getSimulationControlPointMass() * 10);
	hairMassSlider->setValue((*settings)->getSimulationHairMass() * 10);

	envBgColor.setRgb((*settings)->getWindowBgColorR()*255, (*settings)->getWindowBgColorG()*255, (*settings)->getWindowBgColorB()*255, (*settings)->getWindowBgColorA()*255);
	changeBgColorButton(envBgColor);
}

void SettingsWindow::applyWindow()
{
	if (hairsTab->change == true || environmentTab->change == true)
	{
		*change = true;

		hairsTab->change = false;
		environmentTab->change = false;
	}

	this->hide();
}