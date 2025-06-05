#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(330, 104);

    // Initialize: set SpinBox value to match the Slider
    ui->pLenSpinBox->setValue(ui->pLenSlider->value());

    // Synchronize Slider and SpinBox
    connect(ui->pLenSlider, &QSlider::valueChanged, ui->pLenSpinBox, &QSpinBox::setValue);
    connect(ui->pLenSpinBox, &QSpinBox::valueChanged, ui->pLenSlider, &QSlider::setValue);

    // Regenerate passwor if any value changes
    connect(ui->upperCaseCheckBox, &QCheckBox::toggled, this, &MainWindow::generatePassword);
    connect(ui->lowerCaseCheckBox, &QCheckBox::toggled, this, &MainWindow::generatePassword);
    connect(ui->numberCheckBox, &QCheckBox::toggled, this, &MainWindow::generatePassword);
    connect(ui->specialCheckBox, &QCheckBox::toggled, this, &MainWindow::generatePassword);
    connect(ui->regeneratePassword, &QPushButton::pressed, this, &MainWindow::generatePassword);
    connect(ui->pLenSlider, &QSlider::valueChanged, this, &MainWindow::generatePassword);
    connect(ui->pLenSpinBox, &QSpinBox::valueChanged, this, &MainWindow::generatePassword);

    // Set uppercase and lowercase options as default
    ui->upperCaseCheckBox->setChecked(true);
    ui->lowerCaseCheckBox->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generatePassword()
{
    // Get selected options from checkboxes
    bool upperCaseChecked = ui->upperCaseCheckBox->isChecked();
    bool lowerCaseChecked = ui->lowerCaseCheckBox->isChecked();
    bool numberChecked = ui->numberCheckBox->isChecked();
    bool specialChecked = ui->specialCheckBox->isChecked();

    int pLength = ui->pLenSlider->value();
    QString chars; // All possible characters for the password
    QString password; // The generated password

    // Build the character set based on user selection
    if (upperCaseChecked) chars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (lowerCaseChecked) chars += "abcdefghijklmnopqrstuvwxyz";
    if (numberChecked) chars += "0123456789";
    if (specialChecked) chars += "!@#$%^&*()_+-=[]{}";

    // Check if any character type is selected
    if (!chars.isEmpty())
    {
        // Generate a random password using the selected character set
        for (int i = 0; i < pLength; i++)
        {
            int index = QRandomGenerator::global()->bounded(chars.length());
            password += chars.at(index);
        }
    }

    ui->pOutput->setText(password); // Display the generated password
}
