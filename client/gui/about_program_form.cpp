#include "about_program_form.h"
#include "ui_about_program_form.h"

#include "settings_form.h"

#include "client/scripts/csv_func.h"

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
}

void about_program_Form::setWindowLanguage(int index)
{
    switch (index) {
    case ENGLISH:

        ui->textEdit_abot_program->setText("<html><head/><body>When you <span style=\" font-weight:600;\">start the program</span>, you will see a login form asking you to enter your personal key or register as a new user. </p><br/></p>When you log in to your account, you will be notified of your current password. You will have to enter this password every time you start the program in the future so that you do not forget it over time, otherwise we will not be able to restore your wallet.</p><br/></p>On the <span style=\" font-weight:600;\">&quot;Overview&quot;</span> tab of the main menu, you can track your <span style=\" font-style:italic;\">balance</span> in <span style=\" font-style:italic;\">three currencies</span>. Under the balance you can see your current <span style=\" font-style:italic;\">address</span> and <span style=\" font-style:italic;\">password</span>, which you can copy, but under no circumstances give it to a third party. To the right of the balance you can track your last four transactions with complete transaction information.</p><br/></p>In the <span style=\" font-weight:600;\">&quot;Send&quot;</span> tab, you need to enter the address of the user's wallet to which you want to send a certain amount with the choice of currency (the address is in the &quot;Overview&quot; tab). It is not obligatory to send a message for this user. You can enter your own value for the commission, which will affect the speed of processing your payment. Also, you can insert a link of another user who has requested money from you, for this there is an appropriate checkbox in front of the input field for the link. When the link is inserted, the data will automatically fill in for you and you will only need to select the commission value.</p><br/></p>In the tab<span style=\" font-weight:600;\"> &quot;Receive&quot;</span> you can enter a message and set the desired amount of money, after which the button will generate a link (request), which you can pass to another user (by copying it) to make a transfer to your purse. Under the interaction buttons you can see a table of your requests that you have made over time.</p><br/></p>Under the tab <span style=\" font-weight:600;\">&quot;All transactions&quot;</span> you can see all the transactions you have made during the whole period of your wallet's work.</p><br/></p>This help is created to familiarize you with the program <span style=\" text-decoration: underline;\">BlockChain Wallet</span>, if you have any questions, the answers to which you have not found in this help, or suggestions, write us an email: <span style=\" font-weight:600;\">blockchainwallet@gmail.com</span></p></body></html>");
        this->setWindowTitle("About the program");

        break;
    case UKRANIAN:

        ui->textEdit_abot_program->setText("<html><head/><body>При<span style=\" font-weight:600;\"> запуску програми</span> вам висвічується форма авторизації, в який вас просять ввести свій особистий ключ або ж зареєструватися як новий користувач. </p><br/></p>При вході в ваш <span style=\" font-weight:600;\">Особистий кабінет</span> вам висвічується повідомлення, яке сповіщає Вас про поточний пароль. Цей пароль надалі Вам доведеться вводити при кожному запуску програми, щоб ви його не забули з плином часу, інакше ми не зможемо відновити ваш гаманець.</p><br/></p>На головному меню у вкладці<span style=\" font-weight:600;\"> &quot;Огляд&quot;</span> ви можете відстежити ваш <span style=\" font-style:italic;\">баланс</span> у<span style=\" font-style:italic;\"> трьох валютах</span>. Під балансом ви можете побачити свою поточну <span style=\" font-style:italic;\">адресу</span> та <span style=\" font-style:italic;\">пароль</span>, який ви можете скопіювати, але ні в якому разі не передавайте його третім особам. Праворуч від балансу Ви зможете простежити ваші останні чотири транзакції з повною інформацією про угоду.</p><br/></p>У вкладці <span style=\" font-weight:600;\">&quot;Відправити&quot;</span> Вам потрібно ввести адресу гаманця користувача, на який ви хочете відправити певну суму з вибором валюти (адреса знаходиться у вкладці <span style=\" font-weight:600;\">&quot;Огляд&quot;</span>). Не обов'язковою умовою є повідомлення для цього користувача. Ви можете ввести своє значення суми для комісії, яке буде впливати на швидкість обробки вашого платежу. Так само ви можете вставити посилання іншого користувача, який запросив у Вас гроші, для цього є відповідна галочка навпроти поля введення для посилання. Коли посилання буде вставлена, дані автоматично заповняться за Вас і потрібно буде лише вибрати значення комісії.</p><br/></p>У вкладці<span style=\" font-weight:600;\"> &quot;Отримати&quot;</span> ви можете вписати повідомлення і виставити потрібну суму грошей, після чого після натискання кнопки буде згенеровано посилання (запит), який ви можете передати іншому користувачеві (скопіювавши його), щоб він зробив переклад на Ваш гаманець. Під кнопками взаємодії ви можете спостерігати таблицю ваших заявок, які ви робили протягом усього часу.</p><br/></p>У вкладці<span style=\" font-weight:600;\"> &quot;Всі транзакції&quot;</span> ви можете бачити всі транзакції, які ви зробили за весь період роботи гаманця.</p><br/></p>Ця довідка створена для ознайомлення з програмою <span style=\" text-decoration: underline;\">BlockChain Wallet</span>, якщо у вас є якісь питання, відповіді на які ви не знайшли в цій довідці, або пропозиції, напишіть нам на пошту:<span style=\" font-weight:600;\"> blockchainwallet@gmail.com</span></p></body></html>");
        this->setWindowTitle("Про програму");

        break;
    case RUSSIAN:

        ui->textEdit_abot_program->setText("<html><head/><body>При <span style=\" font-weight:600;\">запуске программы</span> Вам высвечивается форма авторизации, в который Вас просят ввести свой личный ключ или же зарегистрироваться как новый пользователь. </p><br/></p>При входе в Ваш <span style=\" font-weight:600;\">личный кабинет</span> Вам высвечивается уведомление, которое оповещает Вас о текущем пароле. Этот пароль в дальнейшем Вам придётся вводить при каждом запуске программы, чтобы Вы его не забыли с течением времени, иначе мы не сможем восстановить Ваш кошелёк.</p><br/></p>На главном меню во вкладке <span style=\" font-weight:600;\">&quot;Обзор&quot;</span> Вы можете отследить Ваш <span style=\" font-style:italic;\">баланс</span> в <span style=\" font-style:italic;\">трёх валютах</span>. Под балансом Вы можете увидеть свой текущий <span style=\" font-style:italic;\">адрес</span> и <span style=\" font-style:italic;\">пароль</span>, который Вы можете скопировать, но ни в коем случае не передавайте его третьим лицам. Справа от баланса Вы сможете проследить Ваши последние четыре транзакции с полной информацией о сделке.</p><br/></p>Во вкладке <span style=\" font-weight:600;\">&quot;Отправить&quot;</span> Вам нужно ввести адрес кошелька пользователя, на который Вы хотите отправить определённую сумму с выбором валюты (адрес находится во вкладке<span style=\" font-weight:600;\"> &quot;Обзор&quot;</span>). Не обязательным условием является сообщение для этого пользователя. Вы можете ввести своё значение суммы для комиссии, которое будет влиять на скорость обработки Вашего платежа. Так же вы можете вставить ссылку другого пользователя, который запросил у Вас деньги, для этого есть соответствующая галочка напротив поля ввода для ссылки. Когда ссылка будет вставлена, данные автоматически заполнятся за Вас и нужно будет лишь выбрать значение комиссии.</p><br/></p>Во вкладке <span style=\" font-weight:600;\">&quot;Получить&quot;</span> Вы можете вписать сообщение и выставить нужную сумму денег, после чего по нажатии кнопки будет сгенерировано ссылка (запрос), который Вы можете передать другому пользователю (скопировав его), чтобы он сделал перевод на Ваш кошелёк. Под кнопками взаимодействия Вы можете наблюдать таблицу Ваших заявок, которые вы делали в течение всего времени.</p><br/></p>Во вкладке <span style=\" font-weight:600;\">&quot;Все транзакции&quot;</span> Вы можете видеть все транзакции, которые Вы совершили за весь период работы кошелька.</p><br/></p>Эта справка создана для ознакомления с программой<span style=\" text-decoration: underline;\"> BlockChain Wallet</span>, если у вас есть какие-то вопросы, ответы на которые вы не нашли в этой справке, или предложения, напишите нам на почту: <span style=\" font-weight:600;\">blockchainwallet@gmail.com</span></p></body></html>");
        this->setWindowTitle("О программе");

        break;
    }
}
