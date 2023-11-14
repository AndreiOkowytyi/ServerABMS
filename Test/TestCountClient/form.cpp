#include "form.h"
#include "ui_form.h"


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    QObject::connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(addClient()));
    QObject::connect(this->ui->pushButton_2, SIGNAL(clicked()), this, SLOT(maxClient()));


    this->ui->spinBox->setMaximum(1000);
}

Form::~Form()
{
    delete ui;
}

void Form::addClient() {

    const int count = this->ui->spinBox->value();
    this->ui->spinBox->setValue(0);

    for(short x = 0; x < count; ++x) this->m_v_Client.push_back(std::make_unique<Client>(this->ui->lineEdit->text()));

    this->ui->label_2->setText(QString::number(this->m_v_Client.size()));
}

void Form::maxClient() {

    std::thread as([this]() {
        for(;;){


            for(int x = 0; x < 12000; x++) {

            this->m_v_Client.push_back(std::make_unique<Client>(this->ui->lineEdit->text()));
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            this->ui->label_2->setText(QString::number(this->m_v_Client.size()));
        }
            for(int x = 12000; x > 0; x--) {

            this->m_v_Client.erase(m_v_Client.end());
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            this->ui->label_2->setText(QString::number(this->m_v_Client.size()));
            }
        }
    });

    as.detach();
}
