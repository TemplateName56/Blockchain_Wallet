#include "settings_form.h"
#include "ui_settings_form.h"
#include "client/tests/program_exception.h"
#include "client/scripts/csv_func.h"
#include "client/scripts/json_func.h"

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
//    QFileInfo file_info("settings.json");
//    QDir::setCurrent(file_info.path());
//    QFile json_file("settings.json");

//    if (!json_file.open(QIODevice::ReadOnly))
//    {+
//        //throw ProgramException(FILE_READ_ERROR); i think this dont need
//    }

//    QJsonDocument json_document(QJsonDocument::fromJson(json_file.readAll()));
//    json_file.close();

//    QJsonObject current_json = json_document.object();

    JSON file("users.json");
    //file.get_language_user("BW000000000000000");
    settings_Form::languageIndex = file.get_language_user("BW000000000000000");
    //qDebug() << "languageIndex: " << settings_Form::languageIndex ;
    //settings_Form::languageIndex = current_json.value("Language").toInt();
}

//void settings_Form::writeSettings()
//{
//    QFileInfo file_info("settings.json");
//    QDir::setCurrent(file_info.path());
//    QFile json_file("settings.json");

//    if (!json_file.open(QIODevice::WriteOnly))
//    {
//        throw ProgramException(FILE_WRITE_ERROR);
//    }

//    QJsonObject current_json;

//    current_json.insert("Language",settings_Form::languageIndex);

//    json_file.write(QJsonDocument(current_json).toJson(QJsonDocument::Indented));
//    json_file.close();
//}

void settings_Form::closeEvent(QCloseEvent *event)
{
    JSON file("users.json");
    //qDebug() << settings_Form::languageIndex;
    file.set_language_user("BW000000000000000",settings_Form::languageIndex);
    //writeSettings();
}

void settings_Form::setWindowLanguage()
{
    CSV file_tr("translation.csv");

     QVector<QString> str = file_tr.get_tr(languageIndex);

     this->setWindowTitle(str.at(0));

     ui->tabWidget->setTabText(0,str.at(1));
     ui->tabWidget->setTabText(1,str.at(2));
     ui->tabWidget->setTabText(2,str.at(3));

     ui->label->setText(str.at(4));
     ui->trayCheckBox->setText(str.at(5));
     ui->languageLabel->setText(str.at(6));
     ui->coinsTypeLabel->setText(str.at(7));

     emit languageChanged(str);
}


void settings_Form::on_defaultCoinsTypeCB_currentIndexChanged(int index)
{
    emit coinsTypeChanged(index);
}

