#pragma once
#ifndef FORM_H
#define FORM_H

#include "Clinet.h"

#include <QWidget>
#include <memory>
#include <thread>

namespace Ui {
class Form;
}

class Form : public QWidget {
    Q_OBJECT
public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private:
    Ui::Form *ui;
    std::vector<std::unique_ptr<Client>>m_v_Client;

public slots:
    void addClient();
    void maxClient();
};

#endif // FORM_H
