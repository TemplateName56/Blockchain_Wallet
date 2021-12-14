#include "about_of_authors.h"
#include "ui_about_of_authors.h"

about_of_authors::about_of_authors(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::about_of_authors)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("icons/programIcon.png"));
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

about_of_authors::~about_of_authors()
{
    delete ui;
}

void about_of_authors::aboutAuth()
{
    this->show();

    //QTextEdit{"background-color: transparent"};
   // QTextEdit{" border:0px solid black; "};

    // ui->textEdit->setStyleSheet("QTextEdit { background-color:  QPalette::Base }");

    //ничего не меняется, нужно фон прозрачный
}

void about_of_authors::setWindowLanguage(int index)
{
    switch (index) {

       //case ENGLISH:

    //ui->textEdit_about_of_authors->setText("<html><head/><body><p><span style=\" font-style:italic;\">BlockChain Wallet</span> was created by a group of four students who are currently studying at <span style=\" font-style:italic;\">Zaporizhzhya Polytechnic National University</span>. </p><p><br/></p><p>The ideological inspirer was <span style=\" font-weight:600;\">Nikita Khalizev</span>, the work on the software functionality was done by <span style=\" font-weight:600;\">Daniil Potapov</span>, the interaction between the files and the program was organized by <span style=\" font-weight:600;\">Evgeny Latyshev</span>, and the visual component was responsible for <span style=\" font-weight:600;\">Azmanov Ilya</span>.</p><p><br/></p><p><span style=\" font-style:italic;\">The goal of BlockChain Wallet</span> is to popularize the use of electronic wallets among <span style=\" font-style:italic;\">NUZP</span> students.</p><p><br/></p><p><br/></p></body></html>");

           // break;

    //    case UKRANIAN:

   //ui->textEdit_about_of_authors->setText("<html><head/><body><p><span style=\" font-style:italic;\">BlockChain Wallet</span> був створений групою з чотирьох студентів, які на даний момент навчаються в <span style=\" text-decoration: underline;\">Національному університеті &quot;Запорізька політехніка&quot;</span>. </p><p><br/></p><p>Ідейним натхненником виступав <span style=\" font-weight:600;\">Микита Хализев</span>, роботою над функціоналом ПЗ займався <span style=\" font-weight:600;\">Данило Потапов</span>, взаємодії між файлами і програмою організовував <span style=\" font-weight:600;\">Євген Латишев</span>, за візуальну складову відповідав <span style=\" font-weight:600;\">Азманов Ілля</span>.</p><p><br/></p><p><span style=\" font-style:italic;\">Мета BlockChain Wallet</span> полягає в тому, популяризувати використання електронних гаманців серед студентів <span style=\" text-decoration: underline;\">НУЗП</span>.</p></body></html>");

             //        break;

    //    case RUSSIAN:
    //
    // ui->textEdit_about_of_authors->setText("<html><head/><body><p><span style=\" font-style:italic;\">BlockChain Wallet</span> был создан группой из четверых студентов, которые на данный момент учатся в <span style=\" text-decoration: underline;\">Национальном университете &quot;Запорожская Политехника&quot;</span>. </p><p><br/></p><p>Идейным вдохновителем выступал <span style=\" font-weight:600;\">Никита Хализев</span>, работой над функционалом ПО занимался <span style=\" font-weight:600;\">Даниил Потапов</span>, взаимодействия между файлами и программой организовывал <span style=\" font-weight:600;\">Евгений Латышев</span>, за визуальную составляющую отвечал<span style=\" font-weight:600;\"> Азманов Илья</span>.</p><p><br/></p><p><span style=\" font-style:italic;\">Цель BlockChain Wallet</span> состоит в том, популяризировать использование электронных кошельков среди студентов <span style=\" text-decoration: underline;\">НУЗП</span>.</p></body></html>");

    //        break;
        }
}
