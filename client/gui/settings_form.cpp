#include "settings_form.h"
#include "ui_settings_form.h"
#include "client/tests/program_exception.h"
#include "client/scripts/csv_func.h"

settings_Form::settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings_Form)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    this->setWindowIcon(QIcon("icons/programIcon.png"));

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

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
    emit setWindowLanguage();
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
        //throw ProgramException(FILE_READ_ERROR); i think this dont need
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
    CSV file_tr("translation.csv");
    QVector<QString> str_en = file_tr.get_tr(CSV::English);
    QVector<QString> str_ua = file_tr.get_tr(CSV::Ukrainian);
    QVector<QString> str_ru = file_tr.get_tr(CSV::Russian);


     QVector<QString> str = file_tr.get_tr(languageIndex);
     this->setWindowTitle(str.at(0));
     ui->tabWidget->setTabText(0,str.at(1));
     ui->tabWidget->setTabText(1,str.at(2));
     ui->tabWidget->setTabText(2,str.at(3));
     ui->tabWidget->setTabText(3,str.at(4));
     ui->trayCheckBox->setText("&При натисканні кнопки \"Закрити\" згортати вікно в трей");
     ui->languageLabel->setText("Мова інтерфейсу");

     emit languageChanged(str);

//    switch (languageIndex) {
//    case ENGLISH:

//        //this->setWindowTitle("Settings");
//        //this->setWindowTitle(file_tr.get_tr(0, 0));
//        this->setWindowTitle(str_en.at(0));

//        //ui->tabWidget->setTabText(0,"&Main");
//        ui->tabWidget->setTabText(0,str_en.at(1));
//        //ui->tabWidget->setTabText(1,"&Wallet");
//        ui->tabWidget->setTabText(1,str_en.at(2));
//        //ui->tabWidget->setTabText(2,"&Window");
//         ui->tabWidget->setTabText(2,str_en.at(3));
//        //ui->tabWidget->setTabText(3,"&Display");
//        ui->tabWidget->setTabText(3,str_en.at(4));

//        ui->trayCheckBox->setText("&При натисканні кнопки \"Закрити\" згортати вікно в трей");
//        ui->languageLabel->setText("Мова інтерфейсу");

//        break;
//    case UKRANIAN:

//        //this->setWindowTitle("Налаштування");
//        //this->setWindowTitle(file_tr.get_tr(0, 1));
//        this->setWindowTitle(str_ua.at(0));

//        //ui->tabWidget->setTabText(0,"&Головне");
//        ui->tabWidget->setTabText(0,str_ua.at(1));
//        //ui->tabWidget->setTabText(1,"&Гаманець");
//        ui->tabWidget->setTabText(1,str_ua.at(2));
//        //ui->tabWidget->setTabText(2,"&Вікно");
//        ui->tabWidget->setTabText(2,str_ua.at(3));
//        //ui->tabWidget->setTabText(3,"&Відображення");
//        ui->tabWidget->setTabText(3,str_ua.at(4));

//        ui->trayCheckBox->setText("&При натисканні кнопки \"Закрити\" згортати вікно в трей");
//        ui->languageLabel->setText("Мова інтерфейсу");

//        break;
//    case RUSSIAN:
//        //this->setWindowTitle("Настройки");
//        //this->setWindowTitle(file_tr.get_tr(0, 2));
//        this->setWindowTitle(str_ru.at(0));

//        //ui->tabWidget->setTabText(0,"&Главное");
//        ui->tabWidget->setTabText(0,str_ru.at(1));
//        //ui->tabWidget->setTabText(1,"&Кошелёк");
//        ui->tabWidget->setTabText(1,str_ru.at(2));
//        //ui->tabWidget->setTabText(2,"&Окно");
//        ui->tabWidget->setTabText(2,str_ru.at(3));
//        //ui->tabWidget->setTabText(3,"&Отображение");
//        ui->tabWidget->setTabText(3,str_ru.at(4));

//        ui->trayCheckBox->setText("&При нажатии кнопки \"Закрыть\" сворачивать окно в трей");
//        ui->languageLabel->setText("Язык интерфейса");

//        break;
//    }
}


void settings_Form::on_defaultCoinsTypeCB_currentIndexChanged(int index)
{
    emit coinsTypeChanged(index);
}

