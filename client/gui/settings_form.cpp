#include "settings_form.h"
#include "ui_settings_form.h"

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


    //file.get_language_user("BW000000000000000");
     //вместо BW000000000000001 нужен адрес текущего пользователя
    //qDebug() << "languageIndex: " << settings_Form::languageIndex ;
    //settings_Form::languageIndex = current_json.value("Language").toInt();
    try {
        JSON file("users.json");
        languageIndex = 1;
    }  catch (ProgramException &error) {
        error.getError();
    }
}

void settings_Form::closeEvent(QCloseEvent *event)
{
    try {
        JSON file("users.json");
        file.set_language_user(this->current_user->getAddress(), settings_Form::languageIndex);  //вместо BW000000000000001 нужен адрес текущего пользователя
    }  catch (ProgramException &error) {
        error.getError();
    }

}

void settings_Form::setWindowLanguage()
{
    try {
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

        emit languageChanged(str, languageIndex);
    }  catch (ProgramException &error) {
        error.getError();
    }
}


void settings_Form::on_defaultCoinsTypeCB_currentIndexChanged(int index)
{
    emit coinsTypeChanged(index);
}

void settings_Form::loadSettings(User &current_user)
{
    this->current_user = &current_user;
    try {
        JSON file("users.json");
        ui->languagesBox->setCurrentIndex(file.get_language_user(this->current_user->getAddress()));
    }  catch (ProgramException &error) {
        error.getError();
    }
}
