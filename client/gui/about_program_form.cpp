#include "about_program_form.h"
#include "ui_about_program_form.h"
#include "client/scripts/csv_func.h"
#include "settings_form.h"

about_program_Form::about_program_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::about_program_Form)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("icons/programIcon.png"));
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

}

about_program_Form::~about_program_Form()
{
    delete ui;
}

void about_program_Form::aboutShow()
{
    this->show();

    //QTextEdit{"background-color: transparent"};
   // QTextEdit{" border:0px solid black; "};

    // ui->textEdit->setStyleSheet("QTextEdit { background-color:  QPalette::Base }");

    //ничего не меняется, нужно фон прозрачный


}

void about_program_Form::setWindowLanguage(int index)
{
    switch (index) {

    case ENGLISH:

        ui->textEdit_abot_program->setText("<html><head/><body><p>При запуске программы Вам высвечивается уведомление, которое оповещает Вас о текущем пароле. Этот пароль в дальнейшем Вам придётся вводить при каждом запуске программы, "
                                           "чтобы Вы его не забыли с течением времени, иначе мы не сможем восстановить Ваш кошелёк.</p><p><br/></p><p>На главном меню во вкладке &quot;<span style=\" text-decoration: underline;\">Обзор</span>&quot; "
                                           "Вы можете отследить Ваш баланс в трёх валютах. Под балансом Вы можете увидеть свой текущий адрес и пароль, который Вы можете скопировать, но ни в коем случае не передавайте его третьим лицам. "
                                           "Справа от баланса Вы сможете проследить Ваши последние четыре транзакции с полной информацией о сделке.</p><p><br/></p><p>Во вкладке &quot;<span style=\" text-decoration: underline;\">Отправить</span>&quot; "
                                           "Вам нужно ввести адрес кошелька пользователя, на который Вы хотите отправить определённую сумму с выбором валюты (адрес вы можете найти во вкладке &quot;<span style=\" text-decoration: underline;\">Обзор</span>&quot;). "
                                           "Не обязательным условием является сообщение для этого пользователя. Вы можете ввести своё значение суммы для комиссии, это будет влиять на скорость обработки Вашего платежа.</p><p><br/></p><p>...</p><p><br/></p><p>"
                                           "Во вкладке все транзакции Вы можете видеть все транзакции, которые Вы совершили за весь период работы кошелька.</p><p><br/></p><p>Эта справка создана для ознакомления с программой <span style=\" font-style:italic;\">BlockChain Wallet"
                                           "</span>, если у вас есть какие-то вопросы, ответы на которые вы не нашли в этой справке, или предложения, напишите нам на почту: <span style=\" font-weight:600;\">blockchainwallet@gmail.com</span></p><p><br/></p></body></html>");

        this->setWindowTitle("About the program");

        break;

    case UKRANIAN:

        ui->textEdit_abot_program->setText("<html><head/><body><p>При запуску програми вам висвічується повідомлення, яке сповіщає Вас про поточний пароль. Цей пароль надалі Вам доведеться вводити при кожному запуску програми, щоб ви його не забули з плином часу, інакше ми не зможемо відновити ваш гаманець.</p><p><br/></p><p>На головному меню у вкладці &quot;<span style=\" text-decoration: underline;\">Огляд</span>&quot; ви можете відстежити ваш баланс в трьох валютах. Під балансом ви можете побачити свою поточну адресу та пароль, який ви можете скопіювати, але ні в якому разі не передавайте його третім особам. Праворуч від балансу Ви зможете простежити ваші останні чотири транзакції з повною інформацією про угоду.</p><p><br/></p><p>У вкладці &quot;<span style=\" text-decoration: underline;\">Відправити</span>&quot; Вам потрібно ввести адресу гаманця користувача, на який ви хочете відправити певну суму з вибором валюти (адресу ви можете знайти у вкладці &quot;<span style=\" text-decoration: underline;\">Огляд</span>&quot;). Не обов'язковою умовою є повідомлення для цього користувача. Ви можете ввести своє значення суми для комісії, це буде впливати на швидкість обробки вашого платежу.</p><p><br/></p><p>...</p><p><br/></p><p>У вкладці всі транзакції ви можете бачити всі транзакції, які ви зробили за весь період роботи гаманця.</p><p><br/></p><p>Ця довідка створена для ознайомлення з програмою <span style=\" font-style:italic;\">BlockChain Wallet</span>, якщо у вас є якісь питання, відповіді на які ви не знайшли в цій довідці, або пропозиції, напишіть нам на пошту: <span style=\" font-weight:600;\">blockchainwallet@gmail.com</span></p></body></html>");
        this->setWindowTitle("Про програму");

        break;

    case RUSSIAN:

        ui->textEdit_abot_program->setText("<html><head/><body><p>When you start the program, you will receive a notification that informs you of your current password. You will have to enter this password every time you start the program in the future so that you don't forget it over time, otherwise we won't be able to restore your wallet.</p><p><br/></p><p>On the &quot;<span style=\" text-decoration: underline;\">Overview</span>&quot; tab of the main menu, you can track your balance in three currencies. Under the balance you can see your current address and password, which you can copy, but under no circumstances give it to a third party. To the right of the balance you can track your last four transactions with complete transaction information.</p><p><br/></p><p>In the &quot;<span style=\" text-decoration: underline;\">Send</span>&quot; tab, you need to enter the address of the user's wallet to which you want to send a certain amount with a choice of currency (you can find the address in the &quot;Overview&quot; tab). It is not obligatory to send a message for this user. You can enter your own value for the commission amount, it will affect the speed of processing your payment.</p><p><br/></p><p>...</p><p><br/></p><p>In the tab &quot;<span style=\" text-decoration: underline;\">All Transactions</span>&quot; you can see all the transactions you have made during the whole period of your wallet's work.</p><p><br/></p><p>This help is created for acquaintance with the program <span style=\" font-style:italic;\">BlockChain Wallet</span>, if you have any questions, the answers to which you have not found in this help, or suggestions, write to us by e-mail: <span style=\" font-weight:600;\">blockchainwallet@gmail.com</span></p></body></html>");
        this->setWindowTitle("О программе");

        break;
    }
}
