#include "settings_form.h"
#include "ui_settings_form.h"
#include "client/tests/program_exception.h"

settings_Form::settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings_Form)
{
    ui->setupUi(this);
    this->setWindowTitle("Settings");
    ui->tabWidget->setCurrentIndex(0);

    readSettings();
    ui->languagesBox->setCurrentIndex(languageIndex);
    setWindowLanguage();


    connect(this, SIGNAL(languageChanged()), this, SLOT(setWindowLanguage()));
}

settings_Form::~settings_Form()
{
    delete ui;
}

void settings_Form::settingsShow()
{
    this->show();
}

void settings_Form::on_languagesBox_currentIndexChanged(int index)
{
    settings_Form::languageIndex = index;
    emit languageChanged();
}

bool settings_Form::minimizeInTray()
{
    return ui->trayCheckBox->isChecked();
}

void settings_Form::on_trayCheckBox_toggled(bool checked)
{
    emit trayCheckBoxToggled();
}

void settings_Form::readSettings()
{
    QFileInfo file_info("settings.json");
    QDir::setCurrent(file_info.path());
    QFile json_file("settings.json");

    if (!json_file.open(QIODevice::ReadOnly))
    {
        throw ProgramException(FILE_READ_ERROR);
    }

    QJsonDocument json_document(QJsonDocument::fromJson(json_file.readAll()));
    json_file.close();

    QJsonObject current_json = json_document.object();

    settings_Form::languageIndex = current_json.value("Language").toInt();
}

void settings_Form::writeSettings()
{
    QFileInfo file_info("settings.json");
    QDir::setCurrent(file_info.path());
    QFile json_file("settings.json");

    if (!json_file.open(QIODevice::WriteOnly))
    {
        throw ProgramException(FILE_WRITE_ERROR);
    }

    QJsonObject current_json;

    current_json.insert("Language",settings_Form::languageIndex);

    json_file.write(QJsonDocument(current_json).toJson(QJsonDocument::Indented));
    json_file.close();
}

void settings_Form::closeEvent(QCloseEvent *event)
{
    writeSettings();
}
void settings_Form::setWindowLanguage()
{
    switch (languageIndex) {
    case ENGLISH:
        this->setWindowTitle("Settings");

        ui->tabWidget->setTabText(0,"&Main");
        ui->tabWidget->setTabText(1,"&Wallet");
        ui->tabWidget->setTabText(2,"&Window");
        ui->tabWidget->setTabText(3,"&Display");

        ui->trayCheckBox->setText("&When you click the \"Close \" button, minimize the window to tray");
        ui->languageLabel->setText("User interface language");

        break;
    case UKRANIAN:
        this->setWindowTitle("Налаштування");

        ui->tabWidget->setTabText(0,"&Головне");
        ui->tabWidget->setTabText(1,"&Гаманець");
        ui->tabWidget->setTabText(2,"&Вікно");
        ui->tabWidget->setTabText(3,"&Відображення");

        ui->trayCheckBox->setText("&При натисканні кнопки \"Закрити\" згортати вікно в трей");
        ui->languageLabel->setText("Мова інтерфейсу");

        break;
    case RUSSIAN:
        this->setWindowTitle("Настройки");

        ui->tabWidget->setTabText(0,"&Главное");
        ui->tabWidget->setTabText(1,"&Кошелёк");
        ui->tabWidget->setTabText(2,"&Окно");
        ui->tabWidget->setTabText(3,"&Отображение");

        ui->trayCheckBox->setText("&При нажатии кнопки \"Закрыть\" сворачивать окно в трей");
        ui->languageLabel->setText("Язык интерфейса");

        break;
    }
}

