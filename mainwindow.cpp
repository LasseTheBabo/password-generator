#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(338, 104);

    // Wert vom Slider in SpinBox (Initialisierung
    ui->pLenSpinBox->setValue(ui->pLenSlider->value());

    // Slider und SpinBox syncronisieren
    connect(ui->pLenSlider, &QSlider::valueChanged, ui->pLenSpinBox, &QSpinBox::setValue);
    connect(ui->pLenSpinBox, &QSpinBox::valueChanged, ui->pLenSlider, &QSlider::setValue);

    // Passwort bei Wertänderung neu generieren
    connect(ui->upperCaseCheckBox, &QCheckBox::toggled, this, &MainWindow::generatePassword);
    connect(ui->lowerCaseCheckBox, &QCheckBox::toggled, this, &MainWindow::generatePassword);
    connect(ui->numberCheckBox, &QCheckBox::toggled, this, &MainWindow::generatePassword);
    connect(ui->specialCheckBox, &QCheckBox::toggled, this, &MainWindow::generatePassword);
    connect(ui->regeneratePassword, &QPushButton::pressed, this, &MainWindow::generatePassword);
    connect(ui->pLenSlider, &QSlider::valueChanged, this, &MainWindow::generatePassword);
    connect(ui->pLenSpinBox, &QSpinBox::valueChanged, this, &MainWindow::generatePassword);

    // UpperCase und LowerCase als standart
    ui->upperCaseCheckBox->setChecked(true);
    ui->lowerCaseCheckBox->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generatePassword()
{
    bool upperCaseChecked = ui->upperCaseCheckBox->isChecked();
    bool lowerCaseChecked = ui->lowerCaseCheckBox->isChecked();
    bool numberChecked = ui->numberCheckBox->isChecked();
    bool specialChecked = ui->specialCheckBox->isChecked();

    int pLength = ui->pLenSlider->value();
    QString chars;
    QString password;

    if (upperCaseChecked) chars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (lowerCaseChecked) chars += "abcdefghijklmnopqrstuvwxyz";
    if (numberChecked) chars += "0123456789";
    if (specialChecked) chars += "!@#$%^&*()_+-=[]{}";

    // Überprüfen ob eine Zeichenart ausgewählt wurde
    if (!chars.isEmpty())
    {
        // Passwort Generieren
        for (int i = 0; i < pLength; i++)
        {
            int index = QRandomGenerator::global()->bounded(chars.length());
            password += chars.at(index);
        }
    }

    ui->pOutput->setText(password);
}
